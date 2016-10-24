package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"strconv"
	// "./Gobang"

	"github.com/bitly/go-simplejson"
)

func main() {
	test()

	// http.HandleFunc("/p0", handlerP0)
	// http.HandleFunc("/p1", handlerP1)
	// http.ListenAndServe(":8989", nil)
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

	fmt.Println("request: %v", r_json)

	player := "" // "player_white" or "player_black"
	m := r_json.Get("body").MustMap()
	for k, _ := range m {
		player = k
		break
	}

	// 请求和回复的数据结构都一样，修改部分字段回复即可
	w_json := r_json
	w_json.SetPath([]string{"head", "result"}, 0)
	w_json.SetPath([]string{"head", "err_msg"}, "success")
	w_json.SetPath([]string{"body", player, "name"}, "alpha_"+player)
	w_json.SetPath([]string{"body", "url"}, "http://120.76.53.165/p1")

	w_json_bytes, _ := w_json.Encode()
	w.Write(w_json_bytes)
}

func handlerP1(w http.ResponseWriter, r *http.Request) {

}

func test() {
	json := simplejson.New()
	head := simplejson.New()

	head.Set("type", "0")
	head.Set("result", 0)
	head.Set("err_msg", "success")

	json.Set("head", head)

	body := simplejson.New()
	player := simplejson.New()
	player.Set("type", "MACHINE")
	player.Set("name", "alpha")
	player.Set("url", "localhost:8989/hello/P1")
	player.Set("side", "w")
	body.Set("player_white", player)

	json.Set("body", body)

	json_byte, _ := json.Encode()
	fmt.Println(string(json_byte))

	// ----------

	r_json, _ := simplejson.NewJson(json_byte)

	fmt.Println(r_json.Get("head").Get("err_msg"))
	fmt.Println(strconv.FormatInt(r_json.Get("head").Get("type").MustInt64(), 10))

	fmt.Println(r_json.GetPath("body", "player_white", "url").MustString())

	// r_json.SetPath(branch, val)
	// fmt.Println(r_json.MustString())
	r_json.SetPath([]string{"body", "player_white", "url"}, "www.baidu.com")

	fmt.Println(r_json.GetPath("body", "player_white", "url").MustString())
}
