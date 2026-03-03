// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕, 안녕... 너 여기 처음이냐? 네 얼굴은 본 적이 없는 것 같은데. 자기소개를 하지. 나는 주세페 파치오, 이 작은 정의의 섬에서 문제 해결을 전문으로 하는 사람이야.";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 맞아요, 저 여기 처음이에요. 궁금해서 그런데, 무슨 문제들을 해결하시는지 여쭤봐도 될까요?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, 또 만났군, 자네\n "+pchar.name+"! 내 누추한 집에 무슨 일로 왔나?";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "파지오, 나 한 클랜과 심각한 갈등이 있어. 이 문제를 해결해야 해.";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "주세페, 나는 아돌프 바르비에라는 남자를 찾고 있어. 최근에 그와 선술집에서 함께 술을 마셨다고 들었는데...";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "주세페, 자네는 술에 완전히 강하다고들 하더군. 아무리 마셔도 끝까지 버틴다지.";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && PCharDublonsTotal() >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "네 게임에 참여할 준비가 됐어. 여기 내 판돈이야.";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "나는 각 클랜 영지에 들어가려면 지금 쓰는 암호가 뭔지 알고 싶어.";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("재미있는 이야기라도 있나?","섬에 무슨 새로운 일이 있었나?","최근 소문 좀 들려줄래?");
				link.l2.go = "rumours_LSC";
				link.l3 = "별일 없어, Giuseppe. 그냥 너를 보고 싶었을 뿐이야.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "별별 일 다 하지, 자네, 별별 일 다 해. 예를 들면, 나는 제독과 클랜들 사이에서 중재 역할을 하지. 이미 알고 있을지도 모르겠지만, 리바도스와 나르발, 그리고 제독은 서로 원수지간이야. 일이 꼬이면 내가 중재자로 나서지.\n게다가, 제독이 클랜들에게 식량을 팔 때도 나는 종종 중립 역할을 맡아. 하지만 이건 내 일의 아주 작은 부분일 뿐이야. 그러니 리바도스나 나르발과 문제가 생기면 주저 말고 내게 도움을 청하게, 뭔가 방법을 찾아보지.";
			link.l1 = "좋아. 생각해 보지.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "어느 클랜?";
			link.l1 = "나르발족.";
			link.l1.go = "parol_nrv";
			link.l2 = "리바도스.";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "도널드 그린스펜을 보고 싶지, 맞지?";
			link.l1 = "맞아. 그래서, 암호를 알고 있나?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "블랙 에디를 보고 싶지, 맞지?";
			link.l1 = "그런 셈이지. 그래서, 암호를 알고 있나?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "물론이지! 하지만 먼저 자세한 내용을 좀 알려줄게. 암호는 한 단어로만 이루어져 있고, 매주 바뀌어: 매달 7일, 14일, 21일, 28일에 바뀌지.\n그러니 실수하지 않으려면 오늘 날짜를 잘 확인해. 마지막으로, 너도 알다시피 이건 자선사업이 아니야. 암호 하나에 50두블룬이야. 기억해, 두블룬만 받아.";
				link.l1 = "오십 두블론? 그건 엄청난 금액이잖아!";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "그래, 이봐 꼬마. 값은 알지? 50두블룬 있냐?";
				if (PCharDublonsTotal() >= 50)
				{
					link.l1 = "그래. 돈 가져가.";
					link.l1.go = "parol_pay";
				}
				link.l2 = "유감이지만, 지금은 없어. 나중에 혹시...";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "자, 자, 얘야, 진정해라. 욕심내지 말고, 날 믿어. 내 정보가 진짜 얼마짜린지 나는 잘 알지. 너는 그냥 배들 사이를 돌아다닐 수 있는 게 아니야\n "+pchar.questTemp.LSC.parol+" 그렇지? 그래. 그러니까 돈 좀 잃을 각오는 해야 해... 자, 오십 두블룬 낼 준비됐어?";
			if (PCharDublonsTotal() >= 50)
			{
				link.l1 = "그래. 돈 가져가.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "유감이지만, 그런 돈은 없어. 나중에 혹시...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveDublonsFromPCharTotal(50);
			dialog.text = "좋아! 거래하게 되어 기쁘군. 현재 암호는 "+pchar.questTemp.LSC.parol+" 는: '"+sTotalTemp+"'. 잘 기억해 두고 실수하지 마라, 그렇지 않으면 네 목숨값으로 동전 한 닢도 주지 않겠다.";
			link.l1 = "알아, 알아... 고마워!";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "아, 물론이지, 내 오랜 친구 아돌포! 그래, 그와 얘기했었지. 있잖아, 내 사랑, 나는 내 돈을 돌려받아서 정말 기뻤어. 다시는 못 볼 줄 알았던 돈이었거든! 아돌포가 자기 훌륭한 라이플을 담보로 큰돈을 빌렸는데, 내 돈을 갚는 데 애를 먹었지\n나는 돈을 돌려받을 희망을 완전히 잃고, 그 슈투첸을 우리 모두가 사랑하는 악셀 요스트에게 팔려고 했어. 그런데 갑자기 아돌포가 내 금화를 가져왔지! 알고 보니 그는 슈투첸을 되찾을 만큼의 동전뿐 아니라, '산타 플로렌티나'의 맨 앞에 있는 세실 갈라드의 선실까지 살 수 있을 만큼 모았더라고!\n확실히, 반쯤 잠긴 창고에서 사는 것보다 훨씬 낫지\n그래서 아돌포는 라이플도 되찾고, 새 집도 얻고, 나는 내 돈을 찾았어. 그가 술을 산다는데 내가 왜 같이 한잔 안 하겠어?";
			link.l1 = "아, 그렇지! 마실 이유가 아주 많았지. 그것도 공짜로... 고마워, 주세페. 네 덕분에 정말 큰 도움이 됐어. 이제 아돌프를 어디서 찾을 수 있는지 알겠어.";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "항상 기쁜 마음이지, 자기야. 하지만 아돌포를 그의 선실에서 찾으려면 저녁이 될 때까지 기다려. 지금은 무슨 일로 바쁘게 돌아다니고 있거든... 그래, 그리고 나도 자주 찾아와. 우리 이야기 좀 하자!\n";
			link.l1 = "내 선실이 생기면 초대할게... 잘 가, 행운을 빌어!";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "어? 불이라도 난 것처럼 내 집에 막 들이닥치는 거야? 네가 누군데??";
					link.l1 = "너희 정의... 독살자 놈!";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "살려줘! 맹세해, 내가 원해서 한 게 아니야! 놈들이 내 머리에 총을 들이댔어...";
					link.l1 = "닥쳐. 그건 나도 안다. 마지막 그 자식은 어디 있지? 마르첼로 외눈박이는 어디 있냐?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "맹세해, 그놈들이 나를 강제로 시켰어! 나는 이미 제독에게 전부 말했어! 나는 저항할 수 없었어, 그놈들은...";
					link.l1 = "닥쳐. 그건 나도 알아. 마지막 그 놈은 어디 있지? 마르첼로 사이클롭스는 어디에 있어?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "뭐... 뭐라고 했어?";
			link.l1 = "다 알고 있다, 이 자식아. 너 찰드 카퍼랑 짜고 있었지. 독탄 럼주 한 통을 제독에게 가져왔잖아. 이제 기도나 해라, 이 비참한 놈아...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "잠깐! 멈춰! 살려줘! 맹세해, 내가 억지로 한 거야! 걔네가 내 머리에 총을...";
			link.l1 = "닥쳐. 그건 나도 알아. 마지막 그 자식 어디 있지? 마르첼로 외눈박이는 어디에 있어?!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "나... 나... 나도 모르겠어!";
			link.l1 = "거짓말하지 마, 이 쓰레기야! 다 보여. 사이클롭스는 어디 있지?";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "그... 그가 카퍼한테서 어떤 명령을 받고 떠났어. 어디 있는지 나도 몰라!";
			link.l1 = "또 거짓말이군. 너 다 알고 있잖아. 겁쟁이 짓 그만해, 이 더러운 놈아 - 카퍼는 죽었으니 이제 널 해칠 수 없어. 하지만 마르첼로가 어디 있는지 말하지 않으면 지금 당장 돼지처럼 널 도륙해버릴 거다! 채드가 키클롭스에게 무슨 명령을 내렸지?";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "그가 그를 보내서... 레드 메리를 죽이라고 했어.";
			link.l1 = "뭐?! 지금 말해 봐, 그가 어떻게 그럴 수 있다는 거지? 그녀의 선실 안에 들어가는 건 불가능해! 도대체 어떻게 그녀를 죽일 생각이야?!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "그는 대장장이가 밖에 나간 사이에 위르겐의 선실로 들어갈 거야. 그 다음엔 창고 맨 아래로 이동해서, 창고를 가로질러 메리의 선실에 도착할 거고\n그 다음엔 그저 그 아가씨가 등을 돌리거나 잠들 때까지 기다리기만 하면 된대. 그게 바로 채드가 내게 말한 전부야. 난 더는 아무것도 몰라, 맹세해!";
			link.l1 = "그 정도면 됐다. 언제 갔지? 내가 묻잖아, 사이클롭스가 '케레스 대장간'에 언제 갔는지?";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "그자는 이미 위르겐 선장의 선실에 있겠지... 아니면 아래 화물창에 있을지도...";
			link.l1 = "젠장! 섬을 빙 돌아서 헤엄칠 시간 없어! 나한테 나르발 놈들 배로 가는 암호를 말해! 어서 말해, 거짓말하면 난 어떻게든 살아남겠지만, 넌 반드시 죽게 될 거야!";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"'...";
			link.l1 = "알겠어. 이제 그 소녀가 살아남길 빌어.";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "나는 내가 아는 건 이미 다 말했어! 맹세해!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "그... 그는 '플레론' 안 어딘가에 있어. 채드가 거기 숨어서 다음 명령을 기다리라고 시켰거든.";
			link.l1 = "알겠어. 진짜여야 할 텐데...";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "그래? 자네, 어느 클랜이 괴롭히고 있나?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "나르발.";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "리바도스.";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "제독의 해적들.";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "그런 거 없어. 농담이었어, Giuseppe, 나 괜찮아.";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "글쎄, 사실 갈등이라기보단 그냥 작은 오해일 뿐이야, 헤헤. "+sti(npchar.quest.price)+"  두블론만 있으면 네 문제는 하루 만에 해결될 거야.";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "그래, 그 얘기 들었지. 꽤나 소란을 피웠더군, 내 사랑. 하지만 빠져나갈 방법이 있어. "+sti(npchar.quest.price)+" 두블론만 내면 네 문제는 하루 만에 해결될 거야.";
				else dialog.text = "네가 저지른 학살에 대해 정의의 섬 전체가 다 알고 있어. 도와주기 쉽지 않겠지만, 가능성은 있어. "+sti(npchar.quest.price)+" 두블론을 주면 네 문제를 해결해 보겠다.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "여기, 동전이나 받아서 알아서 해.";
				link.l1.go = "pay";
			}
			link.l2 = "안타깝게도 지금은 두블룬이 충분하지 않아. 하지만 나중에 가져올 테니, 그때 다시 이야기하자.";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "글쎄, 사실 갈등이라고 할 것까진 없고, 그냥 작은 오해일 뿐이야, 헤헤. "+sti(npchar.quest.price)+"  두블룬만 있으면 네 문제는 하루 만에 해결될 거야.";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "그래, 그 얘기 들었어. 꽤 소란을 피웠더군, 내 친구. 하지만 빠져나갈 방법이 있어. "+sti(npchar.quest.price)+"  두블론만 내면 네 문제는 하루 만에 해결될 거야.";
				else dialog.text = "네가 저지른 학살에 대해 정의의 섬 전체가 다 알고 있어. 도와주기 쉽지 않겠지만, 가능성은 있어. "+sti(npchar.quest.price)+" 두블론을 주면 네 문제를 해결해 보겠다.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "여기, 동전이나 받아서 알아서 해.";
				link.l1.go = "pay";
			}
			link.l2 = "안타깝게도 지금은 두블룬이 충분하지 않아. 하지만 나중에 가져올 테니, 그때 다시 이야기하자.";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "글쎄, 사실 갈등이라고 할 것도 없고, 그냥 작은 오해일 뿐이야, 헤헤. "+sti(npchar.quest.price)+" 두블룬만 내면 네 문제는 하루 만에 해결될 거야.";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "그래, 들었지. 꽤 소란을 피웠더군, 내 친구. 하지만 빠져나갈 방법이 있어. "+sti(npchar.quest.price)+" 두블룬만 있으면 네 문제는 하루 만에 해결될 거야.";
				else dialog.text = "네가 저지른 학살에 대해 정의의 섬 전체가 다 알고 있어. 도와주기는 쉽지 않겠지만, 가능성은 있어. "+sti(npchar.quest.price)+" 두블론을 주면 네 문제를 해결해 보겠다.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "여기, 동전이나 받아서 알아서 해.";
				link.l1.go = "pay";
			}
			link.l2 = "안타깝게도 지금은 두블룬이 충분하지 않아. 하지만 나중에 가져올 테니, 그때 다시 이야기하자.";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveDublonsFromPCharTotal(sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("You have given "+sti(npchar.quest.price)+" doubloons");
			dialog.text = "훌륭해. 이제 앉아서 좀 쉬어. 내가 네 문제를 해결할 때까지 내 선실에 머무르는 게 좋겠어. 더 이상 일을 악화시키지 않았으면 하거든, 내 사랑.";
			link.l1 = "좋아...";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("One day later..."+ NewStr() +"Fazio has dealt with the conflict", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "어서 와라, 내 아들! 저놈들 전부 거짓말쟁이야, 허허. 내 머리가 남들보다 좀 더 단단할 뿐이지, 나도 너처럼 똑같은 인간이라 럼주 마시면 취한다. 사람들은 취하려고 럼을 마시지, 그게 럼의 유일한 목적이야. 그거 생각해 본 적 있냐, 얘야?";
			link.l1 = "정말 그렇지.";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "나랑 재미있는 게임 한 판 할래? 이름은 '바닥까지 들이켜라!'야, 하하! 이미 들어봤겠지? 맞지?";
			link.l1 = "그래, 그런 소문이 좀 돌았지... 난 그걸 '상 위에 얼굴 박기'라고 부르겠어.";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "하하하, 이보게, 자네 덕분에 이 늙은이가 한바탕 웃었구먼, 더 무슨 말을 하겠나! '얼굴을 탁자에!' 이 말은 기억해 두지... 자, 어때? 백 두블룬 걸고 한 판 할 텐가?";
			link.l1 = "백 더블룬?";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "그래, 그리고 진 놈이 술값 내는 거다. 콜?";
			if (PCharDublonsTotal() >= 100)
			{
				link.l1 = "그래, 거래지. 내 판돈 여기 있다.";
				link.l1.go = "drink_4";
			}
			link.l2 = "흠. 내게 그렇게 많은 두블룬은 없어.";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "그래, 그걸 구하면 나한테 와. 그럼 같이 한 판 하자!";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveDublonsFromPCharTotal(100);
			Log_Info("You have given 100 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "훌륭해, 내 친구! 그럼 밤 아홉 시에 산초의 선술집에서 보자고! 그래, 네 판돈은 네가 늦으면 내가 갖는 거야, 그게 규칙 중 하나지. 하지만 넌 늦지 않을 거지, 이 친구?";
			link.l1 = "그래, 주세페. 병 싸움할 준비나 해!";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "그리고 너, 그리고 너도, 내 친구야! 얼굴을 테이블에 박아라! 하하!";
			link.l1 = "아홉 시에 선술집에서 보자!";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "자, 내 친구, 이제 테이블에 입 맞출 준비 됐나, 헤헤? 착한 산초가 이미 럼을 가져왔지. 규칙은 굳이 설명 안 해도 되겠지? 아주 간단해. 한 병에서 번갈아 마시다가 누가 먼저 쓰러지나 보는 거야.\n그래, 우리 얘기하자고, 꼭 얘기해야지! 괜찮은 사람들과 대화하는 건 정말 멋진 일이잖아, 안 그래? 그리고 네가 이기면 산초에게서 상을 받아갈 수 있어. 준비됐나?";
			link.l1 = "그래, 그렇다고 하겠어. 시작하자, Giuseppe!";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "죽은 자 위에 열다섯 명... 힉! 아하! 요호호... 그리고... 술병...";
			link.l1 = "영광스러운...";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
