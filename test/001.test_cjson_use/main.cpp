#include <stdio.h>
#include <sys/time.h>

#include"cJSON.h"

// g++ -g -o cjson_speed_test -std=c++14 cjson_speed_test.c cJSON.c

int main()
{
    int cnt = 0;
    timeval st, et;

    cJSON *json_root;
    char str_buf[1024] = "{\"uri\":\"/uriCSh56j30cbGa\",\"host\":\"www.baidu.com\",\"uagent\":\"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36 Edg/91.0.864.64\",\"accept\":\"*/*\",\"method\":\"GET\",\"date\":\"Mon, 12 Jul 21 10:35:26 GMT\",\"resp_content_type\":\"video/fli\",\"status\":200,\"resp_content_length\":20480,\"timestamp\":\"2021-07-12T02:38:13.074829000\",\"traffic_id\":1057153235624398,\"protocol\":\"http\",\"src_ip\":\"112.1.101.40\",\"src_port\":22291,\"dst_ip\":\"112.2.81.190\",\"dst_port\":80,\"random_code\":7449212903698783717,\"feature_code\":\"y0BMEwnJ7RFICUAC5FKYkStTLVw=\"}";

    gettimeofday(&st, NULL);
    while(1) {
        json_root = cJSON_Parse(str_buf);

        cJSON_GetObjectItem(json_root, "protocol");
        cJSON_GetObjectItem(json_root, "uri");

        cJSON_GetObjectItem(json_root, "host");
        cJSON_GetObjectItem(json_root, "uagent");

        cJSON_GetObjectItem(json_root, "src_port");
        cJSON_GetObjectItem(json_root, "dst_port");

        cJSON_GetObjectItem(json_root, "timestamp");
        cJSON_GetObjectItem(json_root, "feature_code");

        cJSON_GetObjectItem(json_root, "src_ip");
        cJSON_GetObjectItem(json_root, "dst_ip");

        cJSON_GetObjectItem(json_root, "traffic_id");
        cJSON_GetObjectItem(json_root, "random_code");

        cJSON_Delete(json_root);

        cnt++;
        gettimeofday(&et, NULL);
        if(et.tv_sec - st.tv_sec >= 10) {
            break;
        }
    }

    printf("deserialization per second:%d\n", cnt/10);
    return 0;
}


