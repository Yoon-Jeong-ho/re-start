using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Mission3 : MonoBehaviour
{
    public Text inputText, keyCode;
    
    Animator anim;
    PlayerCtrl playerCtrl_script;

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

        //�ʱ�ȭ
        inputText.text = "";
        keyCode.text = "";

        // Ű�ڵ� ����
        for (int i = 0; i < 5; i++)
        {
            keyCode.text += Random.Range(0, 10); // 0 ~ 9 
        }
    }

    //x��ư ������ ȣ��
    public void ClickCancle()
    {
        anim.SetBool("IsUp", false);
        playerCtrl_script.MissionEnd();
    }

    //���� ��ư ������ ȣ��
    public void ClickNumber()
    {
        if (inputText.text.Length <= 4)
        {//���� �� ���� ����
            inputText.text += EventSystem.current.currentSelectedGameObject.name;
        }

    }

    // ���� ��ư ������ ȣ��
    public void ClickDelete()
    {// input�� �ý�Ʈ�� �־�߸� �۵��Ѵ�.
        if(inputText.text!= "")
        {
            inputText.text =inputText.text.Substring(0, inputText.text.Length - 1);
        }

    }

    // üũ ��ư ������ ȣ��
    public void ClickCheck()
    {
        if (inputText.text == keyCode.text)
        {
            MissionSuccess();
        }
    }

    // �̼� �����ϸ� ȣ��� �Լ�
    public void MissionSuccess()
    {
        ClickCancle();
        missionCtrl_script.MissionSuccess(GetComponent<CircleCollider2D>());

    }
}
