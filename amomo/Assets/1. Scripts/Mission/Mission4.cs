using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Mission4 : MonoBehaviour
{
    // 버튼을 가져오자
    public Transform numbers;
    public Color blue;
    Animator anim;
    PlayerCtrl playerCtrl_script;
    MissionCtrl missionCtrl_script;

    int count;
    // Start is called before the first frame update
    void Start()
    {
        //getcomponent를 그냥 쓰면 안된다. 여기서 애니메이션은 하위 파일에 있다.
        anim = GetComponentInChildren<Animator>();
        missionCtrl_script = FindObjectOfType<MissionCtrl>();

    }

    //미션 시작
    public void MissionStart()
    {
        anim.SetBool("IsUp", true);
        playerCtrl_script = FindObjectOfType<PlayerCtrl>();
        // 모든 버튼의 색을 하얀색으로 초기화
        for(int i = 0; i < numbers.childCount; i++)
        {
            numbers.GetChild(i).GetComponent<Image>().color = Color.white;
            numbers.GetChild(i).GetComponent<Button>().enabled = true; // 버튼 초기화
        }

        // 숫자 랜덤 배치
        for(int i = 0; i < 10; i++)
        {
            //전부다 섞인다.
            Sprite temp = numbers.GetChild(i).GetComponent<Image>().sprite;

            int rand = Random.Range(0,10);
            numbers.GetChild(i).GetComponent<Image>().sprite = numbers.GetChild(rand).GetComponent<Image>().sprite;
            numbers.GetChild(rand).GetComponent<Image>().sprite = temp;

        }
        count = 1;
    }

    //x버튼 누르면 호출
    public void ClickCancle()
    {
        anim.SetBool("IsUp", false);
        playerCtrl_script.MissionEnd();
    }

    // 숫자 버튼 누르면 호출 될 함수
    public void ClickNumber()
    {
        if(count.ToString() == EventSystem.current.currentSelectedGameObject.GetComponent<Image>().sprite.name)
        {// 차례대로 숫자를 누를것인지 판단
            // 버튼 색 변경
            EventSystem.current.currentSelectedGameObject.GetComponent<Image>().color = blue; // 바꾸는게 생기면 초기화도 생각해야 한다.

            // 성공했으면 버튼 비활성화
            EventSystem.current.currentSelectedGameObject.GetComponent<Button>().enabled = false;//다신 누를 수 없게! 그럼 초기화도 !

            count++;

            // 성공 여부 체크
            if(count == 11)
            {
                Invoke("MissionSuccess",0.2f); // 0.2초뒤 실행 
            }
        }
    }


    // 미션 성공하면 호출될 함수
    public void MissionSuccess()
    {
        missionCtrl_script.MissionSuccess(GetComponent<CircleCollider2D>());

        ClickCancle();
    }
}
