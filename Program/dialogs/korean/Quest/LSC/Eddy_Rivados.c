// лидер клана ривадос - Чёрный Эдди
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "리바도스 땅에서 뭐 하는 거야, 백인 놈?";
			link.l1 = "현지인들과 인사 좀 나누고 있었어. 신경 쓰였다면 미안해.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "리바도스의 친구이자 훌륭한 사람을 맞이하게 되어 기쁘네! 치미셋이 자네가 그를 위해 해준 일을 내게 말해줬지. 리바도스 모두가, 나 역시, 이제 자네에게 빚을 졌네. 내 소개를 하지. 에드워드 블랙, 블랙 에디라고도 불리지. 리바도스 패거리의 두목이네.";
			link.l1 = ""+GetFullName(pchar)+". 하지만 이미 치미셋이 내 얘기를 했을 거라 생각해. 그가 꼭 말해주겠다고 약속했으니까...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "그리고 그는 그렇게 했소. 이제 우리 배들을 자유롭게 방문할 수 있소. 경비병들도 그대를 막지 않을 것이고, 우리는 그대를 반갑게 맞이할 것이오. 하지만 나르발들과는 조심하시오. 그대가 치미세트를 구한 걸 이미 알았을 테니, 그자들은 그걸 달가워하지 않을 것이오. 우리는 적이니까.";
			link.l1 = "고려해 보지. 따뜻하게 맞아줘서 고마워, 에디! 이제 치미셋과 이야기할 수 있게 해 주게.";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("They say that you are a close friend of Black Eddie, the head of Rivados. How did you do this?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Rivados claim you as their friend. How'd you do it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that the Narwhals have a price on your head. Are you scared?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> информационный блок
		case "Total_info": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "하얀 형제가 살아 있다고? 정말 기쁘군! 그럼, 네가 익사했다고 모두에게 말한 건 결국 나르발 놈들의 거짓말이었네...";
				link.l1 = "나도 너를 다시 보게 되어 기쁘다, 에디. 내 죽음에 대한 소문은 한참 과장된 거야.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "만나서 반갑군, "+pchar.name+". 소식이라도 있나?";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "에디, 너 혹시 네이선리얼 호크라는 사람 알아? 내가 알기로 그는 여기 있어야 해.";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "리바도스 패거리에 대해 좀 더 말해 줘.";
				link.l2.go = "rivados";
			}
			link.l9 = "별일 없어. 그냥 인사나 하려고 했어.";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "나타니엘 호크? 아니, 나는 그 사람을 몰라. 그는 리바도스 배에도 없고, 중립 구역에도 없어. 나발 패거리라면 얘기가 다르지; 우리는 그쪽엔 가지 않아.";
			link.l1 = "그렇군...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "리바도스 패거리는 오래전에 결성되었어. 이 버려진 배들의 도시에서 최초의 클랜이었지. 오십 년도 더 전에, 베탕쿠르 제독의 원정대가 서아프리카에서 여러 척의 대형 노예선을 이끌고 이곳으로 항해해 왔어. 타르타로스의 선창에는 카리브 해 플랜테이션으로 보내질 수백 명의 흑인 노예들이 가득 실려 있었지. 그 노예들 중에는 페드로 리바도스라는 남자가 있었어. 몇몇 포르투갈 신부들이 그에게 글을 읽고 쓰는 법을 가르쳤다고 하더군.\n그는 수십 명의 노예들을 족쇄에서 풀어주고 반란을 일으켰어. 안타깝게도 나머지 노예들은 그를 따르지 못했지. 반란은 진압당했고, 노예상들은 리바도스의 손발을 묶어 배의 선창에 가둬 굶주림과 갈증에 죽게 내버려 뒀어. 며칠 뒤, 날씨가 험악해지면서 베탕쿠르의 함대는 거센 폭풍에 휩쓸렸지.\n며칠이 지나, 악천후와 싸운 끝에 '산 아우구스틴'과 '타르타로스', 이 두 척만이 온전한 상태로 이 정의의 섬 한가운데에 갇히게 되었어. 그 사건들로 많은 이들이 죽었지, 흑인도 백인도. 하지만 더 많은 이들이 살아남았어. 전 노예들은 함께 새로운 삶을 시작했고, 해방자 페드로 리바도스를 기리며 자신들을 리바도스라 부르게 되었지.";
			link.l1 = "아주 흥미로운 이야기군... 고마워!";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок
		
		case "capper":
			dialog.text = "리바도스 영토에서 뭘 원하는 거지, 백인?";
			link.l1 = "내 이름은 "+GetFullName(pchar)+" 그리고 나는 도드슨 제독의 명령으로 여기 왔다. 블랙 에디와 이야기해야 해. 내가 알기로 그게 바로 너지.";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "그래, 나는 에드워드 블랙이야, 블랙 에디라고도 불리지. 자, 제독이 나한테 뭘 원하는지 말해 봐.";
			link.l1 = "'타르타로스'에 치미셋이라는 남자가 있어. 제독이 그를 풀어줄 의향이 있대.";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "이거 정말 좋은 소식이군. 치미셋은 우리 리바도스의 영적 지도자라서 모두가 그를 그리워하고 있지. 하지만 제독이 그의 자유를 대가로 뭔가를 원한다는 것도 이해하고 있어, 맞지?";
			link.l1 = "아무것도 아니야. 그는 그저 선의의 표시로 그를 풀어주고 싶을 뿐이야. 하지만 문제가 있어...";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "가라, 백인 놈아.";
			link.l1 = "전직 제독의 보선장이자 지금은 간수인 채드 카퍼가 이제는 나르발족에 합류해 배신자가 되었고, 제독의 통제 밖에 있소. 우리는 채드가 치미셋을 죽일 계획이라는 걸 알고 있소. 제독은 그런 일이 일어나길 원치 않소. 배신자를 제거하고 당신의 사람을 구출하기 위해 공동 작전을 제안하오.";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "네 말이 좀 이상하게 들리긴 하는데, 계속 말해 봐. 치미셋이 곤란에 빠졌나?";
			link.l1 = "그래. 채드는 그를 죽일 계획이야. 카퍼는 나르발들을 이용해서 도시를 장악하려고 하지. 우리가 치미셋을 구하려면 빨리 움직여야 해, 지금은 채드가 아무것도 의심하지 않으니까. 제독이 '타르타로스'에서 모든 경비를 데려갔어, 통로는 비었지. 여기 감옥 안쪽 문을 여는 열쇠가 있어. 가져가.";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "사람들을 모아 타르타로스에 가서 치미세트를 풀어줘. 모든 패는 네 거야.";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "덫 냄새가 나는데... 혹시 매복이라도 있으면 어쩌지? 만약 제독이 리바도스를 공격하기로 마음먹으면 어떻게 하지? 왜 직접 카퍼를 처리하지 않는 거지?";
			link.l1 = "도드슨이 말하길, 네가 치미셋의 목숨을 신경 쓴다고 하더군... 그는 할 만큼 했어: 여기 열쇠가 있고, 경비병들도 사라졌지. 이제 네가 안으로 들어가서, 채드를 처리하고, 네 사람을 구출하면 돼. 함정은 없다는 내 말을 믿어도 좋아. 아, 그리고 마지막으로 한 가지 더: 제독께서 치미셋의 생명과 자유를 대가로 채드의 목을 원하신다. 합의하는 건가?";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "치미셋의 생명은 리바도스에게 그 무엇과도 바꿀 수 없을 만큼 소중하다. 우리는 즉시 '타르타로스'로 이동하겠다. 하지만 너는 인질로 여기 남아 있어야 한다. 만약 매복이 있다면, 리바도스의 분노를 직접 겪게 될 것이다!\n지코모! 문 근처에 서서 우리 손님을 지켜봐라. 절대 밖으로 나가지 못하게 해. '타르타로스' 공격은 내가 직접 이끌겠다!";
			link.l1 = "행운을 빌어, 에디. 그리고 기억해라: 나는 차드 카퍼의 목이 필요하다!";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "치미세가 자유를 얻었어! 거짓말이 아니었구나, 백인. 이제 널 리바도스의 친구라 불러줄 준비가 됐어!";
			link.l1 = "기쁘군. 챈드 카퍼는 죽었나?";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "용서해 주시오, 백인 친구여. 당신은 우리를 위해 할 수 있는 모든 것을 다 했지만, 우리가 당신을 저버렸소... 내가 당신을 저버렸소! 그 망할 카퍼가 도망쳤소. 그와 함께 있던 나르발 두 놈은 죽였지만, 그 더러운 간수는 아래쪽 문을 통해 나르발 구역으로 헤엄쳐 도망쳤소.";
			link.l1 = "젠장... '타르타로스'에는 출구가 두 개 있다는 거 몰랐어?";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "우린 그 생각을 못 했어. 정문으로 공격했지...";
			link.l1 = "안타깝군. 난 그의 목을 기대하고 있었는데. 아쉽게 됐어. 이제 그는 계속 우리를 방해하겠지.";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "내 잘못을 인정하오. 하지만 우리는 적대적인 배들까지 따라갈 수는 없었소. 차드의 목 대신, 우리 우정과 존경을 받게 될 것이오. 이제부터는 우리 영토를 자유롭게 드나들 수 있소. 치미셋의 지혜도 분명 도움이 될 것이니, 필요한 게 있다면 그와 이야기해 보시오. 그리고 제독에게도 내가 그의 행동을 높이 평가했다고 꼭 전해 주시오.";
			link.l1 = "좋아.";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "잠깐! 우리가 차드를 잃었지만, 내가 그의 책상에서 몇 장의 서류를 발견했어. 우리가 도착했을 때 그가 이걸 보고 있었지. 여기 있어. 도움이 될지도 몰라, 하얀 형제여.";
			link.l1 = "하! 아마도... 챠드는 종이쪽을 아주 믿지...";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "여기는 언제나 환영받는 손님이오, 백인 친구. 모든 리바도스들에게 이 사실을 알리겠소. 행운을 빌지!";
			link.l1 = "너도 그래, 에디...";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Have you heard the latest news? The Rivados' insolence is out of control, they have attacked the admiral's prison and released their wizard!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Just think about it - those uppity Rivados dared to attack the 'Tartarus'! They say that the jailer, Chad Kapper, has escaped to the Narwhals...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("This is the height of impudence, isn't it? Attacking a military facility of the admiral! Aye, looks like Black Eddie is getting stronger...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
