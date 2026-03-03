// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "이봐, 나리, 왜 싸움을 걸었지, 응? 네가 우리 적이 아니라면 내 작업장에 볼일 없어. 나가!";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "아, "+GetFullName(pchar)+"! 자네의 업적에 대해 들었네. 도널드와 친구가 되고 우리 동맹이 된 건 잘한 일이야. 나르발들은 우정을 소중히 여길 줄 알지, 그건 확실히 말할 수 있어.";
					link.l1 = "그러길 바라지. 이제 네 도움을 받을 수 있을까?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "그래서? 뭐 원하는데?";
					link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 그리고 나는 그냥 돌아다니면서 사람들을 알아가고 있어. 내가 방해하고 있나?";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "아, "+GetFullName(pchar)+"! 자네의 업적에 대해 들었네. 도널드와 친구가 되고 우리 동맹이 된 건 잘한 일이야. 나르발들은 우정을 소중히 여긴다네, 그건 확실히 말할 수 있지.";
					link.l1 = "그러길 바라지. 이제 네 도움을 받을 수 있을까?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "아, "+GetFullName(pchar)+"! 또 얘기하고 싶어? 유감이지만, 나에겐 그럴 시간도, 의욕도 없어.";
					link.l1 = "좋아, 더 이상 귀찮게 안 할게.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "정확해! 너 때문에 귀찮아, 이봐. 나는 위르겐 슈미트, 나르발 클랜의 총기 제작자이자 대장장이야. 우리 사람들에게 무기를 공급하지. 하지만 좋은 칼이나 열쇠, 자물쇠를 만들거나 타워 머스킷의 기계장치를 수리하려면 시간이 걸려. 정말 많은 시간과 인내, 그리고 세심한 주의가 필요하지. 그래서 사람들이 나를 귀찮게 하는 걸 싫어해.";
			link.l1 = "무기를 만드나? 뭐 하나 주문할 수 있을까?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "아니. 나는 오직 나르발 클랜의 일원들에게만 무기를 만들어 준다네. 이것이 내 신조이고, 반드시 지킬 거야. 그러니 기대도 하지 마, 나리. 우리 클랜에 들어오거나 최소한 동맹이 되면, 그때 가서 얘기해 보지.";
			link.l1 = "좋아. 그럼 난 간다. 귀찮게 해서 미안했어!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "할 수 있지. 나르발의 친구라면 내 친구이기도 하니, 네 말을 듣고 있어.";
			link.l1 = "칼 하나 주문하고 싶어.";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "고 앨런 밀로우를 위해 특별한 검을 만들었다고 들었어. 그 브로드소드, 내가 봤는데 정말 훌륭한 무기더군. 나도 그런 걸 주문할 수 있을까?";
				link.l2.go = "narval";
			}
			link.l3 = "아직 생각이 없어. 좀 더 생각해보고 다시 올게!";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "하, "+GetFullName(pchar)+"! 아직도 안 죽었구나? 이거 참 신기하네! 정말 살아있는 거야?";
				link.l1 = "걱정 마, 유르겐. 나 살아 있어! 물에 빠져 죽을 뻔하진 않았으니까...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "아, "+GetFullName(pchar)+"! 뭐야, 뭘 원해?";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "네가 부탁한 특별한 쇳덩이 세 개를 가져왔어. 한번 봐, 네가 원하던 게 맞는지?";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "한번 봐봐, 유르겐. 바닥에서 흥미로운 철 주괴를 찾았는데, 네가 말한 것보다 훨씬 무거워. 적어도 다섯 파운드는 될 거야.";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "칼을 하나 주문하고 싶은데.";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "검 값으로 두블룬을 더 가져왔어.";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "고(故) 앨런 밀로우를 위해 특별한 검을 만들었다는 얘기를 들었어. 그 브로드소드도 봤는데, 정말 훌륭한 무기더군. 나도 그런 걸 주문할 수 있을까?";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "내 주문 때문에 왔어. 벌써 다 끝났겠지, 맞지?";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "아니야, 별일 아니고, 그냥 인사하고 싶었어.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> заказ клинков
		case "blade":
			dialog.text = "좋아. 하지만 어떤 주문이든 특별한 조건이 있으니, 먼저 잘 듣도록 해.";
			link.l1 = "듣고 있어.";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "나에게서 칼은 한 번, 한 자루만 주문할 수 있다. 내가 만드는 건 특정 무기가 아니니, 종류만 말하라—레이피어, 세이버, 브로드소드 중 하나다. 신중히 선택해라. 칼의 최종 특성과 품질은 내가 그때그때 가진 재료에 달려 있다\n이제, 주문 제작에는 이십 일이 걸린다. 나는 두블룬만 받는다. 천 닢이다. 선불로 내라.";
			link.l1 = "정말이네! 비싸구만...";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "값이 비싸지. 하지만 나는 훌륭한 칼을 만들기 때문에 그만한 값어치는 해. 어차피 결정은 네가 하는 거니까, 부담 갖지 마.";
			link.l1 = "알겠어, 유르겐. 그래, 주문하고 싶어.";
			link.l1.go = "blade_3";
			link.l2 = "흠. 너한테 뭔가를 주문하기 전에 생각할 시간이 좀 필요해. 이 얘기는 나중에 하자!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "좋아. 그럼 두블론을 내놔.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.blade_pay = PCharDublonsTotal();
				link.l1 = "여기요, 부디. 나는 가지고 있어 "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "흠. 안타깝게도 지금은 가지고 있지 않아. 하지만 꼭 가져다줄 테니, 그때 다시 이야기하자.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "그래서 이게 너의 최종 선택이야? 정말 확실해?";
			link.l1 = "그래, 맞아.";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // оплата
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.blade_pay));
			Log_Info("You have given "+sti(npchar.quest.blade_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "훌륭하군. 내 일과 재료값을 이미 치렀으니, 이제 바로 시작할 수 있지.";
				link.l1 = "주문해도 될까요?";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "좋아. 네가 준 두블룬 받아들이지. 나한테 가져와야 해 "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+" 더.";
				link.l1 = "내가 그것들을 손에 넣으면 당신에게 가져다주겠소.";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "물론이지! 어떤 종류가 좋아? 레이피어, 세이버, 아니면 브로드소드?";
			link.l1 = "레이피어. 나는 우아하고 가벼운 무기가 좋아.";
			link.l1.go = "rapier";
			link.l2 = "세이버지. 내 생각엔, 그게 최적이야.";
			link.l2.go = "sabre";
			link.l3 = "브로드소드지! 베고, 찍어!";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "원하시는 대로 하겠습니다. 주문하신 물건은 이십 일 뒤에 오십시오, 그전에는 안 됩니다.";
			link.l1 = "고마워! 스무 날 뒤에 다시 보자. 잘 있어, 유르겐.";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "원하시는 대로 하겠습니다. 주문하신 것은 이십 일이 지나야 찾으러 오십시오, 그 전에는 안 됩니다.";
			link.l1 = "고마워! 스무 날 뒤에 보자. 잘 있어, 유르겐.";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "원하시는 대로 하겠습니다. 주문하신 물건은 이십 일 뒤에 오십시오, 그전에는 안 됩니다.";
			link.l1 = "고마워! 스무 날 뒤에 보자. 잘 가, 유르겐.";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "그래. 검이 준비됐어. 자, 가져가서 써 보시오. 손에 쥐는 순간 그 값어치를 알게 될 거요.";
			link.l1 = "고마워, Jurgen.";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// заказ палаша Нарвал для Мэри
		case "narval":
			dialog.text = "안타깝지만, 친구여, 두 가지 이유로 거절해야겠군. 첫째, 그런 브로드소드라면 나르발 클랜의 일원, 그것도 특별한 사람을 위해서만 만들어주지. 둘째, 그걸 만들 재료도 없어.";
			link.l1 = "그 특별한 쇠란 게 뭐지? 바닥에서 건져 올렸다고 들었는데...";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "맞아. 이 금속 조각들이 우리 얕은 바다 여기저기에 흩어져 있어. 어떻게 생긴 건지는 나도 몰라. 하지만 이 쇠는 특별해서 녹슬지 않고, 이걸로 만든 칼날은 무뎌지지도 않아. 그러니 네가 그 쇠를 구할 수 있다면, 우리가 이 문제를 해결할 수도 있겠지. 하지만 아직 문제가 하나 있어. 너는 나르발이 아니잖아...";
			link.l1 = "흠. 그게 정말 중요해?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "그래. 내 변덕이라 생각할 수도 있겠지만, 그런 브로드소드라면 오직 나르발을 위해서만 만들어 주겠다.";
			link.l1 = "음... 좋아, 인정하지. 하지만 내게 한 가지 생각이 있어. 이 칼을 나르발 클랜의 일원에게 주문해도 될까?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "흠. 네가 쇠를 가져온다면 만들어 줄 수 있지. 내 원칙에 어긋나진 않아... 그런데 누구를 위해 이 브로드소드(넓은 칼)를 만들어 달라는 거지?";
			link.l1 = "붉은 메리에게 주는 거야. 그녀는 나르발 클랜 출신이고, 이런 훌륭한 무기를 가질 자격이 있어.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "하! 그 정도는 나도 알아챌 수 있었지. 내가 너무 늙었나 봐... 뭐, 동의하지. 메리는 이런 선물을 받으면 정말 기뻐할 거야, 분명히... 쇠를 가져오면 내가 브로드소드 만들어 줄게. 칼날 값은... 에이, 됐다, 그냥 공짜로 만들어 주지. 이건 너뿐만 아니라 우리 둘이 주는 선물이 될 테니까.";
			link.l1 = "고마워! 철이 얼마나 필요해?";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "우리가 바닥에서 찾아낸 조각들은 전부 똑같았어 - 각각 1파운드였지. 나도 그런 조각 세 개가 필요해.";
			link.l1 = "좋아. 내가 그들을 찾아볼게. 그리고 다시 이야기하자.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// кладем гигантский кусок метеорита на дно
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("Meteorite in the locator " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "어디 보자... 그래, 맞아! 바닥에서 그렇게 작은 조각들을 찾는 게 힘들었나?";
			link.l1 = "글쎄, 뭐라고 해야 할까... 메리는 그런 고생을 할 만한 가치가 있지, 안 그래?";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "어디 보자... 이거 참 신기하군! 그래, 바닥 철이 맞긴 한데 이렇게 큰 조각은 처음 본다네. 이 정도면 도검 하나 만들기에 충분하겠어. 찾기 힘들었나?";
			link.l1 = "글쎄, 뭐라고 해야 할까... 메리는 그만한 고생을 할 만한 여자 아니겠어?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "점점 더 마음에 들어, "+pchar.name+"... 좋아, 그럼. 이제 우리 아름다운 아마존을 위해 내가 일할 차례군. 브로드소드 만드는 데 이틀 걸릴 거야, 다른 주문은 제쳐두지.\n모레 메리를 나한테 데려와. 메리한텐 말하지 마, 깜짝 선물이니까. 아이처럼 기뻐할 거야.";
			link.l1 = "좋아, 유르겐. 거래 성사야! 내일모레 보자!";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", 귀찮게 하지 마. 너 그 브로드소드 제때 완성하길 바라는 거 아니야?";
			link.l1 = "그래, 알겠어. 나 간다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("거기서 뭐 하는 거야, 응? 도둑놈!","저것 좀 봐! 내가 잠깐 생각에 잠긴 사이에, 네가 내 가슴을 뒤지기로 했군!","내 상자를 뒤지려고 했나? 가만두지 않겠다!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("이봐, 무기는 집어넣는 게 좋겠어. 그거 들고 있으면 신경이 곤두서거든.","여기서는 칼을 들고 돌아다니는 거 용납 안 해. 집어넣어.","이봐, 중세 기사처럼 칼 들고 설치지 마. 집어넣어, 너한테 안 어울리거든...");
			link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 도시의 시민이니 칼을 내려주겠나.","이봐, 나는 이 도시의 시민이니 칼을 거둬 줘.");
				link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"조심해라, 친구. 무기 들고 돌아다니면 나까지 불안해질 수 있으니까...","사람들이 무기를 뽑은 채 내 앞을 지나가면 싫어. 무섭거든...");
				link.l1 = RandPhraseSimple("알겠어.","내가 가져간다.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
