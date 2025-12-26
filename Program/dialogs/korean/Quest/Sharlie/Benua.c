int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "아들아, 다시 보니 반갑구나. 빚을 갚으러 온 것이냐?";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "예, 아버지. 그렇습니다.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "늦어서 미안하오, 하지만 그 일로 온 건 아니오. 하지만 곧 그렇게 될 테니, 걱정 마시오.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "무엇이든 필요한 것이 있느냐, 아들아?";
				link.l1 = "예, 아버지. 형님 미셸 드 몽페르를 뵙고 싶습니다. 그분이 말씀하시길...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "무슨 일로 왔느냐, 아들아?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua"))
			{
				dialog.text = "안녕하세요, 아들아. 와줘서 기쁘구나. 너와 이야기하고 싶었단다.";
				link.l1 = ""+TimeGreeting()+" 신부님, 말씀하십시오.";
				link.l1.go = "SharlieEpilog_Benua_1";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_back"))
			{
				link.l99 = "제 아버지에 대해 이야기하고 싶습니다.";
				link.l99.go = "SharlieEpilog_Benua_3";
			}
			//<-- Эпилог
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "예, 아버지. 도움이 필요합니다. 제 이름은 "+GetFullName(pchar)+". 미셸 드 몽페르가 당신과 이야기하라고 내게 조언했소.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "네, 아버지. 도움이 필요합니다. 제 이름은 "+GetFullName(pchar)+". 형 미셸 드 몽페르가 당신과 이야기하라고 조언했소.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "예, 신부님. 미셸을 도우려면 배가 필요한데, 저는 이제 막 카리브에 도착했고 지갑도 비었습니다. 형이 신부님께서 돈을 좀 빌려주실 수 있다고 하더군요...";
				link.l1.go = "FastStart_2";
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua"))
			{
				link.l1 = "안녕하십니까, 아버지. 다소 특이한 일로 도움을 청하고자 합니다.";
				link.l1.go = "WildRose_Abb_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2") && PCharDublonsTotal() >= 800)
			{
				link.l3 = "아버지, 필요한 금액을 모았습니다. 금화 800입니다.";
				link.l3.go = "WildRose_Abb_14_pay";
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3"))
			{
				dialog.text = "안녕하냐, 아들아. 네... 흠, 그 일의 결과를 들으러 온 것이겠지?";
				link.l1 = "여전히 통찰력이 대단하시군요, 아버지. 더 이상 기다리게 하지 마시고, 말씀해 주십시오. 아버지의 사람이 무엇을 알아냈습니까?";
				link.l1.go = "WildRose_Abb_16";
				break;
			}
			//<-- Дикая Роза
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "네, 아버지. 도움이 필요합니다.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "예, 아버지. 그렇습니다.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "아니요, 아무것도 아닙니다, 아버지.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "무슨 일로 나를 찾아왔느냐, 아들아?";
			link.l1 = "안녕하세요, 아버지. 당신과 이야기하라고 들었습니다. 제 이름은 샤를 드 모르입니다. 미셸 드 몽페르를 찾고 있습니다. 제가 알기로 그는 마르티니크 어딘가에 있을 텐데요. 저는... 그의 동생입니다.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "미셸 드 몽페르의 동생? 드 모르? 참 이상하군...";
			link.l1 = "아버지, 의심하시는 건 이해합니다. 우리는 단지 성이 다를 뿐입니다. 제 아버지는 앙리 드 몽페르입니다.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "아-아, 이제 알겠군. 나는 예전에 앙리 드 몽페르를 직접 알았지. 빛 쪽으로 몸을 돌리게, 젊은이. 그래! 정말 그와 똑같이 생겼군. 그 고귀한 이목구비까지! 우리 본당에서 앙리 드 몽페르의 아들을 만나게 되어 기쁘네.\n자네가 물은 것에 대해 말하자면, 미셸은 몰타 기사단의 고위 장교이지만... 곤경에 처해 있네. 다행히도, 기사단의 기사 한 명이 지금 나를 방문 중이야. 그가 자네를 불운한 형에게—주님께서 그의 운명을 불쌍히 여기시길—데려다주는 데 동의할지도 모르네...";
			link.l1 = "이 사람이 누구입니까, 신부님?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "아들아, 내일 아침에 다시 오너라. 지금은 더 할 말이 없구나.";
			link.l1 = "좋아.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "안녕하구나, 아들아. 약속한 대로, 내가 어제 말한 사람이 이미 여기 와서 너를 기다리고 있다. 그는 네 형에게 데려갈 준비가 되어 있지. 내가 들은 바로는, 형이 참으로 비참한 상태라 하더구나. 주님께서 그의 영혼을 불쌍히 여기시길 바라노라...\n";
			link.l1 = "이 사람이 누구입니까, 신부님?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "그래, 샤를, 나도 그건 알고 있네. 하지만 실망시켜야겠군. 미셸은 여기 없어.";
			link.l1 = "그가 여기 없다는 게 무슨 말입니까? 저를 교회에서 기다리겠다고 했잖아요! 신부님, 무슨 일이 있었던 겁니까? 제 형은 어디에 있죠?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "아들아, 네 형이 여기 왔다가 어젯밤 늦게 내 소박한 집을 떠났단다.\n어디로 갔는지는 모르겠구나. 하지만 너에게 이 편지를 남기고 갔어.";
			link.l1 = "믿을 수가 없어... 내가 그놈을 위해 얼마나 했는데! 그 편지 내놔!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "그렇게 분노하지 마시오, 샤를. 여기 편지가 있소. 읽어보시오, 그리고 나서... 그 다음에 당신과 이야기하고 싶소. 하지만 먼저, 형제의 메시지를 읽으시오.";
			link.l1 = "나는 참을 수 없을 만큼 조급해지고 있어!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "편지를 읽었군. 이제 너에게 할 말이 있네, 샤를르...";
				link.l1 = "하지만... 그럴 수가 있나? 이게 무슨 허튼소리야? 내 형이 별난 건 알지만, 미친 사람은 아니라고!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "아들아, 편지를 읽어라. 나중에 이야기하자.";
				link.l1 = "네, 아버지...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "네 형의 행동은 나 역시 놀라게 했소, 샤를. 아직도 당혹스러운 순간들이 있소. 기사단과 삼위일체의 충직한 종복이던 그가, 지금은 탈영병처럼 행동하고 있으니 말이오.";
			link.l1 = "그렇게 이상한 행동을 하는 이유가 무엇인지 짐작가는 바가 있소?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "유감이지만, 나는 몰라. 하지만 그에게는 나름의 동기, 아주 깊은 동기가 있을 거라 생각해. 자신의 모든 과거를 부정한다는 건 정말 중대한 이유가 있다는 뜻이지. 그게 뭔지 상상조차 할 수 없어. 하지만 뭔가 굉장히 나쁜 일, 아니 끔찍한 일이 관련되어 있다는 느낌이 들어...";
			link.l1 = "무엇입니까, 아버지?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "아들아, 신부는 눈이 아니라 마음으로 보는 법이다. 말로는 설명할 수 없지만... 네 형이 뭔가 더럽고 사악한 일을 하러 나섰구나. 내 입으로 이런 말을 하게 될 줄은 몰랐다. 하지만...";
			link.l1 = "글쎄, 내 형이 뭔가 음흉한 일을 꾸미고 있다는 건 의심하지 않아. 그가 뭘 하려는지도 짐작할 수 있지. 그 '무언가'는 노랗고, 듣기 좋은 짤랑거리는 소리를 내거든.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "네 형제를 움직이는 건 금에 대한 욕망이 아닌 것 같소. 내 생각엔, 그는 그보다 더 큰 무언가가 필요한 듯하오.";
			link.l1 = "나는 미셸에게서 많은 것을 배웠고 그의 철학도 이해하게 되었으니, 그에게 무엇이 중요하고 무엇이 중요하지 않은지 분별할 수 있다고 생각합니다. 하지만 아버지의 귀한 말씀도 마음에 새기겠습니다.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "신의 가호가 있기를, 아들아. 어서 가거라, 어서. 주님께서 너를 지켜주시길!";
			link.l1 = "감사합니다, 아버지. 안녕히 계십시오!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "미셸 드 몽페르의 동생? 드 모르? 이상하군...";
			link.l1 = "아버지, 의심하시는 건 이해합니다. 우리는 단지 성이 다를 뿐입니다. 제 아버지는 앙리 드 몽페르입니다.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "아-아, 이제 알겠군. 나는 앙리 드 몽페르를 직접 알았소. 빛을 향해 고개를 들어보게, 젊은이... 그래! 자네는 그와 똑같이 생겼군. 이목구비도, 귀족다운 모습도 똑같아! 우리 교구에서 앙리 드 몽페르의 아들을 만나게 되어 기쁘오.\n미셸이 유럽에서 온 남자의 방문을 받았다는 소문은 이미 들었지만, 그가 친형제일 줄은 상상도 못했소. 자네가 미셸을 도와줄 수 있길 바라오, 지금 그 친구는 힘든 시기를 겪고 있거든. 아무튼, 내가 무엇을 도와주면 되겠소?";
			link.l1 = "미셸이 내가 관청과 문제가 생기면 당신이 도와줄 수 있다고 말했어.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "미셸이 그렇게 말했소? 알겠소. 이런 문제라면 내가 도와줄 수 있소. 나는 신성 로마 교회와 네덜란드 식민지에 어느 정도 영향력이 있소. 그러니 스페인과 네덜란드 당국 사이에서 중재할 수도 있을 것이오. 물론, 자네의 과실이 너무 심각하다면 내가 할 수 있는 일은 많지 않으니, 그럴 경우엔 약간의 완화만 가능하오. 완전한 화해를 위해서는 여러 번의 중재가 필요할 것이오. 게다가 어떤 경우든 자네는 자선과 항해 경비 명목으로 나에게 금화 두블룬을 제공해야 하오. 또, 한 번에 한 나라만 도와줄 수 있소. 이 조건이 괜찮다면 언제든 나를 찾아오시오. 그럼 무엇을 할 수 있을지 함께 알아보도록 하지.";
			link.l1 = "고마워! 명심할게.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "무슨 일로 왔느냐, 아들아? 말해 보아라, 듣고 있노라.";
			link.l1 = "미셸이 내가 당국과 문제가 생기면 당신이 도와줄 수 있을 거라고 말했어.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "무엇을 도와줄까, 아들아?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater"))
			{
				link.l1 = "명령 전달에 대한 보수 문제로 다시 돌아가죠.";
				link.l1.go = "SharlieEpilog_Benua_DublonsLater_2";
			}
			if (CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				link.l1 = "명령을 보내고 싶습니다...";
				link.l1.go = "SharlieEpilog_Benua_Delivery";
			}
			//<-- Эпилог
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "스페인 당국과 문제가 생겼어.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "네덜란드 당국과 문제가 생겼어.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "미안하지만, 이번엔 내가 직접 처리할 생각이야.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "그래서 고귀한 나리들이 너를 아바나 감옥에 쳐넣고 싶어 안달이구나...";
			link.l1 = "그렇습니다, 아버지...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "그래서 그 영리한 상인들이 너를 윌렘스타드 감옥에 쳐넣으려고 안달이구나...";
			link.l1 = "그러하옵니다, 아버지...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "네, 그 소문은 우리 교회에도 이미 들려왔습니다. 당신의 고민을 도와드릴 수 있습니다. 해결할 수 있는 일이지요. 내가 필요로 하는 것은\n " + sTemp + " 당신의 곤경을 해결하기 위해서.";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "좋아! 여기 금이야.";
					link.l1.go = "agree";
				}
				link.l2 = "그렇다면 이제 내가 두블룬을 찾을 때로군.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "그래, 자네의 '무용담' 소문이 우리 교회에도 들려왔네. 자네 명성이 더럽혀졌구나, 아들아. 좀 더 신중해야 하네. 하지만 내가 도와줄 수 있지. 나는 필요하네\n " + sTemp + " 당신의 곤경을 수습하기 위해서요.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "좋아! 여기 금이야.";
						link.l1.go = "agree";
					}
					link.l2 = "그럼 이제 내가 두블룬을 찾을 때로군.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "그래, 아들아. 너도 네 형만큼이나 절박하구나... 아마 이건 우리 집안의 특징인 듯하다. 내가 상황을 완전히 바로잡을 수는 없지만, 그래도 네 암담한 처지를 조금은 덜어줄 수 있을 것 같구나. 그리고 원한다면 나중에 더 많은 제물을 바칠 수도 있지. 나는\n " + sTemp + " 일단 지금은 내가 곧바로 당신의 문제를 해결하기 시작하겠소.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "좋아! 여기 금이야.";
						link.l1.go = "agree";
					}
					link.l2 = "그렇다면 내가 지금이야말로 두블룬을 찾을 때군.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "이제 최소한 2주는 기다려야 하오. 그동안 내가 적절한 사람들을 만나 이야기할 수 있을 것 같소.";
			link.l1 = "감사합니다, 아버지! 기다리고 있겠습니다...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "드 모르? 그리고 자네가 미셸 드 몽페르의 동생이라고? 이상하군...";
			link.l1 = "의심이 드는 것도 이해합니다, 신부님. 제 아버지는 앙리 드 몽페르입니다.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "아-아, 알겠네. 나는 앙리 드 몽페르를 직접 알았지. 이리로 나오게, 젊은이. 그래! 눈매도 같고, 귀족다운 얼굴도 똑같군! 앙리 드 몽페르의 아들이 내 교회에 와줘서 기쁘네. 자네가 형을 도울 수 있길 바라네. 최근에 그 친구는 운이 참 없었거든.";
			link.l1 = "예, 신부님. 미셸을 도우려면 배가 필요하지만, 저는 이제 막 카리브에 도착했고 지갑도 텅 비었습니다. 형이 신부님께서 돈을 좀 빌려주실 수 있다고 하더군요...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "미셸이 그렇게 말했어?";
			link.l1 = "신부님, 제가 그리 믿음직스럽게 들리지 않을 수도 있지만, 사실입니다. 제가 배를 구하는 대로 형을 감옥에서 꺼낼 수 있으니, 최대한 빨리 배가 필요합니다.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "알겠다, 아들아. 네가 진실을 말하고 있다는 걸 알 수 있구나. 좋아, 미셸과 네 아버지를 위해 내가 도와주겠다. 약간의 저축이 있으니 가져가거라. 5만 페소와 100 두블룬이면 충분하겠지.";
			link.l1 = "감사합니다, 신부님. 조건이 무엇입니까?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "압박은 없어. 갚는 데 반년이면 충분해.";
			link.l1 = "아주 좋소, 신부님. 다시 한 번 감사하오!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "내 축복과 함께 가거라, 아들아.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "훌륭하구나, 아들아. 그 돈이 너에게 도움이 되었기를 바란다.";
			link.l1 = "정말 그랬소! 고맙소!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "샤를, 내 눈을 의심하겠군! 여긴 어쩐 일이오?!";
			link.l1 = "축복해 주십시오, 거룩하신 신부님. 좋은 소식을 전하러 왔습니다 - 제가 결혼하게 되었으니, 제 결혼식 주례를 맡아 주셨으면 합니다.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "아들아, 정말 훌륭하구나! 네가 아버지에게서 그 편지를 받고는, 언제나 그렇듯 네 생각대로 행동하기로 한 것이냐? 진심으로 기쁘구나! 하지만 네가 이 교회에서 결혼하기로 결심하지 않는 한, 내가 도와줄 수는 없을 것 같구나.";
			link.l1 = "성부님, 임무가 교착 상태에 빠진 것으로 이해합니다. 제가 도울 일이 있을까요? 결혼식이 스페인 예배당에서 열린다면 물론 흥미로운 모험이 되겠지만, 저는 반드시 마르티니크에서 축하 연회를 열고자 합니다.\n적당히 화려하게, 그리고 명망 있는 증인들과 존경받는 손님들 앞에서 말이지요.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "미안하구나, 아들아. 그러나 네 모든 권위도 가톨릭 교회의 최고 성직자들의 완고함 앞에서는 아무 소용이 없단다, 특히 스페인 식민지에서는 더더욱 그렇지. 우리 나라들 사이에서 가톨릭 선교의 영향력 분할 문제에 대해 아직 합의하지 못했고, 그래서 나는 지금 이곳에 명예로운 손님이자 명예로운 인질로 와 있단다. 스페인인들은 우리 쪽에서 더 나은 제안을 기다리고 있어. 나는 유럽에 서신을 보냈으니, 답장이 두 달 안에 오길 바라며, 그때쯤이면 협상을 재개할 수 있을 거다. 만약 두 달 안에 오지 않더라도, 적어도 여섯 달 안에는 반드시 도착할 거야.\n그리고 그래, 최근 몇 주 사이 교황과 마자랭이 타협을 이루긴 했지만, 진정으로 우호적인 관계를 논하기엔 아직 이르다. 솔직히 말해, 우리가 과연 어떤 합의에 이를 수 있을지 나도 잘 모르겠구나. 내 생각엔 팔로티가 그저 자기 정치적 권력 싸움에서 나를 흥정 카드로 붙잡아 두는 것 같아. 하지만 한 가지 말해야겠구나, 그 종교재판관의 커피는 정말 훌륭하단다!";
			link.l1 = "나는 여섯 달도, 두 달도 없어! 아버지의 뜻을 이루지 못하면, 아버지는 내 의지와 상관없이 결혼을 강요하실 거야. 그리고 아버지의 건강도 예전 같지 않은데, 그래도 내가 고른 사람과 미래의 몽페르 부인을 아버지께 소개할 시간쯤은 갖고 싶어.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "유감이지만, 그럼 네 결혼식에는 다른 신부를 찾아야겠구나, 아들아. 안타깝게도 나는 여기 오래 머물러야 하니.";
			link.l1 = "내가 그 심문관의 커피 자리에서 당신을 데려간다면 뭐라고 하겠소?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "기꺼이 당신의 도움을 받아들이겠소. 내가 이 임무에 우연히 선택된 것은 아니라고 생각하오. 최악의 경우, 그들은 베누아 신부를 그냥 잊어버릴 것이오. 그리고 주께서 인내하라 명하셨으나, 모든... 축복에도 불구하고 내 결론이 무겁게 느껴지오. 하지만 다시 말하오 - 팔로티 신부가 당신의 부탁을 들어줄 가능성은 적소.";
			link.l1 = "그럼 시간 낭비하지 않고 설득도 시도하지 않겠소. 예배가 끝나는 대로 바로 교회를 떠나 내 배로 곧장 가겠소. 망설이지 마시오, 신부님 – 저들이 우리 만남을 봤으니 나를 알아볼 것이오, 내가 총독 저택에서 신부님을 빼내야 한다면 훨씬 더 도와드리기 어려울 것이오.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "위험하구나, 아들아, 매우 위험하다. 밖에는 경비병들이 나를 저택까지 호위하려고 기다리고 있고, 도시는 병사들로 가득하다.";
			link.l1 = "기습으로 가겠습니다, 베누아 신부님. 저를 믿기만 하시면 모든 게 잘 될 겁니다. 이런 일에는... 약간 경험이 있으니까요.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "원하시는 대로 하십시오. 하지만 제발, 불필요한 유혈 사태는 피해주세요! 저도 이런 경험이 좀 있어서요... 우리를 이끄시오, 아들아. 내가 바로 뒤따르겠소. 하지만 무기는 들지 않을 것이니, 그 점은 묻지도 마시오.";
			link.l1 = "생각도 안 했어요, 아버지. 제가 할 수 있습니다. 저를 따라오시되 조심하세요, 우리에게 총을 쏠 수도 있으니까요.";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "아들아, 내 석방에 대해 감사 인사를 할 시간이 없었구나. \n스페인 주교와 종교재판관 팔로티가 우리 추기경과 교황청 사이에 새로 맺어진 관계를 방해하려 했던 모양이니, 너는 오로지 우리 나라의 이익을 위해 행동한 셈이야. 또 한 번 말이지. \n하지만 나 말고는 아무도 '고맙다'고 하지 않을 거다.";
			link.l1 = "흔한 일입니다, 신부님. 도와드릴 수 있어서 기쁩니다. 그런데 저도 여쭤볼 게 있지 않습니까, 기억하시죠?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "물론이지! 그럼 즐거운 일부터 시작하세. 샤를, 자네의 가장 중요한 날을 위한 준비는 어떻게 되어가고 있나?";
			link.l1 = "서서히 형태를 갖추고 있군. 내가 아는 군사 작전들도 이보다 더 쉽고 빠르게 준비됐었지만, 그래도 이건 그만한 가치가 있어!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "물론이지, 아들아! 그리고 이 기회에 한 가지 분명히 하고 싶구나 – 너는 결혼식을 어떻게 상상하고 있느냐?";
			link.l1 = "얼마나 거만하냐고?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "물론이오! 내가 교회를 준비해야 하니, 자네도 혹시 중요한 사람들을 초대하고 싶을 수도 있겠지.";
			link.l1 = "특별한 일은 없습니다, 교황님. 제가 우리 친구라 여기는 이들은 다른 곳에서 우리를 기다릴 것입니다. 여기에는 몇몇 관리들과 제 부하들, 그리고 평범한 구경꾼들만 있을 뿐입니다.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "그렇다면, 작은 기부 정도면 충분할 것 같군.";
			link.l1 = "그다지 무서운 얘기는 아니군. 그런데 그런 기부금이 금으로 얼마지?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "성가대, 엄숙한 예배, 그리고 기타 비용으로는 백오십 두블룬, 그 이상은 안 됩니다.\n거기에 신혼부부가 내는 통상적인 헌금까지 합치면, 총 이백 두블룬입니다.";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "여기 있습니다, 신부님.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "그 군사 작전에 관해서라면... 은행까지 걸어갔다가 돌아와야겠군.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "너의 헌금은 어떻게 할 것이냐, 아들아?";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "여기 있습니다, 신부님.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "그래, 그래, 곧 가져올게...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "아직 답해야 할 질문이 하나 남아 있소 - 신부를 인도하고 그녀를 대신해 혼인에 증인이 될 사람은 누구요?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "블루웰드에서 온 얀 스벤손. 그는 영국인이지만 존경받는 인물이며 헬렌을 마치 자신의 딸처럼 아끼고, 헬렌의 양어머니는 글래디스 맥아더다.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "노엘 포르게 나리, 분명 저에게 영광을 베풀어 주실 거라 믿습니다.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "필리프 드 푸앵시 기사 나리, 분명 저에게 영광을 베풀어 주실 겁니다.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "그래, 그럼 신랑을 위해 증언할 사람은 누구요? 기억하시오, 반드시 고귀한 혈통과 훌륭한 평판을 가진 남자여야 하오.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "노엘 포르게 나리, 분명 저에게 영광을 베풀어 주실 것이오.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "필리프 드 푸앵시 기사 나리, 분명 저에게 영광을 베풀어 주실 것이라 확신합니다.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "파데이는 과들루프 출신의 존경받는 상인이야. 나는 그가 가장 좋아하는 술만 챙기면 돼.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "파데이는 과들루프에서 온 존경받는 상인이야. 나는 그의 가장 좋아하는 술만 좀 챙기면 돼.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "좋소, 내가 초대장을 보낼 테니 손님들이 도착하려면 시간이 좀 걸릴 것이오.\n한 달이면 모든 준비가 끝나고, 지정된 인물들도 도시에 도착해 있을 것이오.";
			link.l1 = "좋아! 그럼 몇 가지 볼일을 볼 시간이 있겠군. 곧 뵙겠소, 신부님, 그리고 행운을 빌어 주시오!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "좋습니다, 내가 초대장을 보낼 테니, 손님들이 도착하려면 시간이 좀 걸릴 거요. 한 달이면 모든 준비가 끝나고, 초대받은 이들도 도시에 도착해 있을 것이오.";
			link.l1 = "좋아! 그럼 볼일 몇 가지를 볼 시간이 있겠군. 곧 뵙겠소, 신부님, 그리고 행운을 빌어 주시오!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "좋습니다, 초대장을 보내겠지만, 손님들이 여기까지 오는 데 시간이 좀 걸릴 겁니다. 한 달쯤이면 모든 준비가 끝나고, 지정된 인물들도 도시에 도착해 있을 거라 생각합니다.";
			link.l1 = "좋아요! 그럼 볼일 몇 가지를 볼 시간이 있겠군요. 곧 뵙겠습니다, 신부님, 그리고 행운을 빌어 주십시오!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "그래, 그 날이 왔구나, 아들아! 모든 준비가 끝났다네 – 두어 시간만 지나면 시작할 수 있을 것이야. 얼굴이 창백해 보이는구나!";
			link.l1 = "조금 긴장됩니다, 신부님.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "흔한 일이네. 오늘은 자네 인생에서 가장 중요한 날이니, 나뿐만 아니라 여기 온 모두가 진심으로 기뻐하고 있네. 최소한 기본 기도문은 기억하고 있겠지? 자네가 교회에 얼굴을 자주 비춘 적은 없으니 말일세. 그래도, 어떤 경우든 내가 도와주겠네.\n그리고 한 가지 더 – 내가 알기로는 신부가 자신의 신념을 굽히지 않을 모양이니, 우리가 드레스를 입은 그녀를 볼 일은 없겠군? 뭐, 상류사회가 또 한 번 자네의 깜짝 놀랄 만한 모습을 보게 되겠어 – 자네는 정말 놀라움이 가득하지. 아무튼, 가거라, 아들아, 단정하게 준비하고 오면 시작하겠네.";
			link.l1 = "예, 교황님. 시작합시다.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "하늘에 계신 우리 아버지, 아버지의 이름이 거룩히 여김을 받으시며, ad...";
			link.l1 = "...adveniat regnum tuum";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...requiem aeternam dona eis";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "...뜻이 하늘에서 이루어진 것 같이 땅에서도 이루어지이다. 오늘 우리에게 일용할 양식을 주시고, 우리가 우리에게 죄 지은 자를 사하여 준 것 같이 우리 죄를 사하여 주시고...";
			link.l1 = "...우리에게 빚진 자들을 우리가 용서하듯이";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...처음과 같이, 이제와 항상, 영원무궁토록. 아멘";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "으, 으음...";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "으, 으음...";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "우리들을 유혹에 들지 않게 하시고, 다만 악에서 구하소서. 아멘.";
			link.l1 = "아멘.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "사랑하는 여러분, 우리는 하나님의 면전과 이 모인 회중 앞에서 이 남자와 여자를 거룩한 혼인으로 맺기 위해 함께 모였습니다. 사랑하는 여러분 "+sld.name+" 그리고 샤를, 그대는 하나님의 말씀을 들었고, 그분께서 인간의 사랑과 혼인의 의미를 일깨워 주셨소. 이제, 성스러운 교회를 대표하여 그대의 의도를 묻고자 하오.\n"+sld.name+" 그리고 샤를, 주님 앞에서 자발적이고 진실된 마음으로 혼인하길 원하시오?";
			link.l1 = "그래.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "건강할 때나 아플 때나, 기쁠 때나 슬플 때나, 평생 서로에게 충실할 것을 맹세하겠습니까?";
			link.l1 = "그래.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "주님께서 그대에게 보내실 자녀들을 사랑하고 받아들이며, 그들을 기독교 신앙 안에서 키울 것을 약속하십니까?";
			link.l1 = "그래.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "자, 서로를 바라보고 맹세를 하시오.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "여기 모인 분들 중 이 두 사람이 성스러운 혼인으로 맺어져서는 안 될 이유를 아는 이가 있다면, 지금 말씀하시고, 그렇지 않으면 영원히 침묵하시기 바랍니다.\n이로써, 주님과 이 자리에 모인 모든 이들 앞에서, 나는 두 분을 부부로 선포합니다! 성부와 성자와 성령의 이름으로. 아멘.";
			link.l1 = "아멘.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Whispering) Charles, my son, just move your lips, I beg you - don't try to make any sound...";
			else sTemp = "";
			dialog.text = "신혼부부여, 함께 무릎 꿇고 기도하시오. Oratio fidelium. "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "축하하네, 아들아. 네 아버지도 자랑스러워하실 것이고, 나 역시 자랑스럽네. 이 힘든 시기에 서로 아끼고 행복하게 지내게나.";
			link.l1 = "감사합니다, 신부님. 훌륭한 미사였고, 신부님께서 집전해 주셔서 기쁩니다.";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "그래서 나에게 조언을 구하러 온 것이냐, 내 자식들아?\n좋다, 다 들어주마.";
			link.l1 = "도움이 필요해서입니다, 아버지. 인맥이 넓고 온갖 사람을 아는 분의 도움이요...";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "방해해서 미안하구나, 아들아. 하지만 나는 그저 겸손한 수도원장일 뿐, 무슨 비밀 요원이 아니라는 것을 상기시켜야겠구나.";
			link.l1 = "하지만 겸손한 수도원장도 비밀 요원을 알 수도 있지 않겠소? 아니면 최소한 그를 어떻게 만날 수 있는지 조언해 줄 수도 있지 않겠소?";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "우리를 이곳으로 이끈 일은 정말로 오랫동안 잊혀진 비밀들과 관련되어 있소... 우리는 그저 그 비밀들을 다시 세상 밖으로 끌어내려 할 뿐이오.";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "이봐, 젊은이, 이건 마음에 들지 않는군. 본론만 말하게. 그래야 내가 어떻게, 아니면 정말 도와줄 수 있을지 알겠네.";
			link.l1 = "네, 아버지. 간단히 말씀드리겠습니다...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = ""+pchar.name+", 수수께끼처럼 말하지 마시오 – 솔직히 말해 지치오.";
			link.l1 = "예, 아버지. 간단히 말씀드리겠습니다...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "가거라, 아들아.";
			link.l1 = "내 동료 메리 캐스퍼는 아버지를 찾고 있어 – 아니면 적어도 그에 대한 어떤 단서라도 말이야. 우리는 그녀의 아버지가 영국 해군의 장교였고, 1638년에 케이프 카토체에서 난파된 브리그선 '랭글러'에 탑승해 있었다는 사실을 알아냈지.";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "그런데도 아직 그가 살아 있기를 바라는 것이오? 그렇게 많은 세월이 지났는데?";
			link.l1 = "그가 난파에서 살아남지 못했다 해도, 메리는 아버지가 어디 출신인지, 어떤 사람이었는지, 어떤 삶을 살았는지 알고 싶어하오... 공식 문서에는 자세한 내용이 거의 없지만, 그 안에서도 가치 있는 무언가를 찾을 수 있지 않겠소, 신부님?";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "네 이론이 옳구나, 아들아. 네가 하려는 일은 선하고 신실한 일이다. 하지만 아직도 내가 무엇을 기대하는지 정확히는 모르겠구나.";
			link.l1 = "신부님께서는 오래도록 이 제도에 머무르셨지요. 혹시 영국 해군 장교들에 관한 식민지 기록에 접근할 수 있는 사람을 아십니까?";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "영국 해군 장교들의 기록이 보관된 식민지 기록 보관소에 접근할 수 있는 사람이 필요하오. 신부님, 분명 그런 사람을 알고 계시겠지요.";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "무엇을 묻고 있는지 이해하느냐, 아들아?\n문제는 단순히 그런 정보가 군사 기밀일 수도 있다는 것만이 아니란다...";
			link.l1 = "그리고 또 무엇입니까, 신부님? 솔직히 말씀드리겠습니다...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "무엇을 묻고 있는지 이해하느냐, 아들아?\n문제는 그 정보가 단순히 군사 기밀일 수도 있다는 데에만 있지 않다...";
			link.l1 = "그리고 또 무엇입니까, 신부님? 솔직히 말씀드리겠습니다...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_9":
			dialog.text = "문제는 바로 그 식민지 기록들에 있소. 이십 년 전만 해도 자메이카는 스페인령이었고, 세인트존스와 브리지타운은 끊임없이 습격 위협에 시달렸지. 그곳에 왕립 해군 함선이 주둔했을 가능성은 희박하오...";
			link.l1 = "아버지, 런던에 있는 해군성 기록 보관소를 말씀하시는 건가요?";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "아마도. 서류는 해군성으로 보내졌어야 했지. 그것들을 얻는 건 쉽지 않을 거야.";
			link.l1 = "하지만 할 수는 있지요, 아버지?";
			link.l1.go = "WildRose_Abb_11";
		break;

		case "WildRose_Abb_11":
			dialog.text = "불가능한 일은 없단다, 아들아. 하지만 노력과... 대가가 필요할 것이야.";
			link.l1 = "물론입니다, 아버지. 돈을 아버지께 드리면 되겠습니까, 아니면 다른 사람을 만나야 합니까?";
			link.l1.go = "WildRose_Abb_12";
		break;

		case "WildRose_Abb_12":
			dialog.text = "나는 직접 다른 사람을 만나겠네, 아들아. 내가 너에게 필요한 것은... 800두블룬이네.";
			link.l1 = "알겠습니다, 아버지. 얼마나 걸릴까요?";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "두 달쯤 걸릴 것 같군. 그런데, 그나저나 자네가 찾는 이의 이름을 아직 말하지 않았네.";
			link.l1 = "저자의 이름은 Joshua Casper야.";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "명심하겠소. 지금 전액을 내놓을 준비가 되어 있다면 — 내일이라도 바로 소식을 보내겠소.";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "물론이지, 아버지. 여기요, 받으십시오. 금화 800입니다.";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			link.l2 = "아니오, 아버지, 저에게 그런 돈은 없습니다. 하지만 곧 돌아와서 가져오겠습니다.";
			link.l2.go = "WildRose_Abb_14_nopay";
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "좋소, "+pchar.name+". 두 달 후에 다시 오시오 – 그때쯤이면 분명 어떤 식으로든 답을 드릴 수 있을 것이오.";
			link.l1 = "감사합니다, 신부님. 다시 만날 때까지 안녕히 계십시오!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "그렇소, 아들아.";
			link.l1 = "곧 돌아오겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;
		
		case "WildRose_Abb_16":
			dialog.text = "그는 조슈아 캐스퍼와 그의 배에 대해 모두 알게 되었으나, 그 배는 '랭글러'가 아니었다. \n그런 이름의 브리그는 왕립 해군에 소속된 적이 한 번도 없었다.";
			link.l1 = "흠... 조슈아 캐스퍼가 탔던 배가 분명 그 이름이었지. 그럼 조슈아 본인은 어떻게 됐나?";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;

		case "WildRose_Abb_17":
			dialog.text = "그 사람은 많은 공적과 훈장을 지닌 훌륭한 장교였소 – 모든 것이 그의 인사기록에 남아 있지. 비록 진정한 신앙을 따르진 않았으나, 그는 존경받을 만한 선장이었소. 아가씨께서는 그런 혈통을 자랑스럽게 여겨도 되겠구려.";
			link.l1 = "좋은 소식이로군요, 아버지. 하지만 허락하신다면, 배로 돌아가도록 하지요. '랭글러'가 아니었다면, 그 배 이름이 무엇이었습니까?";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = "'Cornwall'. 그는 1638년 1월에 플리머스에서 출항하여 앤티가와 프로비던스 주둔군에게 급여를 전달하라는 명령을 받았소.";
			link.l1 = "믿을 수가 없군...";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "그 배가 최종 목적지에 도달했는지는 모르겠소. 하지만 세인트 존스에는 들렀지. 항구 사무소에는 그 해 6월 2일자로 작성된 캐스퍼 선장의 보고서가 남아 있소.";
			link.l1 = "아버지, 당신이 겉으로 보이려는 것만큼 단순한 분이 아니라는 건 알고 있었어요! 이 문서에 중요한 내용이 들어 있는 거죠?";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "우리는 영원히 신부님께 빚을 졌습니다. \n방금 그 문서를 언급하셨으니, 뭔가 중요한 내용이 담겨 있는 게 맞습니까?";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "아조레스 근처에서 스페인 갤리온 '토로'와의 전투 보고서뿐이오. 그 전투에서 선원 3분의 1이 목숨을 잃었지 – 보고서를 읽어보시오, 모든 내용이 나와 있소.";
			link.l1 = "질문이 하나 더 있소: 앤티과 항만 당국의 기록을 열람했다면, 혹시 조슈아 캐스퍼의 이름을 다른 곳에서도 본 적이 있소?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "아조레스 근처에서 스페인 갈레온 '토로'와의 전투 보고서뿐이네. 그 전투에서 승무원의 3분의 1이 목숨을 잃었지 – 보고서를 읽어 보게, 모든 내용이 거기 나와 있네.";
			link.l1 = "질문이 하나 더 있소: 앤티과 항만 당국의 기록을 열람했다면, 혹시 조슈아 캐스퍼의 이름을 다른 곳에서도 본 적이 있소?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "너는 내게 많은 것을 요구하는구나, 아들아. 그가 그 난파선에서 살아남아 나중에 함대로 돌아왔을지도 모른다고 말하려는 것이라면, 나는 그럴 가능성이 매우 낮다고 생각한다.";
			link.l1 = "신의 뜻은 참으로 오묘하군요, 신부님.";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "그렇다네, 아들아. 하지만 말이지, 그의 인적 기록에 따르면 조슈아 캐스퍼는 1586년에 태어났다고 되어 있네...";
			link.l1 = "아버지, 어쩌면 아버지 말씀이 옳으실지도 모르겠습니다.";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "아시겠지만, 아버지, 제가 카리브에서 지낸 세월 동안 정말 기상천외한 일들을 많이 봐서, 아무리 믿기 힘든 이야기라도 믿을 수 있을 것 같습니다.";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "분명 저런 장교라면 전장에서 죽을 자격이 있었지. 하지만 철학적으로 말하자면, 그것 또한 일종의 전투였다고 할 수 있겠군...";
			link.l1 = "저는 철학자가 아니오, 신부님. 하지만 모든 것에 감사드립니다...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "틀림없이 그런 장교라면 전장에서 죽을 자격이 있었지. \n하지만 철학적으로 말하자면, 그것 또한 일종의 전투였다고 할 수 있겠군...";
			link.l1 = "저는 철학자가 아니오, 신부님. 하지만 모든 것에 감사드립니다...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "주님께서 너희를 이 길로 인도하신다, 내 아이들아. 그리고 너희를 돕는 것이 내 미천한 의무이니라. 하지만 이 일에 있어 내가 더 이상 해줄 수 있는 것이 없을까 두렵구나...";
			link.l1 = "알겠습니다, 아버지. 그럼, 저희는 이만 물러가겠습니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		//--> Эпилог
		case "SharlieEpilog_Benua_1":
			dialog.text = "너의 아버지의 상태에 대해 매우 걱정하고 있다. 그가 편지에서 너에게 밝혔는지는 모르겠지만, 나에게 보낸 편지에서는 이렇게 말했다. 그의 육체는 점점 쇠약해지고 있으며, 오래 버티지 못할 것 같다고.";
			link.l1 = "병세가 나아지지 않고 있다고 언급했어요... 하지만 자신의 걱정은 말하지 않았던 것 같네요.";
			link.l1.go = "SharlieEpilog_Benua_2";
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua");
		break;

		case "SharlieEpilog_Benua_2":
			dialog.text = "더는 해줄 말이 없다 — 그가 말한 건 그게 전부야. 하지만 분명한 건 하나 있다: 그는 너를 다시 보지 못한 채 주님 앞에 나아가게 될까 두려워하고 있다.";
			link.l1 = "그가 그런 말을 했어요. 사실 나도 그를 찾아가 볼까 생각했지만... 하지만...";
			link.l1.go = "SharlieEpilog_Benua_3";
		break;

		case "SharlieEpilog_Benua_3":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_1"))
			{
				dialog.text = "아들아, 각자에게 주어진 시간이 얼마나 남았는지는 오직 주님만 아신다. 만남을 미루지 마라. 때로는 한 번의 포옹이 천 개의 기도보다도 큰 위안을 줄 수 있단다.";
				npchar.SharlieEpilog_BenuaRazgovor_1 = true;
			}
			else
			{
				dialog.text = ""+pchar.name+"야, 더 이상 그를 찾아가는 일을 미루지 않을 거라 믿는다. 시간은 너의 편이 아니란다...";
			}
			link.l1 = "말씀대로입니다, 아버지. 당장 출항 준비를 시작하겠습니다. 지금 내 입장을 고려하면 모든 걸 정리하는 데 시간이 좀 걸릴 수도 있겠지만...";
			link.l1.go = "SharlieEpilog_Benua_5";
			link.l2 = "염려하시는 건 이해합니다, 성부님. 약속드리죠, 깊이 고민해보겠습니다. 하지만 지금은 시급한 일들이 많아서... 이 대화는 나중에 다시 이어가죠.";
			link.l2.go = "SharlieEpilog_Benua_4_exit";
		break;

		case "SharlieEpilog_Benua_4_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_2");
		break;

		case "SharlieEpilog_Benua_5":
			dialog.text = "혹시 빚이 있다면, 아들아, 먼저 그 빚부터 갚는 것이 좋을 것이다. 고리대금업자란 복수를 잊지 않는 자들이다. 그들의 손에 네 명예뿐 아니라 가문의 이름까지도 더럽혀질 수 있다 — 심지어 구세계에서도.\n"+
			"기타 모든 일에 관해서는 — 너의 아버지와의 우정, 그리고 주님의 영광을 위해 — 내가 도울 수 있는 모든 것을 돕겠다. 서면으로 지시사항을 넘겨주면, 내가 그것을 제때 전달되게 하겠다. 너는 단지 배달료만 부담하면 된다. 모든 편지를 보내는 데는 200 두블론이면 충분할 것이다.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "감사합니다, 성부님. 정말 큰 도움이 됩니다. 자, 여기 있습니다.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "배려에 감사드립니다, 성부님. 하지만 지금은 그 금액이 없습니다. 이 문제는 나중에 다시 말씀드리겠습니다.";
			link.l2.go = "SharlieEpilog_Benua_DublonsLater";
			SharlieEpilog_Benua_Dlg_1();
		break;

		case "SharlieEpilog_Benua_DublonsLater":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_3");
		break;

		case "SharlieEpilog_Benua_DublonsLater_2":
			dialog.text = "그렇지, "+pchar.name+"야. 두블론 200개는 준비했겠지?";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "물론이죠. 여기 있습니다.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "죄송합니다. 아직은 준비되지 않았습니다.";
			link.l2.go = "exit";
		break;

		case "SharlieEpilog_Benua_6":
			dialog.text = "훌륭하다, 아들아.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			RemoveDublonsFromPCharTotal(200);
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater");
		break;
		
		case "SharlieEpilog_Benua_Delivery":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				dialog.text = "그럼, 어디서부터 시작하고 싶은가?";
				npchar.SharlieEpilog_BenuaRazgovor_2 = true;
			}
			else
			{
				dialog.text = "누구에게 무엇을 전하고 싶은가?";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona"))
			{
				link.l1 = "과거에 나는 지도에 없는 섬을 발견한 적이 있어요. 그곳엔 이미 몇몇 정착민들이 있었고, 나는 그들을 돌보고 있었죠. 내가 떠나는 지금, 그 섬엔 새로운 '총독'이 필요할 겁니다.";
				link.l1.go = "SharlieEpilog_Benua_IslaMona";
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Baron"))
			{
				link.l2 = "라 베가의 마르쿠스 티락스에게 편지를 보내고 싶습니다. 아주 중요한 일은 아니지만, 제때에 도착해야 할 편지입니다.";
				link.l2.go = "SharlieEpilog_Benua_Baron";
			}
			if (CheckCharacterItem(PChar, "patent_fra") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Patent"))
			{
				link.l3 = "프랑스의 유효한 특허장을 갖고 있어요. 이를 캡스터빌 관청에 통보하려 합니다.";
				link.l3.go = "SharlieEpilog_Benua_Patent";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Money"))
			{
				link.l4 = "성부님, 내가 이 땅에서 보낸 수년간 많은 자금을 축적했습니다. 하지만 가족에게 그것을 넘기기 전에, 그 돈에 얽힌 피를 정화하고 싶습니다. 나는 약탈자가 아닌, 명예롭고 양심적으로 떠나는 자로 기억되고 싶어요.";
				link.l4.go = "SharlieEpilog_Benua_Money";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Svenson") && CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona_France"))
			{
				link.l5 = "블루벨드의 얀 스벤손에게 내가 떠난다는 소식을 전하고 싶습니다. 작별 인사 없이 군도를 떠나는 것은 실례일 테니까요.";
				link.l5.go = "SharlieEpilog_Benua_Svenson";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Houk"))
			{
				link.l6 = "마룬타운의 호크 가문에게 내가 여행을 떠난다는 사실을 알리고 싶습니다.";
				link.l6.go = "SharlieEpilog_Benua_Houk";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Jino"))
			{
				link.l7 = "세인트존스의 지노 귀넬리에게 내가 구세계로 떠난다는 소식을 전하고 싶습니다.";
				link.l7.go = "SharlieEpilog_Benua_Jino";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_S") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_M") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_L"))
			{
				link.l85 = "이제 끝났군요, 성부님... 떠날 준비가 된 것 같습니다.";
				link.l85.go = "SharlieEpilog_Benua_TimeToGoHome";
			}
			link.l99 = "실례합니다, 성부님. 이만 가보겠습니다.";
			link.l99.go = "SharlieEpilog_exit";
		break;
		
		case "SharlieEpilog_exit":
			DialogExit();
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "First time";
		break;
		
		case "SharlieEpilog_Benua_Jino":
			dialog.text = "물론이지, 아들아.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Jino_2";
			pchar.questTemp.SharlieEpilog_Jino = true;
		break;

		case "SharlieEpilog_Benua_Jino_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Jino_3";
			AddQuestRecord("SharlieEpilog", "8_1");
		break;

		case "SharlieEpilog_Benua_Jino_3":
			dialog.text = "...";
			link.l1 = "완료됐습니다. 이제 발송하세요.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Houk":
			dialog.text = "물론이지, 아들아.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Houk_2";
			pchar.questTemp.SharlieEpilog_Houk = true;
		break;

		case "SharlieEpilog_Benua_Houk_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Houk_3";
			AddQuestRecord("SharlieEpilog", "8");
		break;

		case "SharlieEpilog_Benua_Houk_3":
			dialog.text = "...";
			link.l1 = "완료됐습니다. 이제 발송하세요.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Svenson":
			dialog.text = "블루벨드의 얀 스벤손... 기억하마. 편지를 내게 주면 오늘 중으로 발송하도록 하겠다.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Svenson_2";
			pchar.questTemp.SharlieEpilog_Svenson = true;
		break;

		case "SharlieEpilog_Benua_Svenson_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Svenson_3";
			AddQuestRecord("SharlieEpilog", "7");
		break;

		case "SharlieEpilog_Benua_Svenson_3":
			dialog.text = "...";
			link.l1 = "얀의 집은 쉽게 찾을 수 있습니다. 블루벨드에서 그를 모르는 사람은 거의 없을 겁니다.";
			link.l1.go = "SharlieEpilog_Benua_Svenson_4";
		break;

		case "SharlieEpilog_Benua_Svenson_4":
			dialog.text = "걱정 마라, 아들아. 우리의 사람들은 그 일에 익숙하다. 편지는 정확히 필요한 사람에게, 정시에 전달될 것이다.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money":
			dialog.text = "너는 교회가 범죄로 얻은 금을 축복해주길 바라는 것이냐?";
			link.l1 = "오히려, 그것은 프랑스와 폐하를 위해 봉사하며 얻은 것입니다.";
			link.l1.go = "SharlieEpilog_Benua_Money_2";
		break;

		case "SharlieEpilog_Benua_Money_2":
			dialog.text = "네 마음은 이해한다, 아들아. 교회는 돈을 정화하지 않으며 그것이 어떻게 얻어졌든 무효화하지 않는다. 하지만 이 말이 무슨 의미가 있겠는가? 굶주린 자는 계속 굶주리고, 집 없는 자는 거리에 남으며, 병든 자는 죽어간다. 나는 기꺼이 축복을 내리겠다. 단, 그 금액의 일부가 너 자신이 아닌, 도움이 필요한 사람들에게 쓰인다는 조건으로 말이다.";
			link.l1 = "물론입니다, 성부님. 얼마든지 기부할 준비가 되어 있습니다.";
			link.l1.go = "SharlieEpilog_Benua_Money_3";
		break;

		case "SharlieEpilog_Benua_Money_3":
			dialog.text = "그렇다면, 너는 얼마를 가지고 떠나고 싶은가?";
			link.l1 = "천만 페소.";
			link.l1.go = "SharlieEpilog_Benua_Money_4";
			if (sti(pchar.Money) >= 250000)
			{
				link.l2 = "이천오백만 페소.";
				link.l2.go = "SharlieEpilog_Benua_Money_5";
			}
			if (sti(pchar.Money) >= 500000)
			{
				link.l3 = "오천만 페소.";
				link.l3.go = "SharlieEpilog_Benua_Money_6";
			}
		break;
		
		case "SharlieEpilog_Benua_Money_4":
			dialog.text = "그렇다면 십만 페소의 기부로 충분할 것이다. 이 돈으로 우리는 수개월 동안 도움이 필요한 이들에게 식사를 제공할 수 있다. 지금 바로 이 금액을 낼 준비가 되어 있느냐, 아들아?";
			link.l1 = "물론입니다. 여기 있습니다. 진정으로 도움이 필요한 사람들을 도울 수 있어 기쁘며, 이 돈이 성부님의 감독 아래 현명하고 명예롭게 쓰일 것이라 확신합니다.";
			link.l1.go = "SharlieEpilog_Benua_Money_4_1";
			link.l2 = "죄송합니다. 다시 한 번 곰곰이 생각해 봐야 할 것 같습니다.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_5":
			dialog.text = "그렇다면 네 기부금은 이십오만 페소가 되어야 한다. 이 자금으로 고아들을 위한 보호소를 세울 수 있으며, 그것은 네 이름을 기리고 최소한 초기에는 운영을 유지할 수 있을 것이다. 지금 바로 이 금액을 낼 준비가 되어 있느냐, 아들아?";
			link.l1 = "물론입니다. 여기 있습니다. 진정으로 도움이 필요한 사람들을 도울 수 있어 기쁘며, 이 돈이 성부님의 감독 아래 현명하고 명예롭게 쓰일 것이라 확신합니다.";
			link.l1.go = "SharlieEpilog_Benua_Money_5_1";
			link.l2 = "죄송합니다. 다시 한 번 곰곰이 생각해 봐야 할 것 같습니다.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_6":
			dialog.text = "흠, 시간을 헛되이 보내지는 않았군, "+pchar.name+". 오십만 페소의 기부면 충분할 것 같다. 이 정도의 헌금이라면 병원을 세우고 오랜 세월 동안 필요한 모든 것을 제공할 수 있을 것이다. 지금 바로 이 금액을 낼 준비가 되어 있느냐, 아들아?";
			link.l1 = "물론입니다. 여기 있습니다. 진정으로 도움이 필요한 사람들을 도울 수 있어 기쁘며, 이 돈이 성부님의 감독 아래 현명하고 명예롭게 쓰일 것이라 확신합니다.";
			link.l1.go = "SharlieEpilog_Benua_Money_6_1";
			link.l2 = "죄송합니다. 다시 한 번 곰곰이 생각해 봐야 할 것 같습니다.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_4_1":
			dialog.text = "훌륭하구나, 아들아.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -100000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "10000000");
			AddQuestUserData("SharlieEpilog", "tSum", "100000");
			pchar.questTemp.SharlieEpilog_gold_S = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_5_1":
			dialog.text = "훌륭하구나, 아들아.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -250000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "25000000");
			AddQuestUserData("SharlieEpilog", "tSum", "250000");
			pchar.questTemp.SharlieEpilog_gold_M = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_6_1":
			dialog.text = "훌륭하구나, 아들아.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -500000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "50000000");
			AddQuestUserData("SharlieEpilog", "tSum", "500000");
			pchar.questTemp.SharlieEpilog_gold_L = true;
			pchar.questTemp.SharlieEpilog_Money = true;
			Achievment_Set("ach_CL_205");
		break;

		case "SharlieEpilog_Benua_Patent":
			dialog.text = "그렇다면, 어떤 선택을 하겠느냐, 아들아?";
			link.l1 = "긴 여정이 기다리고 있지만, 나는 특허를 유지하고 프랑스와 국왕에 대한 충성을 지키고 싶습니다.";
			link.l1.go = "SharlieEpilog_Benua_Patent_2";
			link.l2 = "나는 특허를 포기하기로 했습니다. 앞길은 멀고, 언제 돌아올지 알 수 없습니다. 지키지 못할지도 모를 의무와 규칙을 짊어지지 않는 편이 현명하다고 생각합니다.";
			link.l2.go = "SharlieEpilog_Benua_Patent_6";
			pchar.questTemp.SharlieEpilog_Patent = true;
		break;

		case "SharlieEpilog_Benua_Patent_2":
			dialog.text = "그 결정을 내린 것을 기쁘게 생각한다, 아들아. 지금 우리 국가는 그 어느 때보다도 강하고 용감한 기사들을 필요로 한다. 하지만 말해 보아라, "+pchar.name+", 정착하여 가정을 이루고 매 순간 목숨을 걸지 않는 삶을 생각해 본 적은 없느냐? 인간은 영원히 불길 속에서 자신을 시험해야 할 존재는 아니니라.";
			link.l1 = "성부님, 가만히 앉아 있기만 하는 것은 제게 쉽지 않을 것 같습니다. 하지만 성서에도 이렇게 쓰여 있습니다. ‘주님의 전사들조차, 그 사명이 끝나면 안식을 허락받는다.’ 제 사명이 아직 끝나지 않았더라도, 언젠가 제 손으로 검을 영원히 칼집에 넣는 날을 선택하고 싶습니다.";
			link.l1.go = "SharlieEpilog_Benua_Patent_3";
		break;

		case "SharlieEpilog_Benua_Patent_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_4";
			AddQuestRecord("SharlieEpilog", "5_2");
		break;

		case "SharlieEpilog_Benua_Patent_4":
			dialog.text = "훌륭하구나, 아들아. 폐하께서도 너의 충성과 헌신을 결코 외면하지 않으실 것이다.";
			link.l1 = "지금 제 마음은 전혀 다른 곳에 있습니다... 아버지께서 제가 영지에 남아 살기를 강요하지 않으셨으면 좋겠습니다. 아직은 그럴 준비가 되어 있지 않습니다. 다행히도, 이 문제를 생각할 시간은 충분히 있겠지요.";
			link.l1.go = "SharlieEpilog_Benua_Patent_5";
		break;

		case "SharlieEpilog_Benua_Patent_5":
			dialog.text = "...";
			link.l1 = "그럼, 이제 다시 세속의 일로 돌아가죠.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Patent_6":
			dialog.text = "음, 그것도 이치에 맞는 결정이다. 하지만 한 가지는 말해야겠구나. 네가 떠난다면, 이 바다에서 프랑스의 힘은 크게 약화될 것이다.";
			link.l1 = "폐하의 휘하에는 프랑스의 위엄을 지킬 만한 훌륭한 선장들이 충분히 있다고 믿습니다.";
			link.l1.go = "SharlieEpilog_Benua_Patent_7";
		break;
		
		case "SharlieEpilog_Benua_Patent_7":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_8";
			AddQuestRecord("SharlieEpilog", "5_1");
		break;

		case "SharlieEpilog_Benua_Patent_8":
			dialog.text = "...";
			link.l1 = "이제 끝이군요. 마치 짐을 내려놓은 느낌입니다. 솔직히 말하면, 내가 이 카리브에 처음 왔을 때 어떤 사람이었는지도 잊어버릴 뻔했네요... 정말 많은 일이 있었죠.";
			link.l1.go = "SharlieEpilog_Benua_Patent_9";
		break;

		case "SharlieEpilog_Benua_Patent_9":
			dialog.text = "아마 여러 번 들었겠지만, 아들아 — 주님의 길은 인간이 헤아릴 수 없는 법이다. 너에게 주어진 길을 너는 품위 있게 걸어왔다. 하지만 나는 믿는다 — 너의 시련은 아직 끝나지 않았고, 어쩌면 너의 영광은 이제야 절정에 향하고 있는지도 모른다.";
			link.l1 = "영광은 무거운 짐이죠, 성부님. 그것을 바라는 자 모두가 그 무게를 감당할 수 있는 것도 아니고... 또, 제때 멈출 줄 아는 것도 쉽지 않지요.";
			link.l1.go = "SharlieEpilog_Benua_Patent_10";
		break;

		case "SharlieEpilog_Benua_Patent_10":
			dialog.text = "...";
			link.l1 = "그럼, 다시 세속적인 일로 돌아가겠습니다.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron":
			dialog.text = "아들아, 너는 해적들의 우두머리와 관계가 있느냐?";
			link.l1 = "당신은 코드의 수호자를 알고 계신가요?";
			link.l1.go = "SharlieEpilog_Benua_Baron_2";
			pchar.questTemp.SharlieEpilog_Baron = true;
		break;

		case "SharlieEpilog_Benua_Baron_2":
			dialog.text = "코드의 수호자? 아니, 나는 그와는 안면이 없다. 나는 마르쿠스 티락스를 안다 — 그는 처형인이며, 그의 등 뒤에는 너무나도 많은 피가 묻어 있다. 수백 년을 기도하며 살아도 주님의 용서를 받기 어려울 것이다. 그럼에도... 너는 정말 그와 거래를 했느냐?";
			link.l1 = "미셸을 감옥에서 구해내기 위해 그의 신뢰를 얻어야 했습니다. 어쨌든, 저는 제 실수를 깨달았고, 더 이상 그와 관계를 유지할 생각은 없습니다. 이 편지를 통해 그와의 마지막 끈을 끊으려 합니다.";
			link.l1.go = "SharlieEpilog_Benua_Baron_3";
			link.l2 = "지금은 더 이상 중요한 문제가 아닙니다. 저는 군도를 떠나며, 그와의 길도 자연히 갈라질 겁니다, 성부님.";
			link.l2.go = "SharlieEpilog_Benua_Baron_7";
		break;

		case "SharlieEpilog_Benua_Baron_3":
			dialog.text = "그 끈이란 게 무엇이냐, 아들아? 그게 무고한 자들의 피로 더럽혀지지 않았기를 바란다.";
			link.l1 = "형식상으로는 루 프랑수아 해적 정착지의 우두머리로 있었지만, 실제로는 다른 사람이 모든 것을 운영하고 있었습니다. 오늘, 저는 해적 남작이라는 칭호를 완전히, 그리고 영원히 포기합니다.";
			link.l1.go = "SharlieEpilog_Benua_Baron_4";
		break;

		case "SharlieEpilog_Benua_Baron_4":
			dialog.text = "너가 올바른 길로 들어선 것을 기쁘게 생각한다, 아들아. 너의 영혼의 구원을 위해 기도하겠다. 누구나 실수할 수 있지만, 주님은 진심으로 회개한 자만을 용서하시느니라.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Baron_5";
		break;
		
		case "SharlieEpilog_Benua_Baron_5":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_6";
			AddQuestRecord("SharlieEpilog", "4_1");
		break;
		
		case "SharlieEpilog_Benua_Baron_6":
			dialog.text = "훌륭하구나, "+pchar.name+"야. 편지를 넘겨주렴 — 내가 그것이 목적지에 도착하도록 하겠다. 그리고 기도를 잊지 마라, 아들아. 참회와 기도만이 가장 무거운 죄마저도 씻어낼 수 있다.";
			link.l1 = "감사합니다, 성부님. 어쩌면 저에게도 아직 희망이 남아 있을지도 모릅니다.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron_7":
			dialog.text = "죄가 아무리 크다 해도, 아들아, 용서의 문은 항상 열려 있다. 참회와 기도, 그리고 선행은 영혼을 정화하느니라. 그것은 마치 빗방울이 돌 위의 먼지를 씻어내는 것과 같지.";
			link.l1 = "모든 일엔 때가 있는 법이지요, 성부님. 지금은 세속의 일들을 정리해야 합니다.";
			link.l1.go = "SharlieEpilog_Benua_Baron_8";
		break;

		case "SharlieEpilog_Benua_Baron_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_9";
			AddQuestRecord("SharlieEpilog", "4_2");
		break;

		case "SharlieEpilog_Benua_Baron_9":
			dialog.text = "...";
			link.l1 = "여기 있습니다.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona":
			dialog.text = "그들을 돌보려 하고 잊지 않으려는 너의 마음이 기쁘구나, 아들아. 그 섬을 누구에게 맡기고 싶은가?";
			link.l1 = "프랑스 국기를 그 섬에 올리는 것이 좋을 것 같습니다. 언젠가는 누군가 그 섬을 발견할 테고, 다른 나라들이 그것을 차지하려 들겠지요. 나는 그런 일을 두고 볼 수 없습니다.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France";
			link.l2 = "그 섬과 그곳 사람들은 왕권의 그늘 아래가 아니라 자유롭게 살아갈 자격이 있습니다. 나는 블루벨드의 친구 얀 스벤손에게 편지를 보내 이 땅을 맡아달라 부탁할 생각입니다. 그가 기꺼이 수락하리라 믿습니다. 다만 부탁드리오, 성부님 — 이 대화는 비밀로 해주시길. 그들의 안전과 안녕을 위해서요.";
			link.l2.go = "SharlieEpilog_Benua_IslaMona_Pirate";
			pchar.questTemp.SharlieEpilog_IslaMona = true;
		break;

		case "SharlieEpilog_Benua_IslaMona_France":
			dialog.text = "지혜로운 판단이구나, "+pchar.name+"야. 국왕의 보호 아래 그 섬은 질서와 안전을 얻게 될 것이다.";
			link.l1 = "카프스터빌 관청과 섬 주민들에게 편지를 보내겠습니다. 좌표는 봉투에 명시하겠습니다.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_2";
		break;

		case "SharlieEpilog_Benua_IslaMona_France_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_France_3";
			pchar.questTemp.SharlieEpilog_IslaMona_France = true;
			AddQuestRecord("SharlieEpilog", "3_1");
		break;

		case "SharlieEpilog_Benua_IslaMona_France_3":
			dialog.text = "...";
			link.l1 = "여기 있습니다. 왕의 함대가 도착하기 전에 당신들의 사람들이 그 섬을 발견하길 바랍니다.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_4";
		break;

		case "SharlieEpilog_Benua_IslaMona_France_4":
			dialog.text = "걱정하지 마라, 아들아. 가장 유능한 전달자에게 이 편지를 맡기도록 하겠다.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate":
			dialog.text = "네 길이 올바른지 내가 판단할 수는 없다, 아들아. 언젠가는 누군가 그 섬을 발견하게 될 것이고, 한 나라가 그것을 차지하고자 할 것이다. 그것은 시간문제일 뿐. 하지만 네가 그런 결정을 내렸다면 — 그것은 하느님의 뜻일지도 모르지. 걱정 마라: 나는 그들을 위험에 빠뜨리지 않을 것이며, 그들을 위해 기도할 것이다.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_Pirate_2";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_Pirate_3";
			pchar.questTemp.SharlieEpilog_IslaMona_Pirate = true;
			AddQuestRecord("SharlieEpilog", "3_2");
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_3":
			dialog.text = "블루벨드의 얀 스벤손 말이지?";
			link.l1 = "맞습니다, 성부님. 그리고 두 번째 편지는 직접 섬으로 보내야 합니다. 좌표는 봉투에 적혀 있습니다.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome":
			dialog.text = "훌륭하구나, 아들아. 내가 알기로는 네가 '"+GetShipName("Ulysse")+"'라는 피나스호를 타고 여기 도착하지 않았느냐?";
			link.l1 = "맞습니다. 그런데 왜 그러시죠?";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_2";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome_2":
			dialog.text = "그 배는 최근 경매에 부쳐졌단다. 그리고 너, 샤를, 그 배를 다시 얻을 기회가 있어 — 이번에는 선장으로서 말이지.";
			link.l1 = "흠... 확실히 매력적인 제안이군요. 항만청에 들러봐야겠어요. 감사합니다, 성부님.";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_3";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_3":
			DialogExit();
			NextDiag.CurrentNode = "First Time";
			AddDialogExitQuestFunction("SharlieEpilog_PU_Ulysse_1");
		break;
		//<-- Эпилог
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
