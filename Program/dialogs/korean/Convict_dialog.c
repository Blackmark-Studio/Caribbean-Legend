// диалог каторжников в шахте
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("미안하지만, 우리 둘 다를 위해 이제 더 이상 서로 이야기하지 않는 게 좋겠어. 나는 벌을 받을 테고, 너는 떠나라는 소리를 듣게 될 거야.","이미 다 말했잖아, 친구. 아니면 네 때문에 내가 채찍질이라도 당하길 바라는 거야?","나는 듣고 있지 않아...","스파에이드가 번쩍이며 곡괭이를 쾅 하고 내리친다...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("여기 규칙이 엄격하군...","아니, 당연히 원하지 않아.","흠...","아버지, 제 목소리 들리시나요...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "선장님, 뭐 하십니까? 곤란한 일 생기기 전에 무기를 집어넣으십시오!";
			link.l1 = LinkRandPhrase("좋아.","좋아.","걱정 마, 내가 잘 숨겨두고 있으니까...");
			link.l1.go = "exit";
		break;  
	}
}
