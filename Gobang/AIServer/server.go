package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"strconv"

	"./Gobang"
	"github.com/bitly/go-simplejson"
)

func main() {
	http.HandleFunc("/p0", handlerP0)
	http.HandleFunc("/p1", handlerP1)
	http.ListenAndServe(":80", nil)
}

func handlerP0(w http.ResponseWriter, r *http.Request) {
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

	fmt.Println("request: ", string(r_data))

	player := "" // "player_white" or "player_black"
	m := r_json.Get("body").MustMap()
	for k, _ := range m {
		player = k
		break
	}

	// 请求和回复的数据结构都一样，修改部分字段回复即可
	// 回复下棋的URL
	w_json := r_json
	w_json.SetPath([]string{"head", "result"}, 0)
	w_json.SetPath([]string{"head", "err_msg"}, "success")
	w_json.SetPath([]string{"body", player, "name"}, "alpha_"+player)
	w_json.SetPath([]string{"body", "url"}, "http://120.76.53.165/p1")

	w_json_bytes, _ := w_json.Encode()
	w.Write(w_json_bytes)
}

func handlerP1(w http.ResponseWriter, r *http.Request) {
	r_data, err := ioutil.ReadAll(r.Body)
	if err != nil {
		return
	}
	defer r.Body.Close()

	r_json, err := simplejson.NewJson(r_data)
	if err != nil {
		return
	}

	fmt.Println("request: ", string(r_data))

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
		x := m2["x"].(string)
		y := m2["y"].(string)
		side := m2["side"].(string)

		xi, _ := strconv.ParseInt(x, 10, 8)
		yi, _ := strconv.ParseInt(y, 10, 8)

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

	// response
	steps_json := simplejson.New()
	if flag == 1 {
		steps_json.Set("side", "b")
	} else {
		steps_json.Set("side", "w")
	}

	steps_json.Set("x", strconv.FormatInt(int64(row+1), 10))
	steps_json.Set("y", strconv.FormatInt(int64(col+1), 10))
	steps_json.Set("time", nil)

	w_json := r_json
	w_json.SetPath([]string{"body", "steps"}, []*simplejson.Json{steps_json})

	w_json_bytes, _ := w_json.Encode()
	w.Write(w_json_bytes)
}
