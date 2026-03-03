void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN) {
				link.chickengod = "Senora, please excuse me, but I was asked to tell you that you have... a date inside an old pagan pyramid.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("예수님! 이런 비열한 자가 내 방에 들어오다니! 당장 나가라, 아니면 경비병을 부를 것이다!","이럴 리가 없어... 누가 이 쥐새끼를 내 집에 들였지? 당장 꺼져라, 이 자식아! 네가 여기 있을 이유는 없어! 썩 꺼져!","이상한 시대가 왔군. 쥐들이 내 침실까지 들어오고 있어! 꺼져!");
				link.l1 = RandPhraseSimple("진정해...","입 조심해라...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("내 침실에서 뭐 하는 거야? 당장 나가!","정말 유감이오! 당장 이곳을 떠나 주시오!","실례합니다, 나리, 하지만 여기는 초대받지 않으셨습니다. 제 방에서 나가 주십시오!");
				link.l1 = RandPhraseSimple("실례하오... 나는 떠나겠소.","미안하지만, 잘못 들어왔네. 나 가봐야겠어.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "어, 저게 뭐였지?! 내가 정말 바보구나! 두리번거리다가 아무것도 못 봤어... 경비병!!!";
			link.l1 = "닥쳐!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("여기서 꺼져라, 쥐새끼야!","지금 당장 총독 저택에서 꺼져라, 쥐새끼야!","나는 네가 총독 관저에서 뭘 하든 신경 안 써 "+XI_ConvertString("Colony"+npchar.city+"Gen")+"하지만 내 조언은, 지금 당장 꺼지라는 거야!");
				link.l1 = RandPhraseSimple("진정해, 친구...","말 조심해!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("안녕하십니까! 저는 총독의 하인입니다. 제 이름은 "+GetFullName(NPChar)+".","나는 이곳을 지키고 있지, "+GetAddress_Form(NPChar)+".","있잖아, "+GetAddress_Form(NPChar)+", 우리 총독은 좋은 분이시고 우리에게 보수를 잘 주시지...");
				link.l1 = RandPhraseSimple("좋군.","흠, 좋아...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "그래서 총독을 털기로 한 거냐?! 경비병들아, 저 도둑을 잡아라!!";
			link.l1 = "입 닥쳐!";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("여기서 나가는 게 좋겠어, "+GetSexPhrase("친구","소녀")+"...","꺼져!","문을 놓쳤군, "+GetSexPhrase("친구","소녀")+"? ? 이 영지는 총독의 소유다 "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				link.l1 = RandPhraseSimple("내가 원할 때 떠날 거야!","네가 알 바 아니야...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("오늘 여기서 근무하라는 명령을 받았어. 괜찮은 곳이네...","나는 ...의 영지를 지킨다 "+GetAddress_Form(NPChar)+".","내 임무는 총독의 저택을 지키는 것이다.");
				link.l1 = RandPhraseSimple("그럼, 행운을 빌지...","흠, 알겠군...");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "아, 그래. 드디어! 이제 당신과 함께 갈 준비가 됐어, 선장.";
				link.l1 = "그냥 이렇게요? 나리, 정말 이게 원하시는 건가요?";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "뭐라고?! 술 취했어, 나리? 이런 바보 같은 농담이 어디 있어! 제발 가 줘, 부탁이야! "+sld.name+"! 경비병들! 도와줘!";
				link.l1 = "젠장, 이제 가야겠다.";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "그럼요, 물론이지! 아, 아루바 나리와 나는 오랫동안 편지를 주고받는 사이였지!";
			link.l1 = "그렇다면, 배에 올라오십시오!";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "아니오, 부인, 그럴 수 없습니다. 내 명예가 여인을 위험에 빠뜨리는 것을 허락하지 않소, 그리고 분명히 누군가에게 속으셨군요!";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "그렇다면, 내 사랑하는 선장 나리, 그 촌스러운 명예심이나 네 엉덩이에나 쑤셔 넣으라고! 나는 다른 전령을 기다릴 거야, 너처럼 옹졸하지 않은 사람을!";
			link.l1 = "매력적이군!";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;
		
		case "chickengod_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
		
	}
}
