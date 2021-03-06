package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"time"

	"./Gobang"
	"github.com/bitly/go-simplejson"
)

func main() {
	fmt.Println("listening: 80 ...")
	http.HandleFunc("/AI", handlerAI)
	http.ListenAndServe(":80", nil)
}

func handlerAI(w http.ResponseWriter, r *http.Request) {
	r_data, err := ioutil.ReadAll(r.Body)
	if err != nil {
		return
	}
	defer r.Body.Close()

	r_json, err := simplejson.NewJson(r_data)
	if err != nil {
		w.Write([]byte("parse request failed"))
		return
	}
	w_json := r_json

	// 0 - 控制消息    1 - 下棋消息
	msg_type := r_json.GetPath("head", "type").MustInt()
	fmt.Println("---------------------------------------------------")
	fmt.Println("request type:", msg_type, string(r_data))
	fmt.Println("---------------------------------------------------")

	if msg_type == 0 {
		player_black := r_json.GetPath("body", "player_black").MustMap()

		// 请求和回复的数据结构都一样，修改部分字段回复即可
		// 回复下棋的URL
		w_json.SetPath([]string{"head", "result"}, 0)
		w_json.SetPath([]string{"head", "err_msg"}, "success")
		w_json.SetPath([]string{"body", "url"}, "http://120.76.53.165/AI")
		if player_black == nil || len(player_black) == 0 {
			w_json.SetPath([]string{"body", "player_white", "name"}, "alpha_white")
		} else {
			w_json.SetPath([]string{"body", "player_black", "name"}, "alpha_black")
		}

	} else {
		// 读取棋盘信息
		chessMap := make([][]byte, 0)
		for i := 0; i < 15; i++ {
			sliceByte := make([]byte, 0)
			for j := 0; j < 15; j++ {
				sliceByte = append(sliceByte, ' ')
			}
			chessMap = append(chessMap, sliceByte)
		}

		m := r_json.GetPath("body", "steps").MustArray()
		for _, v := range m {
			var m2 map[string]interface{} = v.(map[string]interface{})
			xi, _ := m2["x"].(json.Number).Int64()
			yi, _ := m2["y"].(json.Number).Int64()
			side := m2["side"].(string)

			if xi >= 1 && xi <= 15 && yi >= 1 && yi <= 15 {
				if side == "w" {
					chessMap[xi-1][yi-1] = 'W'
				} else {
					chessMap[xi-1][yi-1] = 'B'
				}
			}
		}

		// AI
		row, col, flag := Gobang.AI(chessMap)

		fmt.Printf("******* row: %v  col: %v  len(map): %v\n", row+1, col+1, len(m))

		// response
		steps_json := simplejson.New()
		if flag == 1 {
			steps_json.Set("side", "b")
		} else {
			steps_json.Set("side", "w")
		}

		steps_json.Set("x", row+1)
		steps_json.Set("y", col+1)
		steps_json.Set("time", getTime())

		w_json := r_json

		// stepArray := r_json.GetPath("body", "steps").MustArray()
		// stepArray = append(stepArray, steps_json)
		w_json.SetPath([]string{"body", "steps"}, []*simplejson.Json{steps_json})
	}

	w_json_bytes, _ := w_json.Encode()
	w.Write(w_json_bytes)

	fmt.Println("---------------------------------------------------")
	fmt.Println("reponse type:", msg_type, string(w_json_bytes))
	fmt.Println("---------------------------------------------------")
}

func getTime() string {
	now := time.Now()
	year, mon, day := now.Date()
	hour, min, sec := now.Clock()
	return fmt.Sprintf("%d%d%d%02d%02d%02d", year, mon, day, hour, min, sec)
}
