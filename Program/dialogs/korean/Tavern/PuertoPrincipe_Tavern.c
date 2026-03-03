// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안만 해도, 그 질문을 벌써 세 번째 꺼냈군...","또 질문이 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 어디로 갔지...","그래, 정말 이번이 세 번째야...","아니, 무슨 질문이 있다고?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "누가 당신의 소중한 진을 슬쩍했다는 소문이 돌고 있네. 아니면 그저 헛소문인가?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "좋은 소식이오, "+npchar.name+"! 네 통을 되찾아왔어!";
				link.l1.go = "OS_Tavern3_1";
			}
		//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "맙소사, 사실이군. 또 들은 게 있나? 뭔가 아는 거야? 제발, 어디서 찾을 수 있는지 안다고 말해 줘. 그걸 되찾지 못하면... 이 마을에서 도망쳐야 해. 내 두 발로 나가든, 아니면 관 속에 들어가든.";
			link.l1 = "정말로, 네 처지가 암담해 보이는군, 친구야. 아니, 네 불운에 대한 소문만 들었을 뿐이야. 그렇게 귀한 화물이 어떻게 네 손을 빠져나간 거지?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern1_2":
			dialog.text = "젠장... 뭐라고 해야 하나? 내 코앞에서 도둑맞았지 뭐야! 아침까지만 해도 그 통은 분명 여기 있었어. 이틀 전에 도착해서, 안전하게 보관하려고 밤에는 집에 가져갔지. 아침에 다시 가져와서 카운터 밑에 잘 숨겨뒀는데, 저녁이 되니 흔적도 없이 사라졌어! 아무도 본 사람도, 들은 사람도 없어.";
			link.l1 = "이런, 망할...";
			link.l1.go = "OS_Tavern1_3";
		break;

		case "OS_Tavern1_3":
			dialog.text = "내가 조금이라도 단서를 잡았다면 벌써 쫓고 있었을 거야. 하지만 유감스럽게도 아무것도 없어 – 마치 그 술통이 이 세상에 어울리지 않아 하늘이 가져가 버린 것처럼 말이지. 그걸 되찾아 오는 자에게는 150두블룬을 주겠어. 그뿐만 아니라, 내 선술집에 그 사람 이름을 새긴 명패도 걸어둘 테니 모두가 그 용맹한 일을 알게 될 거야!\n";
			link.l1 = "내가 할 수 있는 걸 알아볼게. 이 명패 문제는 나중에 다시 얘기하자고. 대신 말해 봐, 이 통에 대해 누가 알고 있었지? 그리고 너 말고 카운터 뒤에 있었던 사람이 또 있나?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "통 하나에 150두블룬이라고? 웃기는군. 하지만 네 문제는 내 문제가 아니야. 네가 알아서 해결해.";
			link.l2.go = "OS_Tavern1_end";
		break;

		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");

			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;

		case "OS_Tavern1_4":
			dialog.text = "거의 아무도 없었지! 내 시중드는 아가씨라면 모를까, 하지만 그건 불가능해. 그날은 선술집이 유난히 북적였거든. 'Sea Beast' 선원들이 사냥에서 멋진 전리품을 들고 돌아왔지. 그녀는 잠시도 쉴 틈이 없었어, 내 계산대 뒤로 몰래 들어갈 시간은 말할 것도 없고.";
			link.l1 = "그게 확실해?";
			link.l1.go = "OS_Tavern1_5";
		break;

		case "OS_Tavern1_5":
			dialog.text = "의심할 여지 없지! 쉴 틈 없이 일하는 건 그녀 성미에 안 맞았고, 저녁이 되자 완전히 팽팽해졌어. 선원 하나가 치근덕거리자, 그녀가 난리를 피워서 온 술집이 귀가 멍멍해질 뻔했지. 내가 자리를 비우고 나서야 겨우 진정시켰어. 이상한 일이야 - 평소엔 그런 접근에도 훨씬 침착하게 대처하거든.";
			link.l1 = "그게 전부야? 그날 다른 이상한 일은 없었어?";
			link.l1.go = "OS_Tavern1_6";
		break;

		case "OS_Tavern1_6":
			dialog.text = "내가 첫 번째 소동을 진정시키고 있을 때, 또 다른 소란이 일어났어\n저 구석에서 선원 둘이 주먹다짐을 벌였지. 하지만 싸움은 오래가지 않았어\n둘은 같은 배 동료로 보였고, 금방 떼어놓았거든. 그 후로는 정말 조용해졌고, 더 이상 언급할 만한 일도 없었어.";
			link.l1 = "좋아, 내가 수색을 시작하지. 기다려. 곧 그 통이 다시 자네, 음... 예리한 감시 아래 돌아올 것 같군.";
			link.l1.go = "OS_Tavern1_7";
		break;
		//<-- Старые счёты
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "찾으셨습니까?! 정말입니까? 선장님, 제 목숨을 구해주셨군요! 누가 이런 짓을 한 겁니까? 그 악당의 이름을 꼭 알아야겠습니다!";
			link.l1 = "그건 '씨 비스트'의 선장과 한패인 잭 베일스라는 자가 치밀하게 계획한 계략이었소. 그들은 선원들을 끌어들여 정교한 속임수를 벌여 자네를 유인했지. 자네가 자리를 비운 사이, 그 통은 무방비 상태였고, 놈들은 손쉽게 그것을 훔쳐 달아났소.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "이런, 맙소사! 잭 베일스! 결국 돌아왔군... 그리고 저런 비열한 수로 선술집을 되찾으려 했던 모양이야. 저 여우 녀석은 절대 패배를 인정하지 않지!";
			link.l1 = "그가 한때 이곳의 주인이었단 말이지? 안심해라, 이제 다시는 꿍꿍이 못 부릴 거다. 내가 저승으로 보냈으니까.";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "선장님! 이건 정말 놀라운 일이에요! 당신이... 당신이 제게 드리웠던 끊임없는 두려움에서 저를 해방시켜 주셨군요! 전 항상 그가 언젠가는 돌아올 거라고 알고 있었어요... 몇 년 전, 우리는 이 선술집의 소유권을 두고 경쟁하는 라이벌이었고, 그는 저를 이겼죠\n하지만 승리의 기쁨이 결국 그의 발목을 잡았어요 – 그는 축하에 도취되어 이곳을 카드 게임으로 저에게 내주고 말았죠. 물론, 아침이 되자 그는 달려와서 선술집을 돌려달라고 애원하며 뭐든지 하겠다고 약속했어요\n하지만 제가 그런 조건을 덥석 받아들일 만큼 어리석진 않죠. 그리고 그는 사라졌어요... 전 그가 이 일을 그냥 넘기지 않을 거란 걸 알았어요. 언젠가 돌아올 거란 예감이 들었죠. 그리고 이제, 그 날이 온 거예요.";
			link.l1 = "공은 인정해야지 – 그는 교묘하게 자기 계략을 실행했어.";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "잠깐만! 저 자가 어떻게 그 통에 대해 알게 된 거지? 이제야... 이제야 감이 오는군! 그 웨이트리스! 그래서 그 여자가 인사도 없이 혼비백산 도망쳤던 거야. 네가 잭을 처리했다는 소문을 들은 게 틀림없어. 이제야 모든 게 맞아떨어지는군. 선장님, 정말 말로 다 할 수 없이 감사하오, 그대는...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
