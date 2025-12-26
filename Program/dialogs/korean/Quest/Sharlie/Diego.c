// Диего де Монтойя
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "원하는 게 있소?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+", 산호세 순찰대장이다. 이 마을 변두리에서 수상한 행동이 있다는 신고를 받았다. 실례지만, 당신이 누구이며 무슨 일로 여기 있는지 설명해 주시겠는가?";
			link.l1 = "Captain "+GetFullName(pchar)+", 장교 나리. 나는 종교재판관 빈첸토 신부의 권한과 직접 지시에 따라 이곳에 왔소. 이것이 내 권한을 증명하는 문서요.";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "좋소... 모든 게 이상 없어 보이오. 종교재판관의 서명까지 제대로 작성되어 있군. 괜히 의심해서 미안하오. 등대에서 무얼 하고 있소?";
			link.l1 = "저는 그런 질문에 답변할 권한이 없습니다. 만약 정말로 제가 종교재판관을 위해 무슨 일을 하는지 궁금하다면, 산티아고에 있는 그분께 직접 문의하여 설명을 들으시길 권합니다.\n당신은 장교이니 군사와 업무상의 비밀에 대해 잘 알겠지요. 제가 말씀드릴 수 있는 유일한 것은, 난파된 스페인 선박의 상황을 조사하고 있다는 점뿐입니다.";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "다시 한 번 사과드리오, 나리. 더 이상 지체하지 않겠소... 아, 잠깐만! 방금 차가운 강철의 칼날을 본 것 같은데, 내 착각이었소? 참 흥미로운 단검이구려! 나에게 보여줄 수 있겠소?";
			link.l1 = "반드시 돌려주는 것, 잊지 마. 내게 아주 중요한 거야.";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "세상에! 이 단검을 알아요, 도서관 책에서 그림으로 본 적이 있어요! 이건 바로 코르테스 본인의 단검이에요! 여기 각인도 있잖아요... 나리, 제발 거절하지 마십시오. 이 단검을 저에게 주십시오! 저는 고대 무기와 맞춤 무기를 수집하는데, 이건 정말 엄청난 유물입니다. 값은 충분히 쳐드리겠습니다.";
			link.l1 = "나리, 이 단도는 팔 물건이 아니오. 선물로 받은 것이니 누구에게도 팔 생각이 없소. 돌려주시오, 제발.";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "오백 금화 더블룬으로도 만족 못 하겠다고? 그건 엄청난 돈이야. 그 정도면 배 한 척은 살 수 있지!";
			link.l1 = "아니. 나는 이미 배가 있고, 이 단도는 세상에 하나뿐이야. 팔 생각 없어.";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "에이, 그거 참 안됐군... 좋아, 귀중품 챙겨가. 더 이상 방해하지 않겠어. 행운을 빌지!";
			link.l1 = "행운을 빕니다, 장교님.";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("Voice\English\Sharlie\Diego De Montoya.wav");
			dialog.text = "그만해! 나 그와 할 말이 있어...";
			link.l1 = "그래, 내가 지금 내 눈앞에서 디에고 데 몬토야 그대를 직접 보게 되는군... 하지만 실례하오, 나리. 우리 예전에 만난 적 있지 않소? 아, 맞아. 트리니다드, 그곳 등대에서였지. 하지만 그때는 분명 다른 이름을 썼던 걸로 기억하오...\n";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "기억력이 좋으시군요, 나리. 뭐, 뒤에서 음모를 꾸미고 전쟁을 벌일 수 있는 사람이 당신만은 아니오. 내가 당신이 나를 보고 싶어 안달이 났다는 것도 잘 알고 있소. 자, 당신의 소원이 이루어진 것 같군.";
			link.l1 = "이런 만남을 기대한 건 아니었소, 나리.";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "뭐, 어쩔 수 없지. 하지만 네가 단도를 내놓으면 여기서 살아나갈 기회를 주겠다.";
			link.l1 = "희귀한 물건을 모으는 너의 열정이 정말 그렇게 깊이 빠졌나, 카바예로? 나를 잡으려고 이렇게 치밀한 함정까지 준비하다니? \n아니, 난 그렇게 생각하지 않아. 진실의 수호자가 널 긴장하게 만드는 건가, 아니면 내가 완전히 헛짚은 건가?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "무슨 말을 하는 건지 전혀 모르겠군. 단검은 제자리로 돌아가야 하고, 그게 네가 알아야 할 전부다. 금을 줘도 내놓지 않더니, 이제는 네 목숨을 위해 내놓게 될 거다.";
			link.l1 = "정말로 내가 방금 한 말을 믿을 거라고 생각하나, 나리? 이미 내가 이 만을 떠나지 못하게 하기로 결심한 것 아니었나?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "내가 맹세한다면 어쩔 텐가?";
			link.l1 = "'개구리 먹는 놈'이라는 말인가? 흠...";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "나리, 마지막 기회를 드리겠소. 내가 관심 있는 단도를 넘기시오, 아니면 잠시 후에 그 시체에서 직접 챙기게 될 것이오. 저항은 무의미하오; 우리 쪽이 수적으로 압도적이니까.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "정말 놀랐소, 나리. 내가 그렇게 멍청하고 고집 센 놈이라 아무 준비도 없이 상어 입에 머리를 들이밀 거라 생각했소? 얘들아, 저놈들 죽여라!";
			else link.l1 = "진정한 힘은 수에 있는 게 아니라, 실력에 있지, 나리!";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
