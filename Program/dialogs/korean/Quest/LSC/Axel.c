// торговец Аксель Йост
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "저것 좀 봐라..."+GetFullName(pchar)+"! 죽다 살아온 거야? 어떻게 그걸 해냈지?";
				link.l1 = "간단하지: 난 죽은 적이 없거든, 하하!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "헤이, 친구, 너 나랑 거래하려면 먼저 나르발족이랑 화해해야 해. 그놈들한테 괜히 엮이고 싶지 않거든. 파지오한테 가 봐, 그가 도와줄 거야.";
				link.l1 = "좋아, 바로 그를 만나러 가지.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "난 너랑 말하고 싶지 않아, 이 친구야. 넌 아무 이유 없이 죄 없는 사람들을 공격하고 싸움을 부추기잖아. 꺼져!";
				link.l1 = "음...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "아, 새로운 얼굴이군! 무슨 일로 여기 왔나? 뭐, 내가 물을 처지는 아닐지도 모르지... 자기소개하지. 내 이름은 악셀 요스트고, 여기가 내 가게야. 마음에 드는 거라도 있나?";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 무슨 물건을 팔고 있소?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+pchar.name+"! 반갑군. 사려고 왔나, 아니면 팔려고 왔나?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "이봐, 악셀, 좋은 소총 팔고 있나? 그냥 평범한 병사 머스킷 말고, 정확도랑 사거리가 뛰어난 그런 거 말이야?";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "이봐, 악셀, 챈드 카퍼가 너한테 위스키 한 통 가져다 달라고 했냐? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "들어봐, 악셀, 네가 그 멍청이랑 내가 나눈 얘기 들었을 거 아냐. 그 자식이 무슨 구슬을 달라고 했지? 난 이해가 안 돼.";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "그래. 거래하자, Axel!";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("섬 주변에 소문 들은 거 있어, 악셀?", "요즘 정의의 섬에서 무슨 일이 있었지?", "최근에 들은 소문이 뭐지?");
				link.l2.go = "rumours_LSC";
				link.l3 = "아직 아니야. 그냥 인사나 하려고 왔어.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "온갖 물건들이 있지: 물약, 칼, 화기, 탄약, 흉갑, 보석, 광물, 마법 부적, 탈리스만, 잡동사니, 제작 재료...\n사람들이 난파선에서 주운 자기한테 필요 없는 것들을 다 나한테 가져오거든. 너도 그렇게 해도 돼. 물론, 식량이나 선박 용품은 취급하지 않아.";
			link.l1 = "좋아, 악셀. 네가 뭘 가지고 있는지 보자.";
			link.l1.go = "Trade_items";
			link.l2 = "고마워, 악셀. 명심할게. 네 도움이 필요할 때 다시 보자.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Trade_items":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 5)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// наводка на Адольфа
		case "adolf":
			dialog.text = "이거 농담이지? 너로 세 번째야, 그걸 묻는 사람이!\n난 그런 무기는 안 다뤄. 하지만 몇 달 전에 아돌프 바르비에가 조준경 달린 사냥용 슈투첸을 나한테 팔려고 했었지. 정말 멋진 무기였어, 네가 찾는 게 딱 그거야.\n근데 바르비에가 터무니없는 값을 불러서, 난 그 제안을 거절했지.";
			link.l1 = "정말이야! 그럼 바르비에르는 어디서 찾을 수 있지?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "나도 잘 모르겠어. 아마 도시 어딘가를 돌아다니고 있을 거야. 산초네 선술집에 자주 들르지, 매일 저녁 술 한잔하는 걸 좋아하거든.";
			link.l1 = "고마워! 거기서 그를 찾아봐야겠어. 그런데, 악셀, 그 소총에 대해 너한테 물어본 사람이 또 누구지? 다른 사람들도 관심을 보였다고 했잖아, 그게 누구야?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "메리 캐스퍼와 마르첼로, 일명 외눈박이.\n그 아가씨가 왜 소총이 필요한지는 전혀 모르겠어. 하지만 우리 붉은 메리는 워낙 별난 사람으로 유명하지. 1년 전엔 지뢰를 만든다고 화약을 엄청 샀다니까. '게를 기절시키려고' 그랬다지. 도널드가 말려서 다행이야.\n그리고 마르첼로는 새 사냥하려고 소총을 사고 싶어 했어. 소금에 절인 소고기가 지겨워졌다고 하더군. 둘 다 아돌프에게 소개해 줬지. 아돌프가 둘 중 누구에게 소총을 팔았는지는 모르겠어.\n그리고... 그 교활한 주세페 파지오가 최근에 아돌프에 대해 물어봤어. 아마 그 녀석도 슈투첸을 사고 싶은가 보지.";
			link.l1 = "경쟁자가 많은 것 같군. 좋아, 내가 아돌프를 찾아볼게. 아직 슈투첸을 팔지 않았길 바라면서.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_2"; //флаг на таверну
			AddQuestRecord("SharkHunt", "12");
			sld = characterFromId("LSC_Adolf");
			sld.lifeday = 0; // убираем настоящего Адольфа
		break;
		
		// бусинка для Белого Мальчика - просто инфа
		case "ole_pearl":
			dialog.text = "헤, 그 녀석이 말하는 '큰 진주'가 바로 그거야! 누구한테나 그걸 달라고 하지. 하나만 주면, 넌 그 녀석의 제일 친한 친구가 될 거야.";
			link.l1 = "아, 그렇군. 큰 진주라니... 고맙다, 악셀. 평범한 구슬을 찾느라 헛수고할 뻔했잖아!";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "그래, 친구, 맞아. 하지만 너도 부쉬밀스 한 통 사려고 온 거라면 실망시켜야겠군. 나한텐 딱 한 통뿐이었고, 그걸 챗이 샀어. 대신 스카치 위스키는 줄 수 있어. 아일랜드산만큼 훌륭하고, 사실 나는 그 맛이 더 좋더라.";
			link.l1 = "다음에 이야기하지. 채드가 너한테서 또 뭔가 샀나?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "아니. 아! 그 사람은 비소에 관심이 있었어. 타르타로스에 쥐가 너무 많다면서, 쥐들을 없애고 싶다고 하더군.\n나는 이제 비소를 다루지 않아. 올레를 고용해서 내 가게를 청소한 뒤로는 필요가 없었거든. 남은 비소는 불쌍한 산초에게 줬지. 쥐들이 그의 선술집으로 옮겨간 것 같더라고. 왜 쥐들이 올레를 그렇게 무서워하는지는 모르겠어...";
			link.l1 = "어쩌면 그의 아버지가 고양이였을지도 몰라.";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "하하! 그럴지도... 어쨌든, 산초가 비소를 가지고 있으니, 필요하면 한 병 받아가.";
			link.l1 = "알겠어, 고마워. 바로 그를 만나러 갈게.";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			DialogExit();
			AddQuestRecord("SharkHunt", "36");
			pchar.questTemp.Saga.SharkHunt = "barmen_whiskey"; // флаг на таверну - поиск мышьяка
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
