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
        //getcomponent�� �׳� ���� �ȵȴ�. ���⼭ �ִϸ��̼��� ���� ���Ͽ� �ִ�.
        anim = GetComponentInChildren<Animator>();
        missionCtrl_script = FindObjectOfType<MissionCtrl>();
    }

    //�̼� ����
    public void MissionStart()
    {
        anim.SetBool("IsUp", true);
        playerCtrl_script = FindObjectOfType<PlayerCtrl>();
        // �ʱ�ȭ
        for (int i = 0; i < images.Length; i++)
        {
            images[i].color = Color.white;
        }

            // ���� �۾�
        for (int i = 0; i < 4; i++)
        {
            int rand = Random.Range(0, 7);// 0 ~ 6 ����

            images[rand].color = red;// ������ ���ڸ� ĥ�ϱ�, �ߺ� ��� ���ߴ�.== 1~ 4
        }
    }

    //x��ư ������ ȣ��
    public void ClickCancle()
    {
        anim.SetBool("IsUp", false);
        playerCtrl_script.MissionEnd();
    }

    // ������ ��ư ������ ȣ��
    public void ClickButton()
    {
        Image img = EventSystem.current.currentSelectedGameObject.GetComponent<Image>(); // �̹��� �����ͼ� ����
        // ��ư ���� �Ͼ�� �̶��
        if(img.color == Color.white)
        {
            // ���������� !
            img.color = red;
        }
        else
        {
            // ���� �������̶�� �Ͼ������
            img.color = Color.white;
        }
        // ���� ���� üũ
        int count = 0;

        for (int i = 0; i < images.Length; i++)
        {
            if (images[i].color == Color.white)
            {
                count++;
            }
        }

        if(count == images.Length)
        { // �̼� ����
            Invoke("MissionSuccess",0.2f);
        }
    }

    // �̼� �����ϸ� ȣ��� �Լ�
    public void MissionSuccess()
    {   
        ClickCancle();
        missionCtrl_script.MissionSuccess(GetComponent<CircleCollider2D>());
    }
}
