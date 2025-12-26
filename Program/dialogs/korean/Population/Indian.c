//Jason общий диалог индейцев на улицах
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
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","백인 스콰")+" 이야기하고 싶은 사람?","또 너군, "+GetSexPhrase("창백한 놈","백인 여자 인디언")+".",""+GetSexPhrase("창백한 얼굴은 말이 많구나. 여자처럼.","백인 여자 인디언은 말하는 걸 좋아하지.")+"","위대한 영이 백인을 데려왔소"+GetSexPhrase("형제","자매")+" 나에게.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그래.","그래, 또 나야.","참으로 시적이군.","나도 다시 만나서 반갑소.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕, 백인 형제여. 인디언과 이야기하고 싶은가?";
				link.l1 = "정글의 아들이여, 반갑소. 하지만 나는 가야 하오.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"정령을 자극하지 마라, 창백한 얼굴! 그 긴 칼 집어넣어!","죽으려고 서두르지 마라, 창백한 얼굴! 그 긴 칼 집어넣어!");
			link.l1 = LinkRandPhrase("좋아.","원하시는 대로 하겠습니다.","말씀대로 하겠습니다.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
