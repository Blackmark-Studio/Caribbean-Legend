// Санчо Карпентеро - бармен
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
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "나가! 거리에서 무고한 사람들을 공격하는 놈들에게는 술을 안 팔아!";
				link.l1 = "음...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+"! 이렇게 다시 보게 되어 정말 기쁘다! 내가 알았지 - 내가 알았어! - 소문은 거짓이었어! 젠장, 나랑 한잔하자!";
				link.l1 = "마시자, 산초! 나도 네가 보여서 정말 기쁘다!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+", 져서 유감이야. 저 뚱뚱한 놈보다 술을 더 마실 수 있는 사람은 거의 없어. 머리는 괜찮아?";
				link.l1 = "너... 너 진짜 독한 럼을 내놓는구나, 산초. 술값은 내가 갚아야지... 얼마냐?";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "파지오를 이겼구나, "+pchar.name+"! 완전 놀랐네! 그를 이긴 사람은 한두 명밖에 없었지. 자, 여기 이백 두블론 가져가.";
				link.l1 = "친절한 말씀 고마워, 산초!";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+"? 너, 그 나르발 기술자가 만든 잠수복 입고 바닷속까지 들어갔다던데, 진짜야?";
				link.l1 = "맞아, 친구. 나는 바다 밑바닥까지 봤다니까!";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "어서 오시오! 내 주점에 새로운 얼굴이 찾아오면 언제나 반갑지! 환영하오! 내 주점에는 언제나 좋은 술이 있소 - 유럽산 와인이 창고에 가득하오!\n음식은... 뭐, 그 정도는 아니지만. 하하... 농담이오. 내 이름은 산초 카르펜테로, 여기가 내 가게요.";
				link.l1 = TimeGreeting()+", 산초. 내 이름은 "+GetFullName(pchar)+". 만나서 반갑소.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, 친구여 "+pchar.name+"! 반갑군! 뭐로 할까?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "이봐, 산초, 어디서 좋은 소총을 구할 수 있는지 아니? 보통 보병용 머스켓 말고, 사냥 같은 데 쓸 수 있는 정확하고 사거리가 긴 그런 거 말이야.";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "이봐, 산초, 너한테 물어볼 게 좀 있어. 아돌프 바르비에라는 남자를 찾고 있는데, 여기서 자주 술 마신다고 들었거든...";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "이봐, 산초, 사람들이 그러는데 차드 카퍼가 너한테 비소를 샀다던데...";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "산초, 너한테 보여주고 싶은 게 있어. 이게 네가 그렇게 손에 넣으려고 했던 박쥐 가면 맞지?";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && PCharDublonsTotal() >= 1)
				{
					if (PCharDublonsTotal() >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "산초, 내 흉갑 가지러 왔어. 여기 돈이야.";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "산초, 내가 내 흉갑을 가지러 왔어. 여기 돈이야.";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "럼 좀 따라 줘, 산초.";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "방을 빌리고 싶어.";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "심심해, 산초. 저녁이 올 때까지 여기서 와인 한 병과 함께 시간을 보내고 싶어...";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("요즘 사람들은 무슨 이야기를 하냐, 산초?", "최근 정의의 섬에서 무슨 일이 있었지?", "소문 좀 있어?");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "산초, 네게 팔 게 게 집게발이 있어.";
					link.l10.go = "crab_trade";
				}
				link.l4 = "산초, 이 섬에 대해 물어보고 싶은 게 있어.";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "아니, 친구. 그냥 어떻게 지내나 궁금해서 왔어. 잘 가!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "나도 그래. 적어도 하루에 한 번쯤은 널 볼 수 있길 바라, 하하! 내 주점에 새로운 손님이 와서 진심으로 기쁘다.";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "럼 좀 따라 줘, 산초.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "방을 빌리고 싶어.";
				link.l2.go = "room";
			}
			link.l3 = "Sancho, 이 섬에 대해 물어보고 싶은 게 있어.";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "잘 있어, 산초!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "아니, 친구, 나는 도와줄 수 없어. 내 전문은 맥주랑 와인이지, 머스켓은 아니거든, 하하! 상점에 가 봐. 악셀이 가끔 흥미로운 무기를 판다고 들었어. 거기서 필요한 걸 찾을지도 몰라.";
			link.l1 = "조언 고마워.";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "아돌프? 그래, 가끔 나를 찾아오지. 하지만 며칠째 못 봤어. 그 뚱뚱한 남자, 주세페랑 얘기한 뒤로 소식이 없어.";
			link.l1 = "주세페... 주세페 파치오 말하는 거야?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "정의의 섬에 주세페는 한 명뿐이지. 그래, 그 사람이야. 몇 시간 같이 앉아서 럼 한 병 나눠 마시고, 아주 활기차게 이야기를 나눴지.";
			link.l1 = "그들이 다투고 있었나?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "아니. 그들은 오랜 친구처럼 이야기했어. 봐, 그냥 캐롤라인에 있는 파지오를 찾아가서 직접 물어봐.";
			link.l1 = "좋아, 그렇게 할게.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "그게 다야? 질문이 좀 더 있다고 하지 않았어...";
			link.l1 = "그래. 말해 봐, 레드 메리랑 마르첼로 외눈박이는 누구지?";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "레드 메리는 나르발족 중 한 명이야. 젊고 아름다운 아가씨지만 완전히 야성적이지. 칼과 권총을 남자 못지않게 잘 다뤄. 원래는 나르발족의 전 지도자였던 앨런 밀로우의 여자친구였는데, 제독이 그를 죽이기 전까지 그랬지\n앨런의 죽음은 그녀에게 큰 충격이었어. 그래서 세레스호 선실에서 울고 샤크를 저주하며 하루하루를 보내고 있지... 하지만 곧 극복할 거야. 인생은 계속되니까.\n마르첼로에 대해서는 잘 몰라, 몇 번밖에 본 적 없어. 무서운 녀석이야. 예전에는 왕실 사냥꾼이었다고들 하더군, 싸움에서 한쪽 눈을 잃고 나서 용병으로 상선에 올라 바다에서 적의 승선 공격을 막으며 살았대.\n당연하게도... 해적을 증오하지.";
			link.l1 = "알겠어... 고마워, Sancho. 정말 큰 도움이 됐어.";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "천만에, 친구. 또 오면 같이 에일 한잔하자.";
			link.l1 = "물론이지!";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "카퍼? 아니, 최근에 선술집에 온 적 없어. 마르첼로 외눈박이가 막 15분 전에 비소 한 병을 샀어. 쥐 때문에 고생하는 모양이지. 무슨 말인지 완전히 이해해... 젠장할 쥐들.";
			link.l1 = "키클롭스가 여기 있었어?!";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "글쎄, 그렇지. 왜?";
			link.l1 = "며칠째 그를 찾고 있었어. 어디로 갔는지 알아?";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "그는 산타 플로렌티나에 사는 아돌프 바르비에와 함께 있었어. 아마 그쪽으로 갔던 게 아닐까?";
			link.l1 = "고마워!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "비소가 필요하면, 한 플라스크에 이십 두블룬에 팔 수 있어--!";
			link.l1 = "나중에 이야기하자, Sancho. 잘 있어!";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "이봐, 친구, 나한테 빚진 거 없어. 이미 백 두블론이나 잃었잖아. 파지오보다 술 더 마시려다 그런 거지...";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "아니야, 아니야, 산초, 제발! 이 오백 페소를 가져가. 내가 기억하기로는 이 정도면 술값은 충분히 될 거야. 네게 빚지고 싶지 않아.";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "에... 고마워, 산초. 네 말이 맞아.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You have received 200 doubloons");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "흠... 그럼 제안을 하나 하지. 저 아래에서 거대한 게를 본 적 있나?";
			link.l1 = "장난해? 놈들이 떼거리로 몰려왔잖아! 무슨 생각이었어?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "녀석들 중 누구라도 죽이면, 반드시 발톱을 나한테 가져와라. 두블룬으로 넉넉히 쳐주지. 한 개당 다섯 닢이다! 악셀 요스트는 그만큼 안 줄 거다, 장담하지.\n굳이 사냥하라고 하는 건 아니야... 하지만 혹시 한두 마리 잡게 되면 내 제안을 기억해둬...";
			link.l1 = "왜 집게발만? 게의 다른 부분들은 어쩌고?";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "대부분의 살은 집게에 있기 때문이지. 게 다리에는 살이 별로 없고, 몸통은 단단한 껍질로 덮여 있거든. 여기서 게살은 진미야. 맛이 아주 훌륭하고, 영양도 풍부하지!\n나만의 특별한 조리법도 있으니, 집게 하나당 두블룬 다섯 개씩 쳐 주겠어.";
			link.l1 = "알겠어, 명심할게...";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "훌륭하군! 몇 개나 가지고 있지?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
			link.l2 = "내 마음이 바뀌었어.";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "좋아. 자, 두블룬을 가져가라 - "+FindRussianQtyString(iTotalTemp*5)+". 고맙다, 친구야. 더 구하면 나한테 가져와.";
			link.l1 = "그래, 친구.";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+iTotalTemp*5+" doubloons");
		break;
		
		// крыс
		case "rat":
			dialog.text = "뭐?! 보여 줘! 내가 직접 봐야겠어!";
			link.l1 = "알았어, 알았어, 하하!";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "이... 이거야! 선원이 내게 그려준 그림에 있던 것과 똑같아!\n친구야... 이걸 나한테 팔아줄 수 있겠어?";
			link.l1 = "그건 상황에 따라 다르지. 내가 기억하기로는, 네가 이 물건에 왕의 몸값만큼 준다고 약속했잖아.";
			link.l1.go = "rat_2";
			link.l2 = "미안하다, 친구야, 이건 팔 수 없어. 내 배에 필요하거든. 그냥 네가 말한 부적이 진짜 이거 맞는지 확인만 받고 싶었어.";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "에이, 참 안타깝군... 그래, 친구야, 이게 바로 그 부적이야. 운 좋은 녀석! 이제 쥐 걱정은 다시는 안 해도 되겠네! 나는 계속 비소로 쥐를 잡아야겠지만...";
			link.l1 = "기대하게 해서 미안해, 산초. 내가 이 물건이 어떻게 생겼는지 확신이 없어서 확인이 필요했어. 미안하다.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "이 일로,"+pchar.name+", 내가... 내가 가진 것 중 가장 훌륭하고 값진 물건을 네게 살 기회를 주겠어! 잠깐만, 지금 가져올게...\n자, 한번 봐. 이건 유일무이하고 눈부신 밀라노 흉갑이야, 장인의 솜씨로 만들어진 작품이지! 전투에서 뛰어난 방어력을 제공하면서도 움직임이 자유롭고, 가볍고 편안해. 이런 품질의 갑옷은 카리브 해에서도, 유럽에서도 정말 드물지.\n몇 해 전, 스페인 전열함의 선장실에서 이 흉갑을 우연히 발견했고, 바로 이런 때를 위해 간직해뒀지. 이걸 네게 이천 금화에다가 쥐 신까지 얹어서 팔 의향이 있어!";
			link.l1 = "흠... 이거 정말 걸작 큐이라스구만! 이 교환, 내게 딱 맞는 것 같아. 쥐를 처리하는 방법은 많지만, 이런 큐이라스를 또 찾는 건 거의 불가능하지. 이런 건 처음 본다니까. 정말로 독특한 갑옷이야.";
			link.l1.go = "rat_yes";
			link.l2 = "얼마라고?! 산초, 오늘 아침에 네 쥐들이 너를 몇 번이나 물었냐? 이천이라고? 네가 이 우상을 찾으려고 얼마나 고생했는지 알기나 해?! 당장 값을 내려!";
			link.l2.go = "rat_torg";
			link.l3 = "얼마라고?! 넌 진짜 상어구나, 산초? '구매할 기회를 제공한다'라니 - 허! 그 돈이면 본토에서 총알도 막고 물 위도 걸을 수 있는 갑옷을 맞출 수 있겠네! 그리고 그렇게 많은 금이 왜 필요하지? 위르겐에게 네 동상을 주조하게 해서 산 아구스틴 갑판에 세워두려고?";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "네가 배에 올라타서 정말 기쁘다, 친구야. 내 문제를 잊지 않아줘서 고맙다! 그러니 내 두블룬을 기다릴게. 갑옷은 네가 올 때까지 준비해 놓을 테니!";
			link.l1 = "곧 데려올게!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+"다른 상황이었다면 오천을 요구했을 거요. 제독께서도 관심을 보이셨으니, 믿어도 좋소, 그분만이 아니오. 하지만 천천히 결정하시오; 갑옷은 당신이 필요할 때까지 기다릴 테니. 당신에게만 팔겠소.";
				link.l1 = "생각해 볼게, 산초.";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+"다른 상황이었다면, 나는 오천을 요구했을 거야. 제독 본인도 관심을 보였으니, 그뿐만이 아니라는 걸 믿어도 좋아.\n좋아, 네가 나와 내 문제를 잊지 않았으니 오백 깎아주지. 쉽지 않은 모험이었겠지.";
				link.l1 = "그게 낫군... 하지만 여전히 이해가 안 돼. 왜 내가 이런 똑같이 특별한 물건을 교환하면서 더 내야 하지? 어쩌면 네가 나한테 돈을 줘야 하는 거 아냐, 산초? 헤헤?";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				Notification_Skill(false, 90, SKILL_COMMERCE);
				dialog.text = "아니, "+pchar.name+", 절대 안 돼. 쥐는 비소로 처리할 수 있지만, 이 갑옷은 언젠가 네 목숨을 구해줄 거야. 그리고 이걸 입으면 이탈리아 공작처럼 보일 거라고! 천오백, 그게 내 마지막 제안이야. 천천히 생각해 보고, 결정나면 말해. 네가 필요할 때까지 이 갑옷은 기다릴 거야, 너한테만 팔 거니까.";
				link.l1 = "산초, 네가 이 쓸쓸한 무덤 같은 곳의 유일한 선술집 주인이 아니었으면... 네 제안을 생각해 볼게.";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = "군인 선장이자 해적인 주제에 협상은 꽤 잘하는군! 요스트 기억나? 그 자식, 쥐들이 나를 괴롭히고 있을 때 내 비소 전부를 헐값에 사 갔지.\n좋아, "+pchar.name+", 네가 이겼어. 오백 더 깎아줄게! 하지만 이게 마지막 제안이야!";
				link.l1 = "아직도 뭔가 속은 기분이지만, 이제는 정글에서 흔한 곤경에 처한 아가씨처럼 느껴지진 않겠네.\n기다려, 곧 돈 가져올게.";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "진정해, "+pchar.name+". 다른 놈한테서라면 오천을 요구했을 거야! 제독님도 관심을 보였지—그리고 그분만 그런 게 아니야, 믿어.\n갑옷은 네 걸로 남겨둘게—그동안 다른 놈한테는 안 팔 거다.";
			link.l1 = "이런 영광이! 곧 돌아올게. 이천!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "됐어! 동의해 줘서 고맙다, 친구. 내 문제를 잊지 않아줘서 고맙고! 이 흉갑을 가져가라, 전투에서 잘 써라.";
			link.l1 = "여기, 부적 가져가. 네 선술집의 쥐들에게 어두운 날이 올 것 같으니, 하하!";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.ratmoney));
			Log_Info("You have given away the talisman 'God of rats'");
			Log_Info("You have received a Milanese armor");
			Log_Info("You gave "+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - PCharDublonsTotal();
			Log_Info("You gave "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
			dialog.text = "넌 여전히 나를 놀라게 해\n "+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+".";
			link.l1 = "상기시키지 마!";
			link.l1.go = "exit";
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "듣고 있어, 친구.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "이 섬이 뭐지? 좀 더 자세히 말해줄 수 있어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "어떻게 하면 이 섬을 떠날 수 있지?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "섬에 대해 내가 알아야 할 게 뭐지?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "여기서는 어떻게 지내고 있나? 선술집은 잘 되고 있나?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없어, 됐어...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "이 섬 말인가? 뭐, 사람들은 정의의 섬, 정의의 섬, 혹은 버려진 배들의 도시라고 부르지만, 우리는 그냥 섬이라고 해. 이곳은 난파된 배들로 이루어져 있는데, 그 배들이 암초 한가운데 얕은 곳에 걸려 있지.\n섬의 중심부가 우리가 사는 곳이고, 바깥쪽 난파선들은 사람이 살지 않아. 외부 세계와의 연결은 10년째 끊겼어.";
			link.l1 = "믿을 수가 없군!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "긴 보트나 뗏목을 만들어도, 그 끝은 좋지 않을 거야. 폭풍과 거센 해류가 정의의 섬을 에워싸고 있어서, 바깥 고리를 넘어서면 목숨을 걸어야 하지.\n정말 뛰어난 선원들로 팀을 꾸려야 겨우 살아남을 희망이 있는데, 이곳 주민들 중 떠나려는 사람은 극히 드물어. 바깥 고리 너머로 나가려는 위험을 감수하는 사람은 더더욱 적지.\n여기서 사는 걸 좋아하는 사람들이 많아. 못 믿겠으면 주변에 물어봐.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "먼저, 이 섬에는 몇몇 출입 금지 구역이 있다는 걸 기억해야 해. 두 개의 클랜, 즉 나르발과 리바도스가 오랫동안 여기서 서로 끊임없이 싸우며 각자 자기 땅을 지키고 있거든. 허락 없이 그들 구역에 들어가면, 넌 죽은 목숨이야.\n그들 구역에 들어가려면 현재 통행 암호를 알아야 해. 실수로 침입하는 건 걱정하지 마. 경비병들이 총을 쏘기 전에 몇 번은 경고해 줄 테니까.";
			link.l1 = "명심하겠다...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "있잖아, 친구, 괜찮아. 난 음식이랑 술 다루는 일에 익숙하거든. 유럽에서 요리사로 여러 군데서 일했지 – 주둔지, 선술집, 배 위에서도 말이야 – 그래서 여기 오자마자 제일 먼저 한 일이 바로 선술집을 차린 거였어.\n내 일이 마음에 들고, 내 삶도 만족스러워. 누구나 먹고 마셔야 하니까, 난 그걸 대접하는 게 즐겁지. 여기 사람들은 다들 친절하고, 대체로 평화로워. 마지막으로 술주정뱅이 싸움 뒤치다꺼리한 게 언제였는지도 기억이 안 나. 그리고 부족들도 나한텐 신경 안 써.\n전체적으로, 여기서의 삶이 내 인생에서 제일 좋아. 여기선 자유롭고, 아무도 내게 이래라저래라 하지 않아.\n딱 하나 미치게 만드는 게 있다면 쥐들이야. 녀석들이 내 식량을 갉아먹고 식기도 망쳐놓으면서 날 괴롭혀. 도저히 없앨 수가 없어.";
			link.l1 = "아, 그래, 나도 그 꼬마 녀석들이 얼마나 성가신지 직접 겪어봤지...";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "쥐 문제라면 내가 이 도시에서 제일 불운한 사람인 것 같아. 다른 배들은 내 플뢰롱만큼 심하게 쥐한테 시달리지 않거든. 악셀 요스트는 어떻게든 쥐를 완전히 없앴다던데, 나는 털복숭이 놈들이 떼로 기어 다니고 있어.\n있잖아, 예전에 '쥐의 신'이라는 특별한 부적 이야기를 들은 적이 있어. 박쥐 얼굴처럼 생겼다더군. 이 부적만 있으면 쥐가 완전히 달아난다더라.\n아마 악셀이 쥐를 처리한 것도 그 덕분이겠지. 그는 바깥쪽에서 사람들이 가져오는 온갖 잡동사니를 사서 다시 팔거든.\n누가 그 부적을 내게 준다면, 왕의 몸값만큼이라도 내고 살 텐데!";
			link.l1 = "기억해 두지...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+", 이제 그만 마시는 게 좋겠어, 친구. 자칫하면 강도라도 당하거나 바다에 빠져 게밥이 될 수도 있으니까. 여기서는 술 너무 많이 마시면 목숨까지 잃을 수 있어, 조심해.";
				link.l1 = "흠... 네 말이 맞는 것 같아, 산초 - 헉! - 이제 충분히 마셨지. 신경 써줘서 고마워.";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "천만에, 친구. 내 최고 럼주 한 파인트에 겨우 스물다섯 페소야!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("네 건강과 네 선술집의 번영을 위하여, 친구!","바다의 모든 이들에게, 어디에 있든!","정의의 섬의 사람들이여!"), LinkRandPhrase("정의의 섬에, 그리고 영원히 번성하길!","어떤 항로를 잡든 바람이 늘 우리 편이길!","행운과 행복을 위하여... 그리고 여자들을 위하여!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "지금은 술 마시면 안 될 것 같아. 내 말 믿어...";
				link.l1 = "좋아...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "헤, 너 참 이상한 놈이구나... 여기, 정의의 섬에서 같이 시간 보낼 사람도 없냐? 너 혼자 여기서 술 마시게 두면 메리가 날 죽일 거야. 저녁에 같이 와서 새벽까지 신나게 놀아, 원하면.";
				link.l1 = "좋은 생각이야!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "문제없어, 친구. 삼백 페소만 내면 훌륭한 한 병을 줄게\n "+LinkRandPhrase("Spanish","Italian","French")+" 와인 - 그리고 원하는 만큼 쓸 수 있는 자리.";
				link.l1 = "고마워!";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "지금은 자면 안 될 것 같아. 내 말 믿어...";
				link.l1 = "좋아.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "무슨 말인지 모르겠네, 친구. 세레스호에 예쁜 아가씨가 기다리고 있는데 혼자 선술집에서 밤을 보내겠다고? 그럴 순 없어, 메리가 날 죽일 거야.";
					link.l1 = "아마 네 말이 맞을 거야...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "위층에서 저녁까지 쉬어도 되지만, 밤은 여기서 못 보내. 메리가 날 죽일 거거든. 미안해...";
					link.l1 = "좋아, 저녁까지 여기 있을게...";
					link.l1.go = "hall_night_wait";
					link.l2 = "좋아... 잠 안 자고도 어떻게든 해낼 거야.";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "20페소면 위층 침대에서 잘 수 있어. 언제 깨워줄까?";
			if(!isDay())
			{
				link.l1 = "아침에.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "해 지기 전에.";
				link.l1.go = "hall_night_wait";
				link.l2 = "다음 날 아침.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "생각이 바뀌었어. 자고 싶지 않아.";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
