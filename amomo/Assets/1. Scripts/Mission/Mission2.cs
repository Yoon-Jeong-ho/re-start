using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Mission2 : MonoBehaviour
{
    public Transform trash,handle; 
    Animator anim;
    PlayerCtrl playerCtrl_script;
    public GameObject bottom; //바닥을 꺼야 한다.
    public Animator anim_shake;


    RectTransform rect_handle;

    bool isDrag,isPlay;
    Vector2 originPos;
    MissionCtrl missionCtrl_script;

    // Start is called before the first frame update
    void Start()
    {
        //getcomponent를 그냥 쓰면 안된다. 여기서 애니메이션은 하위 파일에 있다.
        anim = GetComponentInChildren<Animator>();
        rect_handle = handle.GetComponent<RectTransform>();
        originPos = rect_handle.anchoredPosition;//핸들의 원 위치를 저장

        missionCtrl_script = FindObjectOfType<MissionCtrl>();

    }

    private void Update()
    {
        if (isPlay)
        {
            // 드래그
            if (isDrag)
            { // 핸들의 위치를 이동해준다.
                handle.position = Input.mousePosition;
                rect_handle.anchoredPosition = new Vector2(originPos.x, Mathf.Clamp(rect_handle.anchoredPosition.y, -135, -47)); // 제한해줌!

                anim_shake.enabled = true;

                // 드래그 끝
                if (Input.GetMouseButtonUp(0))
                { // 움직임이 끝났을 때 핸들의 위치를 원위치해준다.
                    rect_handle.anchoredPosition = originPos;
                    isDrag = false;
                    anim_shake.enabled = false;

                }

            }

            // 쓰레기 내려갈 조건
            if (rect_handle.anchoredPosition.y <= -130)
            {
                bottom.SetActive(false);
            }
            else
            {
                bottom.SetActive(true);
            }

            // 쓰레기가 끝까지 내려가지 않게 삭제해준다.
            for (int i = 0; i < trash.childCount; i++)
            {
                if (trash.GetChild(i).GetComponent<RectTransform>().anchoredPosition.y <= -600)
                {
                    Destroy(trash.GetChild(i).gameObject);
                }
            }

            //성공여부 체크
            if (trash.childCount == 0)
            {
                MissionSuccess();
                isPlay = false;

                rect_handle.anchoredPosition = originPos;
                isDrag = false;
                anim_shake.enabled = false;
            }
        }
    }

    //미션 시작
    public void MissionStart()
    {
        anim.SetBool("IsUp", true);
        playerCtrl_script = FindObjectOfType<PlayerCtrl>();
        // 초기화
        for(int i = 0; i < trash.childCount; i++)
        { // 생성된 쓰레기 만큼
            Destroy(trash.GetChild(i).gameObject);
        }

        // 쓰레기 스폰
        for(int i = 0; i < 10; i++)
        {   
            // 사과
            GameObject trash4 =Instantiate(Resources.Load("Trash/Trash 4"),trash)as GameObject;
            trash4.GetComponent<RectTransform>().anchoredPosition = new Vector2(Random.Range(-180, 180), Random.Range(-180, 180)); // 위치 랜덤 지정
            trash4.GetComponent<RectTransform>().eulerAngles = new Vector3(0,0, Random.Range(0, 180)); // 각도 랜덤 지정

            // 캔
            GameObject trash5 = Instantiate(Resources.Load("Trash/Trash 5"), trash) as GameObject;
            trash5.GetComponent<RectTransform>().anchoredPosition = new Vector2(Random.Range(-180, 180), Random.Range(-180, 180)); // 위치 랜덤 지정
            trash5.GetComponent<RectTransform>().eulerAngles = new Vector3(0, 0, Random.Range(0, 180)); // 각도 랜덤 지정

        }        
        for(int i = 0; i < 3; i++)
        {   
            // 병
            GameObject trash1 =Instantiate(Resources.Load("Trash/Trash 1"),trash)as GameObject;
            trash1.GetComponent<RectTransform>().anchoredPosition = new Vector2(Random.Range(-180, 180), Random.Range(-180, 180)); // 위치 랜덤 지정
            trash1.GetComponent<RectTransform>().eulerAngles = new Vector3(0,0, Random.Range(0, 180)); // 각도 랜덤 지정

            // 생선
            GameObject trash2 = Instantiate(Resources.Load("Trash/Trash 2"), trash) as GameObject;
            trash2.GetComponent<RectTransform>().anchoredPosition = new Vector2(Random.Range(-180, 180), Random.Range(-180, 180)); // 위치 랜덤 지정
            trash2.GetComponent<RectTransform>().eulerAngles = new Vector3(0, 0, Random.Range(0, 180)); // 각도 랜덤 지정
            //비닐
            GameObject trash3 = Instantiate(Resources.Load("Trash/Trash 3"), trash) as GameObject;
            trash3.GetComponent<RectTransform>().anchoredPosition = new Vector2(Random.Range(-180, 180), Random.Range(-180, 180)); // 위치 랜덤 지정
            trash3.GetComponent<RectTransform>().eulerAngles = new Vector3(0, 0, Random.Range(0, 180)); // 각도 랜덤 지정

        }
        isPlay = true;
    }

    //x버튼 누르면 호출
    public void ClickCancle()
    {
        anim.SetBool("IsUp", false);
        playerCtrl_script.MissionEnd();
    }

    //손잡이 누르면 호출
    public void ClickHandle()
    {
        isDrag = true;
    }


    // 미션 성공하면 호출될 함수
    public void MissionSuccess()
    {
        ClickCancle();
        missionCtrl_script.MissionSuccess(GetComponent<CircleCollider2D>());

    }
}
