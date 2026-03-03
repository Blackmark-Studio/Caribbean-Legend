// диалог освобожденных каторжников рудника
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("또 왔나, 나리?","이봐, 나리, 그냥 가는 게 좋을 거야...","귀찮게 하지 마시오, 나리! 정중히 부탁드리오.","아, 이건 정말 못 참겠어... 갤리선에서 노 젓는 게 차라리 나았지.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그래, 또 나야.","내게 이래라저래라 하지 마.","계속 귀찮게 하면 어쩔 건데?","그럼 주방으로 돌아가!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "무슨 일이오, 나리?";
				link.l1 = "너한테서? 아무것도 없어, 아마. 그냥 인사나 하려고 했지.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"운명을 시험하지 마, 이봐! 무기 집어넣어!","이봐, 나는 이 마을 시민이니 칼을 집어넣어 줘.");
			link.l1 = LinkRandPhrase("좋아...","원하시는 대로...","말씀대로 하겠습니다...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
