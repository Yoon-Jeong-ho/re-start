using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Mission1 : MonoBehaviour
{
    public Color red;
    Animator anim;
    PlayerCtrl playerCtrl_script;
    public Image[] images;
    MissionCtrl missionCtrl_script;

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
        // 초기화
        for (int i = 0; i < images.Length; i++)
        {
            images[i].color = Color.white;
        }

            // 랜덤 작업
        for (int i = 0; i < 4; i++)
        {
            int rand = Random.Range(0, 7);// 0 ~ 6 랜덤

            images[rand].color = red;// 랜덤한 숫자를 칠하기, 중복 고려 안했다.== 1~ 4
        }
    }

    //x버튼 누르면 호출
    public void ClickCancle()
    {
        anim.SetBool("IsUp", false);
        playerCtrl_script.MissionEnd();
    }

    // 육각형 버튼 누르면 호출
    public void ClickButton()
    {
        Image img = EventSystem.current.currentSelectedGameObject.GetComponent<Image>(); // 이미지 가져와서 저장
        // 버튼 색이 하얀색 이라면
        if(img.color == Color.white)
        {
            // 빨간색으로 !
            img.color = red;
        }
        else
        {
            // 만약 빨간색이라면 하얀색으로
            img.color = Color.white;
        }
        // 성공 여부 체크
        int count = 0;

        for (int i = 0; i < images.Length; i++)
        {
            if (images[i].color == Color.white)
            {
                count++;
            }
        }

        if(count == images.Length)
        { // 미션 성공
            Invoke("MissionSuccess",0.2f);
        }
    }

    // 미션 성공하면 호출될 함수
    public void MissionSuccess()
    {   
        ClickCancle();
        missionCtrl_script.MissionSuccess(GetComponent<CircleCollider2D>());
    }
}
