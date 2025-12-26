// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "뭘 원하지?";
			link.l1 = "가봐야겠군...";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "젠장, 대체 너 누구야?";
				link.l1 = "안녕하십니까, 로페 나리. 아직 서로 인연이 없었지만, 지금이야말로 인사를 나누기에 좋은 때겠지요. 특히 지금처럼 제가 이 어려운 상황에서 나리께 도움을 드리고 싶은 마음이 간절할 때는 더욱 그렇습니다...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "뭘 원하지?";
				link.l1 = "가야겠군...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "도움이라고? 내가? 이런 일이 다 있군! 나리, 이런 관대함이 어디서 나오는지 좀 알려줄 수 있겠소?";
			link.l1 = "물론이지. 나는 네 전 선장인 에스베르도 카바냐스를 찾고 있어, 시간이 많지 않다네... 가능하다면 그가 비밀로 하는 그 장소에서 그를 만나고 싶어. 그보다 더 좋은 건 내가 그보다 먼저 그곳에 도착하는 거지.";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "하하! 내가 이 한심한 놈한테 입 다물라고 했지! 파란 호박, 맞지?";
			link.l1 = "옳은 방향으로 생각하고 있소, 나리.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "그럼 서두르자고. 나를 여기서 빼낼 방법만 찾으면, 내가 아는 모든 걸 다 이야기해 주지. 어떻게 내가 이 구덩이에 처박히게 됐는지 알고 있나?";
			link.l1 = "전반적으로, 그래, 그렇다.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "그 일이 벌어졌을 때 나는 완전히 만취 상태였어. 젠장, 그 빌어먹을 바텐더 놈! 아무것도 기억이 안 나. '칸타브로'의 선창에서 깨어났을 때야 비로소 전부 들었지. 그냥 우리가 떠나기만 했어도 모든 게 끝났을 거야, 사령관이랑 알칼데 둘 다 눈감아주려고 했으니까. 그런데 그 망할 돈 에스베르도 놈이 날 감옥에 처넣었지. 네가 생각하기엔 '정의를 위해서' 그랬다고? 천만에, 그 악당은 내 호박 몫을 가로채고 싶었던 거야. 해변에서 찾은 것보다 물속에 더 많은 호박이 있을 거라고 말한 것도 나였고, 그걸 꺼낼 방법을 알아낸 것도 나였어. 나한테 두둑한 몫이 돌아올 예정이었지, 그런데... 아, 그 개자식! 에휴, 그 얘긴 이제 그만하자. 알칼데도, 사령관도, 돈 데 톨레도도 내가 여기서 썩고 있는 걸 달가워하지 않아. 비둘기장을 뒤집어놓은 그 촌놈이랑 소 같은 마누라만 아니었어도... 어쨌든, 네가 날 도와주는 데 반대하지 않을 거야. 총독한테 가서 내가 유럽에서 온 옛 친구인 척 해, 내가 직접 확인해줄 테니까. 그런데, 네 이름이 뭐지?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+", 훌륭해. 돈 디에고 데 톨레도에게 가서 조언을 구해 봐. 기억해, 너에게는 사흘밖에 없어; 그 뒤로는 '칸타브로'를 쫓아도 소용없을 거야. 나를 풀어주면 그 자식 카바냐스를 상대하는 데 필요한 모든 걸 줄게.";
			link.l1 = "곧바로 총독을 뵈러 가겠습니다, 로페 나리. 우리 둘 모두를 위해 이 상황을 해결할 수 있도록 최선을 다하겠습니다.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "그래서 그 사기꾼 놈이랑 그 쫑알대는 암탉도 결국 복수를 했고, 나도 드디어 이 구덩이에서 벗어나게 됐군. 고맙소, 나리, 자네 할 일은 다 했네. 이제 내 차례를 하게 해주게.";
			link.l1 = "나 다 듣고 있어!";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "좋아. 지난번 순찰 중에 우리는 폭풍을 만나 항로에서 벗어났지. 우리는 신선한 물을 보충하려고 모스키토 해안에서 멀지 않은 서부 본토 해변에 상륙했어. 거기서 우리는 푸른 호박이 풍부하게 매장된 곳을 발견했지. 내가 탐사를 좀 해봤더니, 물속에 그게 한 무더기나 있더군. 그걸 채취하려면 더 좋은 장비가 필요해서, 나중에 다시 오기로 결정했지.\n에스베르도는 인디언들이 잠수해서 호박을 모을 수 있도록 아바나에서 긴 보트 다섯 척을 샀어. 그 다음 이야기는 알다시피, 그 악당이 나를 내쫓고 도망쳤지. 모스키토 해안, 블루웰드 북쪽에서 그놈을 찾아. 서둘러야 해―내 계산으로는 거기까지 일주일 정도밖에 없어. 그놈이 호박을 캐는 한가운데서 붙잡아서, 그놈 호박 다 빼앗고 배를 여러 번 찔러주길 바란다. 하지만 조심해라, 내 예전 선장은 싸움도, 뱃일도 능한 놈이니까. 행운을 빈다, 나리.";
			link.l1 = "너도 잘 지내라, Lope. 잘 가!";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "무엇을 물어보고 싶으신가요, 나리?";
			link.l1 = "돈 몬토로에 관해서라면, 우리는 오래된 지인이지. 그의 불운을 알게 되었을 때 정말 마음이 아팠네. 돈 디에고 데 톨레도가 나를 자네에게 보냈네, 자네가 이미 우리 공통의 친구를 구하려고 했다고 하더군...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "흠... 나리, 이건 좀... 예상 밖이지만, 로페의 친구를 만나서 기쁘오! 그는 이미 한동안 운이 없었는데, 이제 또 이런 일이...";
			link.l1 = "우리가 그를 위해 뭘 할 수 있겠어? 고귀한 이달고가 이런 사회의 쓰레기들 사이에서 썩게 둘 순 없지!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "장사꾼이군! 불쌍한 로페를 돕는 건 쉽기도 하고 어렵기도 하지. 나는 로페가 운 나쁘게도 언쟁을 벌인 그 장사치와 얘기를 나눠봤어. 그자가 우리에게 오백 두블론을 내면 절반쯤은 봐주겠다고 하더군. 자기와 아내가 겪은 '고통'에 대한 값치고는 꽤 큰돈이지. 안타깝게도 나는 필요한 돈의 절반, 이백오십 두블론밖에 모으지 못했어.";
			link.l1 = "그러니까 내가 너한테 두블론 250개를 더 가져오면, 돈 로페가 풀려나는 거냐?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "그래. 그 욕심 많은 놈이 로페가 모든 피해를 보상했다고 소문을 내주겠다고 약속했지. 그리고 총독에게도 자신을 용서해 달라고 부탁할 거야.";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "지금 당장 필요한 돈을 가지고 있지. 자, 이 탐욕스러운 부르주아가 이 돈에 목이 메게 해 줘라.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "최대한 빨리 돈을 구해 오도록 하겠다.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "내 귀를 의심하겠군! 나리, 분명 주님께서 당신을 보내신 게 틀림없소!";
			link.l1 = "언제 우리 사람을 풀어줄 거야?";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "그 말을 들으니 기쁘군, 나리. 자네는 로페의 진정한 친구이자 진정한 귀족이야.";
			link.l1 = "잘 가라!";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "돈 가져왔어?";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "지금 당장 필요한 돈을 가지고 있네. 자, 이 탐욕스러운 부르주아가 이 돈에 목이 메게 해 주지.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "아직 진행 중이야.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "오늘 밤 그 교활한 놈에게 돈을 가져다줄 거야.\n우리 친구를 풀어주라는 명령이 정오쯤엔 내려질 거라고 믿어.\n그리고 나중에 다 같이 모여서 축하할 수 있길 바라는데?";
			link.l1 = "알겠어요, don Rosario 나리. 이제 가봐야겠어요. 또 봐요!";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "곧 우리 친구가 자유의 몸이 될 거야!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "이봐, 내 배에서 대체 뭐 하는 거야? 내가 널 초대한 기억 없는데, 응?";
			link.l1 = "진정해, Geffrey. 나는 Tyrex에서 온 사람이야, 선박 비단 거래 때문에 왔어.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "아-아, 그래, 그럼 얘기해 보자. 그 자가 뭘 꾸미고 있는 거지? 나는 이미 밀수업자들과 얘기했어; 내 생각엔, 그놈들이 물건값을 꽤 제대로 쳐주더라고...";
			link.l1 = "얼마나 되오, 물어봐도 되겠소?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "한 롤에 1,300페소. 괜찮은 값이라고 생각해.";
			link.l1 = "그래, 그리고 타이렉스는 빵 한 개에 금화 네 닢을 원해. 한 푼도 깎아주지 않아. 내가 말하는 건 두블룬이야. 그가 그 가격에 맞는 구매자를 찾아오라고 내게 일을 맡겼지.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "하하하, 꼬마야, 운이 좋구나! 마르쿠스 녀석 입맛이 대단하지! 좋아, 그런 손님을 한번 찾아봐라. 네가 애쓰는 꼴 구경하면 재미있겠군.";
			link.l1 = "그래, 이거 다 존나 웃기고 재밌지. 내가 행복해 보여? 안 그래. 그러니까 웃음 그만두고 나 좀 도와줘.";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "좋아, 좋아, 친구야... 이런, 너 농담 별로 안 좋아하는구나? 뭐, 이해해. 타이렉스 놈의 망상 때문에 네가 잘못한 건 아니지. 우리 모두 이 일에 휘말릴 거야, 믿어라. 그런데 내가 도대체 어떻게 도와줄 수 있겠냐? 이건 상점에 팔 수도 없고, 세관도 답이 아니야. 밀수꾼들밖에 남지 않았지. 또 누가 이걸 필요로 하겠냐? 생각나는 사람이라도 있어?";
			link.l1 = "히스파니올라 때부터 계속 생각해 왔지... 뭐, 됐다. 정기적으로 물건을 사줄 손님을 찾을 시간이 두 달밖에 없어. 뭔가 조치를 취해야겠군. 네 명령은 가장 가까운 만에 상륙해서 수리를 진행하는 거다.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "두 달이라고?! 뭐야, 이게? 아, 젠장. '스네이크'는 수리도 해야 하고 청소도 해야지, 안 그러면 바크 한 척도 못 쫓아가겠지. 이봐, 프랑스 창녀들! 대머리 제프리의 선원들이 두 달 동안 캡스터빌에 머문다! 하하하!... 뭐, 네 쓸데없는 수색에 행운을 빌어주지. 만약 이 빌어먹을 비단에 마커스가 부르는 값을 내겠다는 멍청이를 찾으면, 내가 어디 있는지 알잖아.";
			link.l1 = "잠깐! 이 비단 한 필만 줘. 물건을 잠재 구매자들에게 보여줘야 해.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "물론이지, 문제없어. 너는 그걸 너희 보트에 실어가면 돼... 이봐, 얘들아! 비단 한 꾸러미를 선장 배에 실어 줘라!\n";
			link.l1 = "좋아. 그럼, 내가 구매자를 찾으면 다시 보자!";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "또 뭐 있어, 이 친구?";
			link.l1 = "지금은 아무것도 없어...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "잘 지내냐, 이 친구?";
			link.l1 = "잘 되고 있어. 우리에게 물건을 사줄 사람을 찾았어. 한 통에 5두블론이야. 타이렉스도 좋아할 거라고 믿어.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "말도 안 돼! 너 정말 악마 같은 놈이구나! 그걸 어떻게 해낸 거야, 응?";
			link.l1 = "긴 얘기야, Geffrey. 이제 잘 들어. 자네는 자메이카의 케이프 네그릴에 10일에서 15일 사이에 도착해야 해. 밤에 거기서 자네를 기다릴 거야. 암호는 '리옹의 상인'이야. 알겠나? 다시 말해 봐.";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "리옹에서 온 상인이라. 알겠어. 우리 경리에게 적어두라고 해야겠군; 여기서 글 쓸 줄 아는 사람은 걔밖에 없으니까. 하하!";
			link.l1 = "화물창에 두루마리 백 개 있나?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "더 있어.";
			link.l1 = "훌륭하군. 이제 출항할 시간이야. 나를 실망시키지 마!";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "진정해, 친구야, 모든 일은 제대로 처리될 거야.";
			link.l1 = "행운을 빌어, Geoffrey. 어쩌면 다시 만날 수 있겠지.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "호호호! 교활한 찰리 프린스, 직접 보니 반갑군! 다시 만나서 좋다, 친구!";
			link.l1 = "대머리 제프리! 찰리 프린스라고 했지? 하!";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "네 성은 처음 듣는데? 지금 라 베가에서는 다들 그렇게 부른다더라.";
			link.l1 = "찰리가 어디서 왔는지는 알겠는데, 왜 프린스지?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "그래, 너는 라 베가에서 유일한 고상한 개자식이구나! 하하하! 어떻게 지내? 파스콸레 가게엔 가봤어? 그 늙은 악당한테서 보급품 샀냐?";
			link.l1 = "다시는 안 돼!";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "크-하! 왜, 그 녀석이 마음에 안 들었나? 럼 값에 소금에 절인 소고기를 팔았어?";
			link.l1 = "더 최악이야! 그놈한테서 흑단을 가득 실은 네덜란드 상단에 대한 정보를 얻었지. 그걸 찾아내서 상선을 습격하고, 그 빌어먹을 목재를 수십 마리 쥐새끼들한테서 지키는 게 얼마나 힘들었는지 알아? 그런데 어쩌겠냐, 그 개자식이 흑단 한 조각에 150페소를 줬다니까. 흑단 한 조각에, 이 망할 놈의 흑단 말이야, Geffrey!";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "이런 일은 항상 일어나, 친구야, 장담하지. 라부아지에는 너 같은 괜찮은 녀석들을 이미 열두 명이나 속였어. 그 인간이 너한테 뭔가라도 줬다니, 그건 걔한테선 드문 일이야. 우린 아무리 배고파도 그 자식 '정보'는 안 받아.";
			link.l1 = "고마워, 친구야. 이제야 내가 첫 번째이자 유일한 바보가 아니었다는 걸 알겠군! 하지만 이번엔 그 자식이 스스로 덫에 걸렸어. 내가 반드시 그놈이 나를 본 날을 후회하게 만들어주지.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "이봐-이봐-이봐! 잠깐, 왕자님, 진정 좀 하시지. 여기서 그 장사꾼은 건드릴 수 없는 인물이야. 그놈을 털 생각이면 마르쿠스가 널 쫓아올 거다. 말해 봐, 타이렉스가 너를 라부아지에에게 보냈나?";
			link.l1 = "흠. 그래... 왜?";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "이봐... (목소리를 낮추며) 사안데, 사팔뜨기는 마르쿠스랑 나눈다고들 해. 이제 이해하겠어? 그래서 어느 해적도 라부아지에의 배를 감히 공격하지 않는 거야, 안 그러면 끝장이거든.";
			link.l1 = "알겠네. 경고해 줘서 고맙네, Geffrey. 잘 가고 신의 가호가 있기를!";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "너도 마찬가지야, 친구.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
			pchar.questTemp.CharleePrince = true; // атрибут для найма команды 
		break;
		
		case "Jeffry_22":
            dialog.text = "호호호, 왕자님! 누가 불꽃놀이를 벌였나 했더니 당신이었군! 혹시 스페인 놈들일까 봐 머스킷총 부대도 데려왔지.";
			link.l1 = "제프리? 너도 여기 있었어? 그런데 어떻게? 너도 보물 지도를 샀던 거야?";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "이봐, 난 그런 쓰레기에 돈 낭비 안 해. 어떤 여행자가 이 던전으로 안전하게 가는 길을 쓴 일기를 나한테 가져다줬거든.";
			link.l1 = "누가 그걸 가져다줬지?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "어떤 마약쟁이더군. 술 한 잔 마시려고 백 페소만 필요하다고 했지.";
			link.l1 = "토르투가에서 일어난 일이야?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "아니. 바베이도스였나? 프린스, 왜 그렇게 걱정하는 거야? 우리 인원이 많을수록 보물을 더 빨리 옮길 수 있을 텐데!\n";
			link.l1 = "이거 마음에 안 들어. 이런 우연은 믿지 않아. 이 일기를 쓴 사람이 혹시 카밀라의 아버지일 수도 있겠지?";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "카밀라가 누구야?";
			link.l1 = "이곳 지도를 이백 페소에 팔아먹은 그 계집이야!";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "헤헤... 왕자님, 너무 생각이 많으시군. 보물 사냥하러 가자. 어서!";
			link.l1 = "필요 없어. 이미 찾았어... 그놈들은 아래 감옥, 쇠창살 뒤에 있어. 우리가 직접 구출해야 해. 이봐, Geffrey, 한 가지 더 있어! 펠리 더 커틀라스도 여기 있었어!";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "커틀라스? 그럼 오늘은 우리한테 운 좋은 날이네! 그런데 지금 그 녀석은 어디 있지?";
			link.l1 = "아래에... 죽었어. 보물을 근처에서 그를 만났지. 그는 미쳐버렸고, 탐욕에 사로잡혀 소리를 질렀어. 그러더니 자기 일행들과 함께 나를 공격했지.";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "흠... 펠리는 항상 돈 때문에 운이 없었지. 저 금덩어리를 보고 미쳐버렸을 거야.";
			link.l1 = "그럴 수도 있지... 하지만 Geffrey, 넌 아직도 모르겠어! 우리 셋 다 여기까지 왔잖아! 그리고 우리 모두 같은 단서를 받았어! 그게 우연이라고 생각해? 누군가 분명히 우리 모두를 한곳에 모으려는 거야, 그리고 이곳은 정말 무덤 같은 느낌이 들어.";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "그런데 금은 봤어?";
			link.l1 = "내 두 눈으로 똑똑히 봤어. 거대한 상자 여러 개가 동전이랑 금괴로 가득 차 있었지.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "그렇다면 왜 걱정하시오, 왕자 나리? 앞장서시오, 자네가 말한 금괴들을 한번 보자고. 그 다음에 금을 나누면 되겠군.";
			link.l1 = "아, 네 말이 맞을지도 모르지, 뭐... 가자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            //PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "정말 장관이군! 금이 산더미처럼 쌓여 있잖아! 이제야 왜 커틀라스가 미쳐버렸는지 알겠어. 우리는 정말 운이 좋아, 프린스! 어떻게 생각해, 여기서 금을 얼마나 찾을 수 있을까?";
			link.l1 = "많이 있지. 이 금괴들 처리하고 나면 확실히 알게 될 거야.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "그래, 격자가 아주 튼튼해서 맨손이나 칼로는 못 부술 거야. 네 말이 맞아, 친구 – 도구를 찾거나 화약이 많이 필요하겠어. 이봐, 저기 봐! 저게 뭐지!?";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"정말 젠장, 이런 꼴이라니!";
			link.l1 = "이 빌어먹을 뱀 같은 놈!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "이런, 올해 '플라이 피쉬'에서 이런 일이 벌어졌다면 상어 밥이나 됐겠지... 얘들아, 손님이 오셨다! 인생에 뭐가 그렇게 잘못됐길래, 이 낡은 배에 일부러 찾아온 거냐, 친구?";
			link.l1 = "안녕! 네가 바로 허스키 빌리라고들 부르는 그 녀석 맞지?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "내 목소리만 들어도 모르겠어, 선장? 예전엔 영국이든 스페인이든 상인 놈들 바지에 오줌 지리게 만들었지. 그때가 정말 영광스러웠다니까!... 이제 늙은 빌리는 자기가 아끼는 섬 근처에서, 소중한 장주선에 앉아 인생의 끝을 기다리고 있지...";
			link.l1 = "빌리, 너한테 사업 제안이 있어. 자메이카 주변에서 무슨 일이 벌어지는지 네가 다 안다고 들었는데, 맞아?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "그렇게 들었다면 그런 거겠지, 안 그래? 게의 알을 잡아당기지 말고, 말해. 나한테 무슨 볼일이야?";
			link.l1 = "좋아. 포트 로얄에 조선공이 한 명 있지. 그자는 손님들에게 특별한 서비스를 제공하는데, 그 서비스와 제작에 필요한 선박용 비단이 필요하다고 하더군. 그런데 이 물품을 거래하는 건 여기서 불법이라, 결국 불법 공급자를 따로 구했다고 하네. 누가 그에게 선박용 비단을 공급하는지, 또 어떻게 공급하는지 알아내고 싶네.";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "호호호, 이것 좀 봐라! 도일리 대령 밑에서 일하는 거냐, 아들?";
			link.l1 = "또 시작이군! 아니, 나는 마커스 타이렉스랑 일해. 그는 배 실크 시장에서 몫을 원하고, 이 조선공은 '낯선' 사람들하고 거래하는 게 무서워서 벌벌 떨고 있어...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "오, 그러니까 네가 규약 관리인을 위해 일하고 있다는 거군! 그거 참 좋은 소식이지... 물론 거짓말이 아니라면 말이야. 나는 조선공 따위엔 관심 없어; 한 놈 잡아가면 또 다른 놈이 그 자릴 차지하지. 하지만 내 애마는 다르지. '플라잉 피쉬'가 지금 상태가 말이 아니야. 내 말 알아듣겠나?\n새로 만든 롱보트 하나랑, 네가 말한 그 배 실크 한 통을 가져와. 빌리가 그걸로 제대로 된 돛을 만들어서 순찰대 따위는 가볍게 따돌릴 거야, 하하하! 그 대가로 빌리가 조선공과 그 실크 공급자에 대해 전부 알려줄 테니. 믿어라, 아들아, 네가 알고 싶은 건 내가 다 알고 있지. 다만 네가 진짜 해적이지, 영국놈들 비위나 맞추는 놈이 아닌지만 확인하면 돼!";
			link.l1 = "새로운 장선이 필요하다고? 내가 네가 직접 살 수 있을 만큼 돈을 줄까? 거기에 조금 더 얹어주지.";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "헤헤, 선장, 늙은 빌리는 이 도시에 환영받지 못해. 포트 로얄에서 나를 너무 잘 기억하고 있어서, 옛 친구들 사이에서 그 바위에 목 매달리는 꼴은 보고 싶지 않거든. 그러니, 아들아, 새로 만든 롱보트를 가져오길 기다릴게. 네그릴 곶에서 사흘 동안 기다리겠다. 그리고 비단도 잊지 마!";
			link.l1 = "좋아, Billy. 네가 원하는 작은 배랑 돛천 한 통을 주마. 곧 돌아오겠다.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = " 알겠소, 선장. 빌리가 해변에서 기다리고 있을 거요. 곧 다시 보지!";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "뭐라고? 벌써 나한테 단정(롱보트)을 가져왔단 말이냐?";
			link.l1 = "너 장난꾸러기구나, 이봐, Billy?";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "그래서, 선장님, 내 새로 산 롱보트는 어떻게 됐소?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "끝났어, 허스키. 그녀는 선창에 배 실크 한 두루마리와 함께 넘겨졌어. 이제 네 낡은 배는 마음대로 침몰시켜도 돼.";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = "아직 하고 있어. 기다려.";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "젠장! 이건 빌리가 5년 만에 들은 최고의 소식이야! 헤헷, 이 병 따기 딱 좋은 이유군...";
			link.l1 = "난 됐어. 그래서, 비단 공급업자는?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "아쉽군, 내 새 '플라잉 피쉬'를 축하하며 한잔할 수도 있었는데! 뭐, 괜찮아... 이봐, 아들아\n영국 국기를 단 브리건틴이 매달 중순, 대략 10일부터 15일 사이에 포틀랜드 코브에 도착한다. 만약 그 배가 진짜 영국 배라면 내가 죽기 전엔 럼주 한 방울도 입에 대지 않겠다! 그 배 이름은 '위트레흐트'고, 남서쪽, 큐라소가 있는 곳에서 온다. 분명히 네덜란드 배 선장이야, 보면 알지\n항상 같은 무리들이 해안에서 그 배를 맞이하는데, 교활한 조선공의 우두머리가 이끄는 놈들이지. 그자가 바로 네덜란드인들이 거기서 내리는 선박용 비단을 받아가는 놈이야. 그게 선박용 비단인 건 확실해, 네덜란드 놈들만 그렇게 싸거든.";
			link.l1 = "매달이라고 했나?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "그래, 이 녀석아, 지난 1년 동안 한 달도 빠뜨린 적 없지. 그 음침하고 수염난 녀석들과 얘기하고 싶으면, 매달 10일부터 15일까지 밤에 포틀랜드 코브에서 기다려 보라고. 내 롱보트에 새로 단 비단 돛을 걸고 맹세한다!";
			link.l1 = "헤! 내 돈이 아깝지 않았군. 잘 가라, Billy. 순찰대한테 걸리지 말고 네 늙은 엉덩이 잘 챙기라고. 안 그러면 내가 정말 화낼 거다.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "하, 늙은 빌리가 자메이카 해안에서 진짜 재미 좀 벌일 참이야!\n행운을 빌어, 선장님! 사냥 잘 하시오!";
			link.l1 = "너도 그래, Billy!";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "Joachim";
				sld.lastname = "Gusen";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // правки прогона 3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// мастеровой с верфи Порт-Ройаля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "이봐, 뱃사람, 자메이카에 막 도착했나?";
			link.l1 = "흠. 맞아. 무슨 일이야?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "근처 바다에서 무슨 일 본 적 있어?";
			link.l1 = "그래, 봤지. 어떤 브리건틴이 영국 순찰 코르벳과 싸우고 있었어. 영국 놈들이 세게 한 방 먹였고, 네덜란드 놈들은 도망치려고 화물을 바다에 내던졌지.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "왜 그녀가 네덜란드인이라고 그렇게 확신하지? 제정신인 네덜란드 놈이라면 포트 로열 근처에 얼씬도 안 할 텐데...";
			link.l1 = "영국 깃발을 달고 있었지만, 이름이... '위트레흐트'였지. 별로 영국답지 않잖아? 내가 말하지만, 그들은 네덜란드인이었어, 어쩌면 밀수꾼일지도 몰라. 순찰대도 분명히 그들을 예상했을 거야.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "젠장!";
			link.l1 = "이거 별로 마음에 들지 않는 것 같군...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "여기서 이 브리건틴을 기다리고 있었나?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "내가 왜 그래야 하지?";
			link.l1 = "가자. 네가 누군지 알아. 너는 포트 로얄 조선소의 감독이고, 브리건틴이 아주 특별한 화물을 가져오길 기다리고 있지.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "네 얼굴에 다 써 있잖아, 바로 거기!";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "아르! 얘들아, 이놈들 위장한 순찰대다! 다 끝장내고 여기서 당장 빠져나가자!";
			link.l1 = "젠장! 잠깐, 너 혹시...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "무례하게 구는 거냐, '바다의 늑대'? 입 조심하지 않으면...";
			link.l1 = "가자. 너, 기분 안 좋아 보이잖아. 설마 진짜로 이 네덜란드 놈들이 오길 기다리고 있었던 거야?";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "아니면 뭐? 인생이 뭔지 가르쳐 주겠다는 거야?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "내가 그랬으면 어쩔 건데? 왜 신경 쓰지?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "난 정말 아니야. 여기서 기다리는 건 너지, 내가 아니야. 너에겐 영원이 남아 있잖아.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "오, 내가 신경 쓸 이유는 충분하지. 나는 브리건틴의 화물창에 뭐가 있었는지 알아. 배의 비단 말이야. 너도 그 비단 때문에 여기 온 거지?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "흠... 영원인가?";
			link.l1 = "바다 밑바닥에서 돌아오는 데는 영겁의 시간이 걸리지. 네 브리건틴은 순찰 코르벳에게 침몰당했어, 친구. 순식간이었지. 그래도 전쟁이란 게 얻는 것도 있고 잃는 것도 있는 법이야. 그 침몰한 네덜란드 배 덕분에 나는 짭짤하게 한몫 챙기겠군.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "도대체 어떻게, 궁금하군?";
			link.l1 = "놈들이 도망치려다 바다에 던진 것들을 내가 팔 거야. 거의 다 잃었지만, 귀한 선박용 비단만은 마치... 코르크처럼 떠 있었지. 대부분 건져 올렸으니, 내일 도시로 가서 사는 사람을 찾아볼 생각이야. 어디서 이득을 보고 어디서 손해를 볼지는 아무도 모르는 법이지.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "기다려!";
			link.l1 = "카람바! 이제 어쩌지?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "비단을 얼마나 모았나?";
			link.l1 = "그게 너랑 무슨 상관이야? 이건 내 비단이야! 아니면 네가 총독의 개라도 되냐? 너는 죽었...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "칼 집어넣어, 선원. 난 개도 아니고 고자질쟁이도 아니야. 우린 이 근처 조선소에서 일하지... 이 비단은 원래 우리 몫이었고, 내가 알기로 지금 네가 갖고 있지. 내가 전부 사겠다, 우리한텐 이 비단이 필요해, 친구.";
			link.l1 = "정말이야? 흥미로운데... 얼마지?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "두 롤에 이천오백. 괜찮은 값이지, 이보다 나은 가격은 못 구할 거야.";
			link.l1 = "운이 좋은 것 같군! 나는 가지고 있어 "+FindRussianQtyString(i)+"돈을 보여 줘라. 그러면 지금 바로 육지로 가져가라고 명령하겠다.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "거래 성사!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "흠... 요아킴이 가져오기로 한 건 겨우 80통이었는데, 네가 이렇게 많이 챙길 리가 없지... 그 말은 네가 더러운 수작을 부리려는 거거나... 아니면 밀고자라는 거군! 이놈들아, 저 자식 죽이고 당장 꺼져라!\n";
			link.l1 = "젠장!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "훌륭한 거래야, 친구! 왜 그렇게 침울해? 바다 밑에 가라앉은 네덜란드 놈들 때문에 걱정돼? 이런 일도 있는 거지, 신경 쓰지 마!";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "그래, 맞아... 걔들이 우리 단골 공급처였지. 이제 비단을 어디서 구하란 말이야? 항상 부족한데다, 무역 전체가 도일리 대령의 직접 관리 아래 있잖아. 에이, 젠장...";
			link.l1 = "흠... 이봐, 친구, 그 일은 내가 도와줄 수 있을 것 같군.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "정말이야? 그런데 우리를 어떻게 도울 생각인데? 매달 백 개씩 배달이라도 해 주겠다는 거야?";
			link.l1 = "나? 흠, 아마 나는 아닐 거야. 하지만 마커스 타이렉스라면 알겠지. 그 사람 들어본 적 있어?";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "크-하! 그래서 네가 해적이란 말이지?";
			link.l1 = "아니, 나는 특별한 경우에만 그들과 거래하지. 확실히 말하건대, 마르쿠스는 정기적으로 선박용 비단을 들여와서 살 수 있는 누구에게나 팔고 있어. 그리고 여기서 말하는 건 한 필에 2,500페소 따위가 아니야. 내 생각엔 한 필당 금 5두블룬을 낼 수 있다면, 마르쿠스가 비단을 산더미처럼 쏟아줄 거야. 그건 믿어도 돼.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "흥미로운 소식이군... 마커스 타이렉스라고? 두블룬으로만 받는다고?..";
			link.l1 = "야, 친구, 비단을 누구한테서 사든 그게 그렇게 중요해? 돈은 다 똑같지, 은행에서 페소를 두블룬으로 언제든 바꿀 수 있고. 그래서 어쩌라고, 암호 담당자 귀에 네 얘기 좀 슬쩍 해줄까? 어차피 나 라 베가에 갈 거거든.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "좋아. 거래하자. 조건은 이렇다: 매달 10일부터 15일 사이에 롤빵 100개씩 한 번에 가져와라. 우리는 여기서 기다릴 거다... 잠깐, 만나는 장소를 바꾸자. 이제 이곳은 위험해졌으니. 마룬 타운 근처 네그릴 곶에서 기다리겠다, 거기가 더 안전할 거다. 암호는 '리옹의 상인'이다.";
			link.l1 = "거래 성사됐군, 친구. 정말 지옥 같은 항해였지! 이런 손님이면 타이렉스가 나한테 두블룬 한두 개쯤은 주겠는걸! 하하! 좋아, 이만 가봐야겠다. 다음 달에 타이렉스 배를 기다려. 자네와 가족에게 행운이 있길 바라!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "우리가 예의부터 가르쳐 주면 인생 수업 따윈 필요 없을 거다.";
			link.l1 = "잘난 척하냐, 목수? 좋아, 네 브리건틴 기다려봐라. 좀 오래 걸릴 거다.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "이봐, 선생, 나도 너한테 가르칠 게 좀 있어!";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "목수라고? 젠장, 어떻게 알았지? 크-하! 망할, 얘들아, 이놈은 위장한 순찰대야! 저놈 죽이고 얼른 튀자!";
			link.l1 = "젠장!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "우릴 내버려 둬라, 이 비린내 나는 놈아, 너한테 쓸 시간 없어. 꺼져!";
			link.l1 = "네덜란드 배를 기다리느라 바쁜가? 행운을 빌지. 영원히 기다리게 될 테니.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "무슨 헛소리를 하는 거야?";
			link.l1 = "알겠어. 하지만 혹시 네가 맞더라도, 잊어버려. 그녀는 오지 않아, 순찰 코르벳 때문에. 망원경으로 싸움이 끝나는 걸 봤거든. 너무 빨리 일어났고, 여기서 멀지 않은 곳이었어\n";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "다시 말하지만, 우리는 아무것도, 아무도 기다리지 않아, 그리고...";
			link.l1 = "봐, 난 정말 신경 안 써. 나는 도시 순찰대 소속도 아니고 네가 뭘 하든 관심 없어, 나도 착한 사람은 아니거든. 밀수하는 거라면 그건 네 일이지. 내가 하고 싶었던 건 그냥 경고해 주는 거였어. 행운을 빌어, 친구.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "잠깐만... 'Utrecht'호가 정말 침몰했다는 게 확실해?";
			link.l1 = "틀림없지. 그녀는 도망치려 했고, 화물칸에 있던 모든 걸 내던졌어. 귀한 선박용 비단조차 아끼지 않았지. 하지만 그런 극단적인 조치로도 코르벳함의 속도 우위에는 당해낼 수 없었어.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "정말 안타깝군... 그런데 비단 없이 우리가 뭘 해야 하지? 젠장!";
			link.l1 = "배 실크가 필요하신가?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "왜 묻는 거지, 팔 생각이라도 있는 거야?";
			link.l1 = "나는 아니지만, 그런 사람을 알고 있지. 그 양반은 통이 크고 꾸준한 손님을 찾고 있어. 네가 그 조건에 맞을 것 같나?";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "그리고 저 남자는 누구지?";
			link.l1 = "마커스 타이렉스, 라 베가의 남작이자 코드 키퍼로 더 잘 알려진 인물이지. 그는 정기적으로 배에서 실크를 들여오니 항상 팔 물건이 남아 있어. 네가 값을 충분히 높게 부른다면, 너한테도 팔 생각을 할 거야.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "그래서, 네가 해적이란 말이지?";
			link.l1 = "왜 신경 쓰지? 배짱 있으면 너랑 타이렉스 사이에 거래를 성사시켜 줄 수 있어. 자신 없으면... 그만 가라.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "알았어, 알았어, 화내지 마. 그래, 맞아. 나 타이렉스랑 거래하고 싶어. 그런데 너한테는 뭐가 남지?";
			link.l1 = "화물에 좋은 값을 제시하면, 내가 도와준 대가로 마르쿠스에게서도 꽤 괜찮은 돈을 받을 수 있을 거야. 그래서, 어떻게 할 건가?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "한 번에 5두블론이오. 이보다 더 좋은 가격은 없으니, 내 말을 믿으시오.";
			link.l1 = "금화 5개? 흠. 나쁘지 않군. 이런 손님을 데려왔으니 타이렉스가 나한테 크게 빚지겠어. 좋아, 거래지. 그에게 알려주마. 하지만 가격에 대해 나한테 거짓말한 거라면, 네 목이 위험할 줄 알아라.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "걱정 마, 우리는 정직한 사람들이야. 조건은 이거야: 매달 10일부터 15일 사이에 롤빵 백 개씩 가져와. 우리는 여기서 기다릴 거야... 잠깐, 만나는 장소를 바꾸자, 이곳은 이제 위험해졌어. 마룬 타운 근처 네그릴 곶에서 기다릴게, 거기가 더 안전할 거야. 암호는 '리옹의 상인'이야.";
			link.l1 = "알겠소. 첫 번째 물량은 다음 달에 받을 것이오.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "이번에는 Tyrex에게 더 많은 화물을 가져와도 된다고 전해 줘. 이번 달에는 비단이 다 떨어졌거든.";
			link.l1 = "그러지. 행운을 빌어, 친구야.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "이봐! 내 배에 무슨 일로 올라온 거냐, 친구?";
			link.l1 = "이봐, 커틀라스. 마커스 타이렉스가 날 보냈어. 마라카이보로 행군이 우리를 기다리고 있어.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "아-아, 드디어군. 이번 항해에서 내가 모실 새 상관이 바로 당신이겠지. 좋아. 내 새로운 제독 이름이 뭐지?";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "명령을 내리시지요, 제독 나리 "+GetFullName(pchar)+"?";
			link.l1 = "우리는 마라카이보 호수로 따로 항해할 거다.\n너는 밤에 도착해서 과히라 만에 몰래 상륙해야 해. 거기서 나를 기다리면서 그동안 작은 야영지를 마련해 둬라. 나는 스페인 항구에 상륙할 생각이다.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "알겠소, 제독님!";
			link.l1 = "거기까지 가는 데 얼마나 걸릴 거요?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "흠... 대략 일주일쯤 걸릴 거야. 하루 빠르거나 늦을 수도 있는데, 다 바람에 달렸지.";
			link.l1 = "좋아. 그럼 시간 낭비하지 말자. 과히라 만에서 보자, 친구.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "알겠소, 제독님!";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "명령을 내리시겠습니까, 제독님?";
			link.l1 = "지금은 아무것도 없어. 우리 작전 때문에 바쁘거든.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "해변에 큰 상자를 준비해라. 그 안에 우리 갇힌 동료들을 위해 무기를 모을 것이다.";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "그래서, 핸섬은 무슨 일인데? 내 손이 돈 놈 피 좀 흘리고 싶어서 근질근질하거든!";
				link.l1 = "생각했던 것보다 더 복잡해. 그는 플랜테이션 경비병들이 너무 경계하고 있다고 했어. 무기를 들여보낼 유일한 방법은 물품 사이에 숨기는 거야. 커피나 코프라, 바닐라 중 하나를 급하게 구해와야 해. 그 지역 농장주는 그것들만 취급하거든.";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "야영지를 떠나 돌격대를 모아라. 이제 행군할 시간이니, 어둠을 틈타 공격한다.";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "듣고 계시오, 제독 나리, 내가 생각을 좀 해봤는데...";
			link.l1 = "이게 뭐야, 테락스가 네 칼이나 휘두르지 말고 머리 쓰라고 돈 주는 거냐, 커틀라스?";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "이봐! 플랜테이션에서 반란이 일어난 거 맞지, 제독? 불길이 치솟고 있어! 이번엔 금을 좀 챙길 수 있겠군!..";
			link.l1 = "해변에 상자가 필요해, 커틀라스.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "즉시 하겠습니다, 제독님!";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "즉시 하겠습니다, 제독님!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "사람들은 준비 완료됐습니다, 제독님!";
			link.l1 = "전진하라!";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "제독님, 우리가 구하려던 타이렉스의 친구가... 이미 죽은 것 같습니다.";
			link.l1 = "그래, 하지만 거기서는 아무것도 할 수 없었어. 경비병들 봤잖아; 우리가 살아남은 것만도 다행이지.";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "제독 나리, 마르쿠스가 당신에게 화낼 거예요. 지금은 그에게 가지 마십시오. 저는 이만 가겠습니다. 당신도 가는 게 좋겠어요.";
			link.l1 = "그래...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "나쁜 소식입니다, 제독 나리. 동쪽에서 스페인 함대가 우리를 향해 오고 있습니다. 도망칠 시간이 없습니다.";
			link.l1 = "몇 명이나 되지?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "배 세 척. 대포도 잔뜩. 우리 완전히 끝장났어."; // лесникПОСЛЕДНЕЕ
			link.l1 = "두고 보자.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "장, 너는 커틀라스의 배로 가.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "커틀러스, 스페인 깃발을 올리고 당장 여기서 빠져나가. 내가 놈들을 따돌려 줄게. 라 베가에서 모두 다시 보자.";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "하지만...";
			link.l1 = "변명하지 마! 커틀러스, 피카드가 타이렉스의 집에 못 가면 네 목이 날아가는 거야. 모두 승선해!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "명령을 내리시겠습니까, 제독님?";
			link.l1 = "전투 준비해라. 내가 명령하면 공격해!";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "예, 제독님... 명령만 내리십시오!";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "호호! 안녕하시오, 왕자 나리. 무슨 일로 토르투가에 오셨소?";
			link.l1 = "마커스의 일 또야. 이봐, 커틀러스, 왜 이 집에 사는 그 개자식이 나를 들여보내지 않는 거지?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "가스파르 골든티스? 그 자는 믿을 만한 놈들이랑만 일하지. 다른 놈들은 추천장이 있어야 같이 일할 수 있어. 반짝이는 장신구라도 팔고 싶어? 원하면 내가 보증해 줄 수도 있는데...";
			link.l1 = "그래서 그 자가 고리대금업자란 말이오? 이자가 얼마냐?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "형제여, 뭔가 빠뜨렸군. 가스파르는 고리대금업자가 아니야, 너는 가야 해 "+GetFullName(characterFromId("Tortuga_usurer"))+" 필요하면 말이야. 골든티스는 온갖 종류의 보석과 장신구를 사들여. 참고로, 돈도 후하게 주고 쓸데없는 질문도 안 해. 모든 해적 선장들이 그의 단골이지.";
			link.l1 = "그렇군... 어떤 이들은 심지어 자기 돈까지 그에게 맡긴다고 들었지...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "하하! 그런 소리 한 놈은 거짓말쟁이야, 가서 그 뻔뻔한 놈 눈에 침이나 뱉어 줘. 가스파르는 보석만 다루는 사람이야, 예전부터 그랬지. 남의 돈 때문에 골치 아플 이유가 뭐가 있겠어?";
			link.l1 = "알겠어. 고마워, 커틀라스, 바다에서 보자!";
			link.l1.go = "Pelly_27";
			link.l2 = "흠, 그렇군. 그래서 그자가 잡동사니를 산다고? 흥미롭네... 나를 위해 좋은 말 좀 해줄 수 있다고 했나?";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "또 보자, 왕자.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "물론이지! 이제 너도 우리 중 한 명이야, 헤헤! 여기서 잠깐 기다려.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "모든 게 정리됐어! 이제 골든투스는 찰리 프린스가 잡동사니를 팔러 올 수도 있다는 걸 알게 됐지. 가격도 괜찮긴 한데, 그 구두쇠 고리대금업자들보단 여전히 좀 낮아. 하지만 얘는 뭐든 톤 단위로 사들여! 그리고 내가 이미 말했듯이 쓸데없는 질문도 안 해.";
			link.l1 = "이게 바로 내 잘생긴 녀석이지! 잘했어, 폴! 이제 전리품을 다 풀어놓을 곳이 생겼군!";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "아니, 장 피카르는 '미남'이고, 나는 '커틀라스'야, 하하! 잘 가라, 프린스!";
			link.l1 = "고마워, 커틀라스, 바다에서 행운을 빌어!";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "새 세 마리를 데려왔소, 왕자 나리. 옷장 안이랑 침대 밑에 숨어 있더군. 예쁜 것들이지, 안 그래? 하하하!";
			link.l1 = "내가 보기에 정말 그렇네. 게다가 녀석들 손질도 잘 되어 있어. 돈 스터번이 녀석들을 아주 아끼는 모양이야.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "만세! 여기서 대체 뭐 하는 거야, 왕자?";
			link.l1 = "커틀라스?.. 나는 소리와 소란을 따라왔는데, 설마 네가 있을 줄은 몰랐지. 도대체 어떻게 여기까지 오게 된 거야?";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "아니, 너 왜 여기 있는 거야! 넌 항상 나타나잖아! 이 보물 때문에 Tyrex가 널 보낸 거지, 맞지? 이런, 또 늦었네...";
			link.l1 = "타이렉스? 아니... 어떤 계집애한테서 지도를 샀지. 아마 너한테도 똑같은 걸 팔았겠지, 안 그래? 토르투가에서? 정말 교활한 년이야. 그래도 거짓말은 안 했어 - 이 금더미 좀 봐! 이걸 다 옮기려고 사람들 더 데려올 거야...";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "그래, 금덩이 맞아! 하지만 그건 너나 타이렉스 것도 아니야! 내가 먼저 찾았어! 내 거라고! 내가 어떻게 알게 됐는지는 중요하지 않아! 네가 알 바 아니야!";
			link.l1 = "진정해, 커틀라스. 왜 그렇게 화가 난 거야? 이 더미 좀 봐 - 여기 최소 백만은 있겠는데. 어쩌면 더 많을지도 몰라! 우리 둘 다 충분히 챙길 수 있겠어!";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "항상 네가 더 좋은 몫을 챙겼지, 프린스! 하지만 이번엔 아니야! 보물은 내 거야! 내가 먼저 찾았으니까!";
			link.l1 = "젠장, 폴, 너 왜 이래? 여기서 우리 거래 못 하겠어? 이 금의 절반만 해도 엄청난 돈이야. 네가 이런 돈 만져본 적 없잖아. 게다가 언젠가 내가 좋은 정보 하나 잡으면 너한테 알려줄 수도 있잖아.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "나랑 한판 붙고 싶어, 나리? 절대 안 돼! 한 푼도, 기니 한 닢도 안 줄 거야! 이미 늦었어!\n아, 네 수작 다 보여! 이 금은 절대 못 가져가!!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "정말 웃기네. 진짜로. 너 유머 감각 있구나, 제독. 하지만 사실이야 – 마커스는 너처럼 자기보다 한 수 위라고 생각하는 놈들을 싫어하지. 하지만 영리한 사람은 높이 평가해.";
			link.l1 = "알겠어, 알겠어. 그래서, 무슨 생각 중이야?";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "너랑 핸섬이 분명히 생각하지 못한 게 있지. 너희는 플랜테이션에서 반란을 일으키려고 하잖아. 약탈이나 혼란이 목적이라면 좋은 생각이지. 하지만...";
			link.l1 = "근데 뭐? 반란에 반대하는 거야? 겁났어?";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "나라고? 하! 절대 아니지. 하지만 잘 생각해 봐. 만약 도살 중에 핸섬이 죽기라도 하면 어떻게 될까? 마커스한테 뭐라고 말할 건데? 내가 장담하는데, 우리가 무슨 말을 하든 소용없어. 어차피 우리 가죽은 벗겨질 거야.";
			link.l1 = "흠. 그래서 네 그 대단한 계획이 뭔데? 어떻게든 그를 빼내야 해.";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "우리가 그렇지. 그래서 말인데... 그냥 그를 사버리는 건 어때? 공식적으로 말이야. 금화 몇 닢이면 이 놈들한테선 누구든 살 수 있어 - 자기 어미까지도 팔 놈들이니까. 불쌍한 장은 말해 뭐 하겠어?\n";
			link.l1 = "하! 커틀러스, 네 말대로라면 내가 플랜테이션에 그냥 들어가서 피카르드를 사겠다고 하라는 거냐? 그냥 재미삼아 내가 누구 밑에서 일하는지도 말해줄까? 제정신이냐?";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "그럴 필요 없어. 사실, 오히려 반대지 – 상인인 척해. 물론 네가 그 역할을 소화할 배짱은 없겠지만, 해적으로 보이지도 않아. 기분 나쁘게 듣지 마, 제독 나리, 사실이니까. 그냥 당당하게 그 플랜테이션에 들어가서, 자신감 있게 행동하고 장을 찾는다고 해. 주인이 네 정체를 의심할 수도 있지만, 겉으로는 내색하지 않을 거야. 내가 말했잖아 – 금화 몇 닢이면 입을 다물게 할 수 있다고.";
			link.l1 = "그래서 이... 황금 손이 우리에게 얼마쯤 들겠소? 산 전체 값인가?";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "그럴지도 모르지. 하지만 목숨을 잃는 것보단 금을 내놓는 게 낫지 않겠어. 네가 육지에 있는 동안 난 빈둥거리지 않았어 – 해적처럼 안 보이게 옷을 갈아입고, 플랜테이션과 그 보잘것없는 주인에 대해 수소문했지.";
			link.l1 = "그래서 뭘 찾았냐, 커틀라스?";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "시장 가격이라고 할까. 그 자가 귀중한 포로를 손에 넣은 게 이번이 처음이 아니지. 보통 그런 자들은 교수대에 매달리거나, 아니면 더 나쁘게는 종교재판소의 지하 감옥에 갇히게 되지.";
			link.l1 = "그래서 그 사람은 그걸 얼마에 파는 거야?";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "중요한 사람을 위해서라면? 오백 닢이오. 물론 두블룬으로.";
			link.l1 = "오백이라고?!";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "농장주들아, 뭘 기대했어?";
			link.l1 = "그 돈이면 작은 군대도 무장시키겠군! 도대체 내가 반란 일으키려고 내 배에 무기고를 쌓아두는 이유가 뭐지? 이 정도면 작은 전쟁 치르기에 충분하겠어.";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "무기는 어쨌든 나중에 네 선원들에게 쓸모가 있을 거야. 그러니, 어때?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "(믿을 만한 놈) 테락스가 주는 보상이 여기서 우리가 쓰는 돈보다 적으면 웃기겠지. 하지만 네 말이 맞아 - 우리 목숨이 더 소중하지. 두블론은 내가 가지고 있어.";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "지금은 그런 금산 따위 없어.";
				link.l2.go = "Pelly_44_1";
				Notification_Perk(true, "Trustworthy");
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "있잖아, 커틀라스? 됐다, 그냥 잊어버려. 우리 해적 맞지 않아? 그리고 장은? 잘생긴 얼굴밖에 내세울 게 없나? 상자 하나 준비해, 원래 계획대로 간다.";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "네가 그 돈을 마련했다면 놀랄 일이야 – 엄청난 액수거든. 좋아, 준비가 되거나 더 나은 방법이 생각나면 나를 찾아와.";
			link.l1 = "알겠어. 여기서 기다려.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "그래, 제독. 피카르를 구할 만큼 금을 모았나?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "그래, 드디어 해냈어. 이게 통하길 바라자.";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "아직 작업 중이야, 커틀라스.";
			link.l2.go = "exit";
			link.l3 = "나는 내 피땀 흘려 번 돈을 저 탐욕스러운 플랜터 놈들에게 주지 않을 거야! 상자를 준비해. 우리는 해적 신사처럼 행동할 거다. 그게 내 결정이야.";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "이봐. 우리 선원에 막 들어왔으면서 벌써 그런 돈을 막 쓰는 거야!";
			link.l1 = "돈이 전부는 아니지. 하지만 테락스의 영광을 누리는 건? 그건 값으로 따질 수 없어.";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "그 말엔 반박할 수 없지. 하지만 네가 말했듯이, 돈만의 문제는 아니야. 다른 중요한 게 있어, 제독.";
			link.l1 = "이제 궁금한데. 뭐?";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "내가 이 농장에 대해 샅샅이 조사했다고 말했잖아. 여기서 어떤 물건이 수요가 많고 시장에 유통되는지도 다 알아봤지.\n정식 상인인 척하고 싶으면, 그냥 금덩어리만 주인 책상에 내던지지 말고 그런 물건들부터 챙기는 게 좋을 거야.";
			link.l1 = "그럴 만하군. 무슨 물건을 말하는 거지?";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "글쎄, 살아 있는 물건들 말고도, 헤헤, 이 근처 플랜테이션 주인이 커피, 코프라, 바닐라를 사고팔고 또 되팔지. 그러니까...";
			link.l1 = "어디서든 빨리 그걸 좀 비축해야겠어. 아니면 대상 행렬을 털어서 내가 필요한 게 실려 있길 바라든가.";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "아무 상단이나 오는 게 아니야. 내 것도 아까워서 내놓기 싫지만, 내가 따로 챙겨둔 정보가 있지. 네가 딱 원하는 걸 실은 상단이 곧 도착할 거다. 하지만 조건이 있어...\n";
			link.l1 = "아, 또 뭐야?";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "프랑스 깃발 아래에 있소.";
			link.l1 = "뭐?!";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "네가 답답한 거 이해해, 하하. 결정은 네가 하는 거야... 제독. 자세한 내용을 듣고 싶나?";
			link.l1 = "젠장... 좋아, 말해 봐. 우리에겐 시간이 별로 없어 – 너나 내가 저놈들한테 덤비지 않으면, 다른 놈이 먼저 움직일 거야.";
			link.l1.go = "Pelly_52";
			// link.l2 = "나는 어쩔 수 없을 때 아니면 프랑스 놈들은 건드리지 않아. 더 이상 할 말 없어.";
			// link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "그럼 네가 직접 그 물건들을 빨리 모으는 게 좋을 거다, 프리티 보이가 다른 놈한테 팔리기 전에 말이지. 나도 여기서 영원히 기다릴 수는 없어.";
			link.l1 = "그럴 줄 알았지.";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_52":
            dialog.text = "그래, 이거지! 네 안에 그런 배짱이 있을 줄 알았어... 제독. 자, 본론으로 들어가자면, 내 믿을 만한 연락책이 최근에 보고하길, 약 2주 후쯤 과들루프 근해에 커피와 향신료를 실은 프랑스 호위선단이 나타난다고 하더군. 규모도 크고 무장도 잘 되어 있으니 철저히 준비해둬.";
			link.l1 = "내게 다른 선택지가 있나?";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "기운이 없어 보이시네요, 제독님. 핸섬은 어디 있습니까? 다 물거품이 된 겁니까?";
			link.l1 = "그래. 돈은 꽤 벌었지만, 그 고집불통 놈이 피카르를 나한테 안 팔더라고 - 금화 더미를 내밀어도 말이야!";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "뭐 이런 바보가 다 있나! 이제 어쩔 거야?";
			link.l1 = "나는 이미 플랜터와 짐을 내리기로 약속했어. 이제 원래 계획대로 가야 해 – 지금 아니면 영영 기회가 없어!";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "하지만 우리는 잘생이랑 다른 녀석들을 위해 아무것도 준비하지도 않았잖아!";
			link.l1 = "시간 없어! 배에 타라 - 무기랑 약품을 우리 창고에서 짐 자루에 몰래 넣자. 그리고 스페인 깃발 올리는 거 잊지 마!";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "좋은 생각이군.";
			link.l1 = "아무튼, 더 이상 시간 없어. 움직여! 곧 하역이 시작된다고.";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "이게 누구야! 잘생겼네! 얼굴에 상처 하나 없고 당당하게 걷는 걸 보니, 모든 일이 순조롭게 끝난 모양이지?";
			link.l1 = "순조롭다는 말로는 부족해 – 싸움도 피했고 장도 다시 사왔을 뿐 아니라 돈도 좀 벌었지. 네 계획은 완벽하게 통했어, 폴. 수평선 너머도 조용한가?";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "조용하기 그지없군. 마커스한테 다시 가는 거야?";
			link.l1 = "그래.";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_PlantSuccessfulRedemption");
		break;
		
		case "Pelly_62":
            dialog.text = "흠, 원하시는 대로 하십시오, 제독님. 하지만 핸섬에게 무슨 일이라도 생기면, 테락스에게 당신이 내 조언을 무시했다는 걸 꼭 알리겠소. 탈출 준비는 다 끝났나?";
			link.l1 = "내가 상자 안에 뭐가 있는지 다시 한번 확인하고 세어 볼게.";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "확실히 해두시오. 내 수고에 대한 소정의 보수만 주면 도와줄 수 있지, 헤헤.";
			link.l1 = "어때?";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "마라카이보에 총기 밀매상이 한 명 있어. 내가 변장하고 몰래 들어가서, 돈을 주고 무기를 여기로 밀반입하게 할 거야. 하지만 비용이 들어 – 정확히 금화 더블룬으로 말이지.";
			link.l1 = "그런데 왜 이 사람을 이제야 소개한 거지? 이 일로 내가 얼마나 손해를 봐야 하지?";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "내 정보원들 모두도 소개해 줘야 하나? 좋아. 비용, 위험, 내 몫까지 합치면... 잘생이 몸값이랑 비슷하게 들 거야.";
			link.l1 = "커틀러스, 신을 두려워해...";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "나는 신도, 너도 두렵지 않아, 제독. 하지만 우리가 장을 구하지 못하면 마르쿠스가 분노할 텐데? 그건 또 다른 문제지. 그래서 어쩔 거야? 상자 여는 데 도움이 필요해?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "좋아, 어서 가. 이미 충분히 시간을 낭비했으니까. 자, 이 정도면 맞을 거야.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "돈이 꽤 많군, Paul. 생각 좀 해봐야겠어.";
			link.l2.go = "Pelly_67";
			link.l3 = "그건 소량 무기 치고는 너무 비싸군! 도매로 훨씬 싸게 살 수 있거든! 됐어, 내가 직접 처리하지.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "그래, 실컷 생각해 봐라. 하지만 기억해—네가 생각하는 동안 잘생이 얼굴이랑 몸에 멍이 점점 더 늘어나고 있다는 걸, 크크크.";
			link.l1 = "도블론을 가져다줄게...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "화물의 크기가 중요한 게 아니야—타이밍과 위험이 문제지. 뭐, 네가 좋다면 알아서 해.";
			link.l1 = "나만 믿어. 내가 잘 알아. 상자만 준비해 둬 - 여기서부턴 내가 맡을게.";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "준비됐소, 제독? 무기 도움이 필요하오, 아니면 아직 금이 부족하오?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "드디어 충분히 모았어! 가져가서 이제 끝내. 더 이상 신경 쓰이게 하지 마.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "말 조심해, 커틀라스. 난 준비됐지만, 돈을 더 모으려면 시간이 필요해.";
			link.l2.go = "Pelly_67";
			link.l3 = "그건 소량 무기치곤 너무 비싸! 도매로 훨씬 싸게 살 수 있는데! 됐어, 내가 직접 처리하지.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "오, 이게 다 얼마짜리 두블룬이냐! 하지만 걱정 마라 - 한 푼도 빠짐없이 계획에 쓸 거다. 안 그러면 마르쿠스가 나중에 무덤에서라도 날 파낼 테니까, 헤헤. 자, 이제 잘생긴 애드미럴한테 가서 다 준비됐다고 전해라.";
			link.l1 = "여기서 명령하는 건 나다. 이제 움직여.";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "그래, 그게 문제로군. 계획이 뭐요, 제독?";
			link.l1 = "어디서든 빨리 그걸 비축해야겠어. 아니면 대상 행렬을 습격해서 내가 필요한 걸 싣고 있길 바라는 수밖에.";
			link.l1.go = "Pelly_49";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "나한테서 뭘 원하는 거야?";
			link.l1 = "내 친구, 나는 장 피카르를 찾고 있어. 혹시 그 이름을 쓰는 사람인가?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "가능성은 있지. 하지만 네 얼굴은 기억나지 않는다.";
			link.l1 = "너무 거칠게 굴지 마, 장. 나는 마르쿠스 타이렉스가 보낸 사람이야. 내 임무는 너를 여기서 데리고 나가는 거다.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "마르쿠스? 쉬잇... 조용히 해. 미안하다, 친구야, 그건 몰랐어. 하지만 여기서 얘기하면 안 돼, 빌어먹을 경비들이 사방에 있고 항상 엿듣고 있어... 네가 스페인 놈들 사이에서 환영받는 손님인 것 같으니, 밤에 오두막 중 하나에서 나를 찾아와. 그때 얘기하자. 기다릴게, 형제.";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "여긴 안전해... 이름이 뭐야, 형제?";
			link.l1 = "Captain "+GetFullName(pchar)+". 이제 말해 봐, 어떻게 이런 곤경에 빠지게 된 거지. 타이렉스가 모든 걸 알고 싶어 해.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "윌렘스타트의 선술집에서 낯선 사람이 다가왔어... 그가 네덜란드 대상단을 털자며 동료가 되어 달라고 하더군. 나는 브리건틴을, 그는 꽤 독특한 폴라크선을 가지고 있었지. 그래서 카라카스 근처에서 대상단을 쫓아가 약탈했어... 밤이었고, 우리는 전리품을 나누고 있었는데, 어둠 속에서 거대한 스페인 갈레온이 나타났지\n내 동료는 도망쳤고, 나도 도망쳤어. 하지만 내 브리건틴은 이미 손상돼서 갈레온과 다른 두 척의 배를 따돌릴 방법이 없었지. 놈들이 우리 배에 올라타서, 살아남은 자들을 이곳에 가축처럼 팔아넘겼어.";
			link.l1 = "알겠소. 그게 사고였다고 생각하시오? 나는 그 갤리온에 대해 말하는 거요.";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "내가 알 리가 있나. 총격 소리를 들었을지도 몰라, 메인 근처에서 멀지 않았으니까.";
			link.l1 = "흠. 그럴 수도 있지. 전에 네 옛 동료를 만난 적이 있나? 그가 누구지?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "처음 보는 사람이었어. 자기 이름은 이그나시오 마르코라고 했고, 영국을 위해 일하는 사략선장이라더군. 꽤 진지한 인상이라서, 나도 이 일에 참여하기로 했지. 경험 많은 선원이고 선장인 건 확실해. 뒤에는 멋진 선원들이 따르고 있고, 그의 폴라크 배도 정말 아름답더군. 그런 배는 흔히 볼 수 있는 게 아니야.";
			link.l1 = "이그나시오 마르코? 영국의 사략선인가? 그는 스페인 사람인가?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "그는 포르투갈인이지, 스페인 사람이 아니야. 영국의 사략 허가장이 뭐가 문제야? 우리 중에 스페인 놈들도 많은 거 알잖아.";
			link.l1 = "알겠어. 좋아, 여기서 탈출하는 것에 대해 얘기해 보자. 생각나는 거 있어?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "너희 숫자가 얼마나 되지?";
			link.l1 = "내 배, 바르크엔틴, 그리고 펠리 더 커틀라스의 부하들. 내 배는 마라카이보 항구에 정박해 있다.\n커틀라스는 과히라 만에 상륙해서 그곳에 야영지를 차렸다.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "흠...";
			link.l1 = "뭐야, 혹시 타이렉스가 전열함을 여기로 보낼 거라고 기대했나?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "나는 아무 기대도 안 했어. 사실, 마커스가 날 잊지 않은 게 놀랍군.";
			link.l1 = "그 자가 안 했지, 뻔하잖아. 그래서, 뭐 좋은 생각이라도 있어?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "여기서 도망칠 방법은 없어 – 이 농장은 경비가 너무 삼엄하고, 사방이 야생 정글이야. \n강제로 공격하는 것도 소용없어; 네 인원도 부족하고, 근처에 요새까지 있거든.";
			link.l1 = "혹시 너와 네 부하들이 안에서 우리를 도와줄 수 있겠나? 뒤에서 놈들을 세게 쳐 줘.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "뭘로? 맨손이랑 녹슨 마체테로?";
			link.l1 = "만약 네가 무기를 가지고 있었다면 어쨌겠냐?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "음, 그렇다면 우리가 놈들에게 지옥을 보여줬겠지. \n하지만 문제가 하나 있어. 네가 안으로 들고 들어가는 건 전부 검사하니까, 무기를 몰래 들여갈 방법이 없어. \n그러니 이 일은 잊는 게 좋겠어.";
			link.l1 = "그래도 지금으로선 그게 우리가 택할 수 있는 최선이야. 너와 네 부하들에게 무기를 어떻게 전달할지 생각해보겠다... 말해봐, 싸울 수 있는 사람이 몇이나 되지?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "서른 명쯤 될 거야.";
			link.l1 = "그럼 세이버 서른 자루군... 권총도 있으면 도움이 될 거라 생각해.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "선장님, 이 일 정말 진심이십니까?";
			link.l1 = "그래, 나다. 일부러 여기 온 거고, 농담 따위 할 생각 없어. 또 뭘 쓸 수 있는데?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "좋아... 일단 한번 해보자고. 우리 녀석들은 번지르르한 레이피어나 그런 무기에 익숙하지 않으니, 그냥 단순한 냉병기면 충분해. 총도 마찬가지야, 제일 싼 걸로도 괜찮아. 머스켓 한두 자루라도 구해주면 큰 도움이 될 거야; 머스켓 잘 다루는 녀석들이 몇 명 있거든. 탄환, 화약도 필요해. 치료약도 있으면 정말 고맙지.";
			link.l1 = "알겠소. 칼과 도끼는 배의 무기고에서 가져갈 수 있소. 나머지는 구하기가 좀 더 까다롭지. 전부 구하면 알려주겠소.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "서둘러, 형. 여기서 반 년씩이나 있을 수는 없어, 이 빌어먹을 소몰이 일 때문에 하나둘씩 죽어나가고 있잖아. 나 필요하면 밤에 찾아와.";
			link.l1 = "알겠어, 친구. 잠깐만 기다려, 오래 안 걸릴게. 그리고 조심해, 아직 너를 포기할 이유를 주지 말라고.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "소식 있나, 친구? 무기 모아왔어?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "그래. 탄약 상자가 과히라 만에 있어. 이제 남은 건 그걸 플랜테이션에 몰래 들여놓을 방법을 찾는 것뿐이야.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "내가 할게. 기다려.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "좋소, 선장. 나는 이미 그걸 어떻게 할지 생각하고 있었소.";
			link.l1 = "그렇게 들으니 기쁘군. 무슨 일로 왔나?";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "이 플랜테이션에서는 설탕을 만들고 카카오콩을 재배하지. 가끔은 주인이 직접 물건을 팔기도 하는데, 그게 더 이익이 되거든. 그에게 제안을 해 봐. 돈 대신 물건으로 값을 치러. 박스에 담을 수 있는 것들, 예를 들면 코프라나 바닐라, 커피 같은 거 말이야. 흥정할 때는 신경 써서 하되, 너무 무리하지는 마라\n무기 몇 개를 한두 개 박스에 숨기고 표시해 둬. 저녁에 교환을 약속해서, 그들이 박스를 밤새 밖에 두게 만들어\n밤이 되면 우리가 네가 표시한 박스를 찾아서 무장하고, 스페인 놈들에게 본때를 보여 주지. 물론 네 도움이 필요하다.";
			link.l1 = "좋은 생각이야, 형제! 아주 좋아, 이 계획 마음에 들어. 그대로 밀고 가자.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "마지막으로 한 가지 더 말하자면, 교환할 때는 한 가지 종류의 상품만 제안해라. 상품 종류가 많아질수록 경비병들이 더 많은 상자를 검사하게 된다.";
			link.l1 = "동의해. 그럼 한 종류만 고르지. 커피, 바닐라, 그리고 코프라라고 했지?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "그래. 이건 플랜테이션 주인에게 좋은 거래처럼 들릴 거야.";
			link.l1 = "알겠어. 거래가 성사되면 알려줄게.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "가라, 친구야, 시간은 금인데 우리에겐 남은 게 없어...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "...";
			link.l1 = "(조용히) 거래는 성사됐어. 상자들은 내일 저녁에 플랜테이션으로 배달될 거야. 네가 필요한 상자에는 'W'라는 글자가 표시되어 있어. 나머지 상자들에는 알파벳의 다른 글자가 붙어 있지. 사람들 준비시켜. 우리는 새벽 세 시쯤, 해 뜨기 전에 공격할 거야.";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "신호만 주면 시작하겠소...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "드디어! 다시 바다를 보게 되는구나! 바다가 어떻게 생겼는지, 어떤 냄새였는지 거의 잊을 뻔했어. 잘했어, 선장! 너한테 신세를 졌군.";
			link.l1 = "신경 쓰지 마, 나중에 해결하자... 이제 배에 올라타서 여기서 나가자!";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Greetings "+pchar.name+". 다시 만나서 반갑네, 그리고 이번 모험에 함께하게 되어 나도 기쁘네. 이번 일은 힘들겠지만, 우리라면 반드시 해낼 거라 믿어.";
			link.l1 = "다시 만나서 반갑군, 피카르. 다 듣고 있으니, 네 모험 이야기를 해봐.";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "나는 이미 마르쿠스에게 말했고, 이제 너에게도 말할게. 내가 마라카이보의 플랜테이션에서 노예로 있을 때, 스페인 놈들에게서 뭔가를 배웠지. 그 자식들, 술만 마시면 입이 아주 가벼워지거든... 들어봐, 마라카이보 만에서 남동쪽으로 가면 작은 마을이 하나 있어. 정글 깊숙이, 두 산 사이에 숨겨져 있지. 이름도 기가 막혀: 산티아고-데-로스-카바예로스-데-메리다. 그냥 메리다라고 부르자고\n아직은 별로 흥미롭지 않게 들리지? 하지만 그 마을을 둘러싼 산에는 보석이 가득하더라고. 에메랄드, 오팔, 그리고 전설의 파이어 오팔까지\n내가 알기로는, 메리다의 정착민들은 이 보석들에 대해 총독에게 알리지 않았어. 하지만 곧 총독이 알게 될 거고, 그래서 우리가 스페인 식민 관리들이 오기 전에 메리다에 가봐야 해.";
			link.l1 = "정착지를 약탈하고 싶나?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "맞아. 그곳은 정글과 산 속에 묻혀 있고 주둔군도 적어서, 해적 부대에게는 쉬운 먹잇감이지. 게다가 바다에서도 멀리 떨어져 있어서, 창과 활을 든 야만인 말고는 아무도 자신들을 공격할 거라 생각하지 않아.";
			link.l1 = "그 정착지에 귀한 보석이 있다는 걸 얼마나 확신하지?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "만약 우리의 모험이 헛된 단서로 끝난다면, 내가 직접 당신 배에서 장교든 선원이든 되어 일하겠소. 갑판을 청소하고 수많은 백병전에 나서서 당신과 마커스에게 진 빚을 모두 갚을 때까지 싸우겠소.";
			link.l1 = "알겠소... 좋아, 메리다로 가는 길을 아시오?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "물론 정글을 통과하는 정확한 길은 모르지만, 현지 인디언들 중에서 안내인을 고용할 거야.\n마라카이보 호수 남쪽에 상륙해서 인디언 마을을 찾아가고, 길을 아는 사람을 찾아보자.";
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "선장, 내 말투 정말 미안한데, 대체 왜 아직도 메리다에 안 간 거야? 어? 우리 공동의 목적에 침을 뱉은 거라고! 레프리콘이랑 나는 너 없이 떠난다. 타이렉스에게는 내가 다 설명할 거고, 넌 그냥 가. 여기, 마라카이보에서 도와준 대가로 5만 페소 가져가. 친구들한테 빌린 거야. 잘 가라. 젠장, 정말 실망이군, 널 더 믿었었는데.";
			link.l1 = "흠... 미안하군.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "여기에 도착했군. 앞에 정글이 있다. 먼저 인디언 마을을 찾아가서 길잡이를 물어봐야겠어.";
			link.l1 = "하자. 루크, 할 말이나... 아니면 조언이라도 있나?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "메리다 주둔군은 끝장났다. 마을에서 심각한 저항은 없을 거라 본다. 가자!";
			link.l1 = "돌격!!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "끝났다! 이제 영웅은 남지 않았군. 이제 이 '도시'의 총독과 얘기해야겠어. 설득이 통하는 사람이어야 할 텐데.";
			link.l1 = "나도 동의해, 그 놈을 '설득'하자!.. 장! 따라와!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //злой вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //мирный вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "잘했군, "+pchar.name+"! 이제 몫을 나눌 시간이야. 이미 계산은 끝났어. 상자에는 보석이 거의 2000개나 있었지: 에메랄드 1560개, 오팔 1032개, 그리고 파이어 오팔 363개야. 네 몫은 3분의 1이니까, 에메랄드 350개, 오팔 244개, 파이어 오팔 63개다. 자, 받아.";
            }
            else
           	{
           	dialog.text = "잘했군, "+pchar.name+"! 이제 몫을 나눌 시간이야. 이미 계산은 끝났지. 상자에는 보석이 거의 2,000개나 있었어: 에메랄드 1,050개, 오팔 732개, 그리고 파이어 오팔 189개야. 네 몫은 3분의 1이니까, 에메랄드 350개, 오팔 244개, 파이어 오팔 63개다. 자, 받아.";
           	}
			link.l1 = "좋았어!";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "이제 저를 구해주신 데 대한 제 빚에 대해 이야기해 봅시다.\n제가 알기로 당신께서 상당한 비용을 치르셨지요.\n어떤 보상이 공정하다고 생각하십니까?\n보석에서 제 몫을 떼어 드리겠습니다.";
			link.l1 = "네 몫의 3분의 1이면 충분해. 너도 돈이 필요하잖아 – 배를 사고 보급하려면, 선원들 월급도 줘야 하고...";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "고마워, 친구! 네가 적어도 절반은 달라고 할 줄 알았지. 지금 돈이 정말 필요하거든. 자, 이 보석들을 가져가.";
			link.l1 = "정말 대단한 습격이었어, Jean! 히스파니올라, Tyrex로 가자.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "오, 이런 만남이! 만나서 반갑군, "+pchar.name+". 어떻게 지내?";
			link.l1 = "꽤 괜찮아. 최근에 레드 울프의 보물을 찾았지. 이제 마르티니크로 가서 우리 둘 다 아는 친구를 만나려고 해. 타이렉스를 보고 싶어?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "그래. 파스칼 라부아지에에 대해 그와 얘기하고 싶어. 마르쿠스가 나를 그 반은 도적, 반은 상인인 놈한테 보냈지. 내가 시키는 대로 했더니, 그 자식은 쓰레기 같은 걸 주면서 대단한 보수라고 우기더군. 거기서 바로 죽여버릴 수도 있었지만, 마르쿠스가 예의를 지키라 해서 참았지... 그러니 이 엉망진창은 마르쿠스가 알아서 처리해야 해.";
			link.l1 = "미안하지만, 마르쿠스는 아무것도 안 할 거야. 네 눈깔은 걔랑 한패거든.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "뭐야, 이게?";
			link.l1 = "그래, 하지만 이 얘기는 내가 한 거 아니라고 해. 라부아지에도 얼마 전에 나한테 사기 쳤어. 타이렉스가 나한테도 너한테처럼 도와달라고 했지. 이슬라 테소로에서 들었는데, 네 눈 달린 놈 건드리는 건 마커스 건드리는 거랑 똑같다고 하더라. 그러니까 이 일은 잊어버리는 게 좋을 거야. 너만 이런 일 겪는 것도 아니고, 마지막도 아닐 테니까.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "알겠어. 너도 그 둘한테 당한 거야?";
			link.l1 = "그래, 맞아. 나도 그 안경잡이한테 좀 사고를 칠까 생각했었지, 그 자에 대해 더 알기 전에는 말이야. 하지만 그럴 가치도 없더라고.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "아무도 절대 알지 못한다면 그 자식에게 복수하려고 하겠어?";
			link.l1 = "하! 물론이지! 하지만 어떻게 해야 할지는 모르겠군. 라부아지에의 플루트를 공격해 봐. 언젠가 네 선원들이 술에 취해서 다 불어버릴 거야. 어떻게 돌아가는지 모르는 거야?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "지금 마르티니크로 가는 중이오? 라 베가에는 언제 다시 도착할 생각이오?";
			link.l1 = "마커스가 나에게 3주를 줬어.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "두 번 안에 끝내 보도록 해. 내가 곰곰이 생각해 볼게... 14일 뒤에 고나이브 만에서 나를 찾아. 바로 그리로 가고, 라 베가에는 들어가지 마.";
			link.l1 = "뭔가 꾸미고 있는 게 보여, 하하. 좋아. 내가 한번 해볼게.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "그렇게 하는 게 좋겠어. 또 보자!";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"네 배는 어디 있지? 라 베가에서 온 거야? 젠장! 내가 들키지 않고 몰래 오라고 했잖아. 내 계획이 다 망가졌어. 젠장할!..";
				link.l1 = "음...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "거기 있었군, "+pchar.name+". 네가 여기 있어서 다행이야. 동료들은 배로 돌려보내. 이건 사적인 대화야.";
				link.l1 = "좋소.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "거기 있었군, "+pchar.name+". 네가 여기 와서 다행이야. 할 일이 있는데, 들어볼 준비됐나?";
				link.l1 = "물론이지!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "이미 말했잖아 - 네 장교들 내보내!";
				link.l1 = "그래, 그래, 알았어.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "좋아. 이제 우리끼리 자유롭게 얘기할 수 있겠군. 너한테 사업 제안을 하나 하지. 들을 준비 됐나?";
				link.l1 = "물론이지!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "라 베가를 잘 아시오?";
			link.l1 = "음... 그런 것 같아. 왜 묻는 거지?";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "현지 상점 오른쪽에 있는 창고 본 적 있어? 오두막들 사이에 유일하게 큰 집 말이야.";
			link.l1 = "항상 닫혀 있는 그곳 말인가? 그래, 본 적 있어. 왜 묻는 거지?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "잘 봤군 - 여긴 항상 닫혀 있지. 네가 마르티니크에서 임무를 수행하는 동안, 우리의 공통 친구 라부아지에가 마커스 타이렉스의 손님으로 여기서 사흘을 머물렀어. 그들은 이 집에서 럼주를 마시며 즐겁게 시간을 보냈지.";
			link.l1 = "흠...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "그 후 라부아지에의 부하들이 상자와 꾸러미 몇 개를 집 안으로 끌고 들어왔소.\n그 다음 그는 떠났지.\n마르쿠스는 매일 몇 시간씩 그곳에 머물고 있소.";
			link.l1 = "뭐 좋은 생각 있어?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "무슨 제안이야? 분명 이 집이 라 베가에 있는 라부아지에의 근거지일 거야. 창문으로 많이 보진 못했지만, 안에 물건들이 쌓여 있더라. 그 안경쟁이가 우리한테 진 빚을 갚을 능력은 충분히 있는 것 같아.";
			link.l1 = "흠, 흠... 들어가고 싶어? 저 닫힌 문은 어쩔 건데? 무겁고 튼튼해서 조용히 들어갈 방법은 없어.";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", 나를 바보로 아나? 이미 다 해결했어. 자물쇠에 밀랍을 찍어서 열쇠를 만들었지. 돈이 꽤 들었지만, 그건 내 문제야.";
			link.l1 = "헤! 그럼 왜 나를 기다리고 있는 거지?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "그게 더 안전할 거야. 게다가, 내가 믿을 수 있는 사람은 너뿐이니까. 머리 하나보단 둘이 낫고, 눈도 둘보단 네 개가 더 낫지.";
			link.l1 = "그래, 맞아. 라부아지에를 속이려면 그가 가진 눈만큼이나 많은 눈이 필요하지, 하하하! 그런데 티렉스는 어쩔 건데? 우리가 파스칼레의 물건을 뒤지는 동안 그놈이 집에 들어오면 어떻게 하지?\n";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "걔는 안 그래. 항상 자정이면 자기 집에 돌아가. 내일 밤 라 베가로 갈 준비됐지? 그놈들은 누가 자기들을 망쳤는지 절대 모를 거야. 넌 아직 마르티니크에 있고, 나는 라 베가를 일주일 전에 떠났으니까.";
			link.l1 = "네 눈 달린 그 자식 한번 엿먹이고 싶지. 하지만 말해봐, 장, 우리가 집에서 어떻게 통이랑 궤짝을 나른다는 거야?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "분명히 거기서 우리는 상자나 물품 통보다 더 값진 물건들을 찾을 수 있을 거야, 그리고 훨씬 가볍겠지. 그래서, 할 거냐?";
			link.l1 = "그래, 맞아!";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "좋아, 내가 너를 잘못 본 게 아니라서 다행이군. 이제 쉬자, 자정에 라 베가로 출발하니까.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "갈 시간이다. 이 자식 털고 동이 트기 전에 여기서 꺼지자.";
			link.l1 = "전진하자!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "쉿... 이제 조용히 파스콸레 집으로 가자. 나를 따라와.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "이것 좀 봐라 - 여기저기 물건이 널려 있군. 시작하자. 문 옆에 있는 상자를 확인하고, 그다음 위층에 올라가서 방 하나를 맡아라. 나는 여기 남아 있겠다. 귀중품을 잡동사니 사이에 숨기는 요령을 아니까. 눈과 귀를 똑바로 열고, 창문 근처에는 가지 마라.";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", 뭘 가지고 있지? 흥미로운 거라도 있어?";
			link.l1 = "와서 봐. 이거 좀 대단한데.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "젠장! 이제야 왜 타이렉스가 매일 이곳에 오는지 알겠군. 여긴 안경잡이의 창고일 뿐만 아니라 창녀촌이기도 하잖아.";
			link.l1 = "여기서 그녀는 노예인 것 같아.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "알겠어. 저 여자 좀 봐라 - 딱 봐도 항구 창녀잖아... 우리한텐 재수 없는 일이야. 죽여야겠다.";
			link.l1 = "정말 우리가 그래야 하나?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "그 여자가 우리 얼굴을 봤고 네 이름도 들었어. 타이렉스에게 전부 말할 거야.";
			link.l1 = "흠...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "네가 선택해. 그녀의 목숨이 네 목숨값이 될 수도 있어.";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "이 창녀를 믿을 생각은 꿈도 꾸지 마라. 내일이면 타이렉스가 전부 알게 될 거다.\n검은 표식을 받고 싶으냐?";
			link.l1 = "아니, 없어. 그리고 그 계집을 죽이고 싶지도 않아 - 쓸모가 있거든. 그녀는 나랑 같이 간다.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "바보 짓 하지 마! 기회만 생기면 저 여자는 도망칠 거야. 이마 좀 봐, 낙인 보이지? 저 여자는 도둑이야.";
			link.l1 = "흠. 네 말이 맞는 것 같군, 장. 좋아, 저 여자 끝내고 여기서 나가자.";
			link.l1.go = "rocur_82";
			link.l2 = "나는 그년을 내 배에 두고 있을 생각 없어. 절대 도망칠 수 없는 곳에다 처박아 둘 거야, 거긴 비명 소리 들을 귀도 없어. 거기서도 계속 자기 일 하게 될 거고... 내 전용 창녀지, 공짜로 말이야, 크크!";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "이제 끝이야, 그녀가 마커스에게 무슨 말이라도 할 리 없겠지...";
			link.l1 = "불쌍한 아가씨로군... 하, 뭐, 사람들이 그러잖아, 행운의 여신은 못된 년이라고...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "당신은 친절한 사람이군, "+pchar.name+". 왜 그녀한테 신경 쓰려고 해? 뭐, 네 선택이지. 우리가 나갈 때 그녀가 조용히 있도록 해.";
			link.l1 = "그 여자가 아니라면, 이미 죽은 거야.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "A bit. A chest full of doubloons, a handful of rubies, a map of Hispaniola and some rum.";
			else sTemp = "Nothing of value.";
            dialog.text = "뭘 찾았어?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("You have received two treasure collections.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "또 내게 운이 따랐군. 자, 네 몫 가져가라. 이걸 혼자서 전부 해안까지 옮길 수는 없지. 안경쟁이가 우리한테 전액을 지불했어.";
			link.l1 = "훌륭해! 잘했어, Jean!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "이제 가!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "좋아. 끝났군. 조용하게 처리했어. 이제, 배로 돌아가자.";
			link.l1 = "하, 좋은 생각이야.";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "그래, "+pchar.name+". 이제 우리는 헤어질 시간이야. 다시 만날 수 있을지 모르겠지만, 너를 알게 되어 즐거웠어, 친구.";
			link.l1 = "아, 이제 그만, 라 베가에서 자주 보게 될 거요.";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "아니. 이제 Tyrex와는 끝이야. Lavoisier와 엮인 이 소동이 마지막 결정타였어.";
			link.l1 = "흠... 알겠어, 그냥 잊어버려. 우리는 원래 우리 것이었던 걸 되찾았으니까. 타이렉스가 꽤 쏠쏠한 정보를 주지 않나? 지난번엔 레드 울프의 보물 덕분에 50만 이상 벌었지.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "그럼 말해 봐, 그거 찾느라 고생 좀 했나?";
			link.l1 = "음... 쉽지 않았지. 고민도 많이 하고, 여기저기 돌아다니고 싸우기도 했어. 그래도 그만한 가치가 있었던 것 같아.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "타이렉스에게 얼마를 줬지?";
			link.l1 = "세 번째.";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "이 일에서 그가 한 역할이 뭐였지? 마르쿠스가 정확히 뭘 했던 거야?";
			link.l1 = "흠... 그가 나에게 레드 울프의 항해일지를 주었군...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "이게 다야? 맞지?";
			link.l1 = "음... 그렇지 않았다면 울프릭 선장에 대해 절대 알지 못했을 거야...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", 아직도 Tyrex가 더러운 일은 남에게 시키는 거 안 보여? 그 자식이 직접 할 수 있는 일이면 너한테 보물 찾으라고 시켰겠어? 천만에! 분명히 자기가 먼저 해보려다가 다 망치고, 결국 너 불러서 마무리하게 한 거야. 넌 머리 굴리고, 몇 주씩 바다에서 싸우고 목숨까지 걸고 있는데, 그 개자식이랑 그 역겨운 네눈박이 친구는 La Vega에서 창녀랑 놀고 있었지. 그런데도 그걸로 25만 페소나 챙겼다니까. 그냥 그렇게\nMerida 습격 때 자기 개 Leprechaun을 우리 도우라고 보냈다고 생각해? 아니, 자기 이익 챙기려고 보낸 거지. Marcus가 직접 할 수 있는 건 다 자기가 해. 혼자든, Cutlasses, Balds, Leprechauns, 그리고 그 밖에 푼돈 받고 일하는 바보들이랑 같이든 말이야. 너나 나 같은 놈들은 Marcus가 혼자 감당 못하는 일거리만 받아오는 거고\n그동안 그 자식 위해서 해준 일들 기억나지? 네가 얼마나 벌어다줬는지 세어봐라. 난 이제 질렸어. 이제 돈도 있고, 멋진 코르벳도 있고, 충직한 선원들도 있지... 이제부터 난 자유인이다. 자메이카로 간다—거기서 사략 허가장이라도 받을 수 있겠지.";
			link.l1 = "내 생각엔 너가 Tyrex에 대해 완전히 맞는 것 같진 않아... 하지만 행운을 빌게, Jean! 자메이카에서 꼭 성공하길 바란다.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "그러지. 너도 행운을 빌고, 내가 한 말을 곰곰이 생각해 봐. 마르쿠스의 앞잡이 노릇은 네게 어울리지 않아. 네가 훨씬 더 큰 일을 해낼 수 있다는 걸 나도 알아. \n자, 그럼... 잘 가라, 형제여! 신의 가호가 있기를!";
			link.l1 = "사냥 잘 해라, Jean!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", 말해 봐, 우리가 어쩌다 이렇게 오랫동안 정글에서 시간을 보내게 된 거지? 이제 내 계획은 엉망이 됐어. 에휴... 잘 가라, 친구...";
			link.l1 = "헤헷...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "떠날 시간이야, 얘들아. 젠장, 프린스, 네가 날 놀라게 했군. 도시 하나를 불태워 놓고, 정작 중요한 순간에는 손에 피 한 방울 안 묻히더라니.";
				link.l1 = "내가 도시를 불태우라고 명령한 적 없어!";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "떠날 시간이야, 얘들아. 루카스, 넌 놓쳤다. 프린스가 멋지게 처리했고, 꽤 이득도 챙겼지!";
				link.l1 = "도시는 어쩌고, 잘생긴 놈아?! 내가 약속했잖아!";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "적어도 그걸 구하려고 하진 않았군. 그랬다면 우리 놈들이 먼저 네놈 배를 갈랐을 거다. 오늘은 놈들에게도 힘든 하루였지. 좀 풀어야 했어. 곧 익숙해질 거다. 넌 해적 될 자질이 다 있더라.";
			link.l1 = "충고는 고맙지만, 내가 부탁한 기억은 없군. 가자.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = " 농담인 줄 알았지. 뭐... 네가 너무 성급했어. 도시는 끝났어. 해안의 형제단이 움직이면 항상 이렇게 되지. 곧 익숙해질 거야.";
			link.l1 = "확신은 안 서. 좋아, 가자.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "이봐... 방금 그게 뭐였지?";
			link.l1 = "뭐야, 아직도 이해 못 했어? 내가 너를 샀다니까. 예전에 네가 내가 스페인 놈들에게 접근할 수 있다고 했지, 그래서 그걸 이용한 거야.";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "알겠어, 내가 바보는 아니니까. 그런데 우리 다른 계획 진행 중이었던 거 아니었어?";
			link.l1 = "음, 커틀라스랑 나는 네가 반란이나 추격 중에 죽는 꼴은 좀 아니라고 생각해서, 그냥 너를 통째로 사기로 했지.";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "하, 나를 모욕하지 마라. 나는 테락스의 선장들 중 하나다. 칼 다루는 법쯤은 안다.";
			link.l1 = "그건 의심하지 않아. 하지만 자유로워진 게 진심으로 불만이야?";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "아니, 아니야 - 나는 고맙지. 다만... 그 많은 금화를 다 써버린 건 좀 과하지 않았나? 생각만 해도 속이 뒤집혀. 반면에 그 플랜터는 광이 번쩍이는 은쟁반처럼 빛나더라.";
			link.l1 = "그래, '세기의 거래'라니, 정말이지. 좀 쓰리긴 하지. 하지만 시간은 금보다 더 소중해, 장. 너희 모두를 위해 권총이랑 약을 찾아다니는 것도...";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = "고맙긴 한데, 이봐 친구, 너 참 바보구나 - 기분 나쁘게 듣지 마. 내 부하들이 칼질은 잘 못한다고 말했잖아. 하지만 방아쇠는 아무나 당길 수 있지. 너는 커틀라스나 도끼 챙길 때처럼 아무 권총이나 약을 창고에서 가져올 수 있었어 - 걔네는 가리는 거 없어.";
			link.l1 = "흠, 솔직히 그 생각은 못 했는데... 어쨌든 가자 – 커틀라스가 아마 조급해하고 있을 거야.";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "안녕하십니까, 선장님 "+GetFullName(pchar)+". 루크 더 레프리콘, 네 앞에 있지! 우리가 남부 메인 정글로 간다고 들었어.";
			link.l1 = "정확하다. 장선에 올라타라, 곧바로 출발한다.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "늙은 버커니어가 한마디 조언을 해주지, 선장. 우리가 셀바로 들어가면 인디언들을 반드시 만나게 될 거야. 그들에게 줄 선물을 챙겨가게. 인디언 전사들은 멋진 권총, 특히 결투용 권총을 아주 좋아하지. 나침반이나 망원경도 좋아하는데, 그런 걸 마법의 물건처럼 여겨. \n여자들은 값싼 장신구나 거울, 빗 같은 잡화들을 더 좋아하지. 만약 그들과 싸우게 된다면, 블런더버스나 아르퀘버스를 쓰게나. 산탄은 갑옷을 입지 않은 적에게 아주 효과적이거든. 정착지 안에서는 종이 탄약을 쓸 수 있는 총을 추천하네.";
			link.l1 = "아주 좋아, Luke. 네 말은 잘 들었다. 배에 탄 걸 환영한다.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "마을에 도착하자마자 족장부터 만나. 그리고 선물도 챙겨, 아니면 소용없으니. 그의 사람들 중에 앞쪽 정글의 비밀 통로를 아는 이가 있는지 꼭 물어보고, 여행을 두려워하지 않는 자들도 찾아봐. 나도 같이 갈 테니, 어려움이 생기면 나에게 말해.";
			link.l1 = "가자! Jean, Luc - 나를 따라와!";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "질문 있나, 선장?";
			link.l1 = "지금은 없어, Luke.";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "그래! 내가 그들의 추장과 얘기했고, 선물도 줬지. 그러고 나서 그가 자기 사람들을 불러 모아 회의를 열었어. 그들 중 몇몇은 메리다로 가는 길을 알지만, 아무도 가려고 하지 않아—카퐁족이라는 다른 부족을 두려워하거든. 그 카퐁족 때문에 현지인들이 겁을 먹고 있어. 그 망할 놈은 우리가 혼자 힘으로는 길을 찾을 수 없고, 고용할 수 있는 안내인도 없다고 주장해. 그럼 이제 우린 뭘 해야 하지, 어?";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "해독제가 내게 있어.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "흠, 알겠소... 선장님, 겁쟁이도 탐욕 앞에서는 용기를 내게 마련이오. 일을 맡길 만큼 후한 보상을 약속하시오... 아니, 잠깐만. 좀 더 교활하게 접근해 보시오 – 그들의 여자들을 이용하는 거요. 선물 좀 주고 남편에 대해 물어보면, 우리가 찾는 안내자를 알아낼 수 있을 거요. 남편이 도와주면 구슬과 거울을 한아름 주겠다고 여자에게 약속하시오. 아낌없이 약속하고, 설득하시오.";
			link.l1 = "헤! 뭐, 최소한 시도는 해볼 수 있지. 잘 될지는 모르겠지만...";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "음, 또 다른 방법이 있긴 해... 하지만 그리 좋은 방법은 아니야, 무슨 말인지 알겠지?";
			link.l1 = "또 다른 방법이 있어? 말해 봐! 인디언 여자들한테 가서 남편들 좀 우리 편에 서게 해 달라고 빌고 싶진 않거든.";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "이 방법은 아주 오래된 수법이지. 카퐁족보다 너를 더 두려워해야 한다는 걸 보여 줘. 알잖아... 추장에게 네 해적들이 마을의 모든 여자들, 특히 그의 아내와 딸들에게 무슨 짓을 할 수 있는지 말해 줄 수도 있지. 고문하겠다는 협박도 곁들일 수 있고.\n어쨌든, 이 인디언들이 널 두려워하게 만들 방법은 네가 잘 찾아낼 거라 확신해. 개인적으로 나는 이 방법을 좋아하지 않아, 그럴 만한 이유도 있고.";
			link.l1 = "이유? 예를 들면? 내 생각엔 이게 꽤 효과적이고 직설적인 해결책 같은데.";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "일단, 저 일 이후로 우리가 마을에서 환영받을 일은 없을 거야. 자칫하면 함정에 빠지거나 다른 골치 아픈 상황에 처할 수도 있지. 그리고 또 한 가지, 음... 그냥 마음이 내키지 않아. 무장한 적을 상대하는 건 그렇다 쳐도, 여자들을 위협하는 건 또 다른 문제잖아. 인디언들을 좀 더 외교적으로 처리할 방법을 찾아보는 게 좋겠어.";
			link.l1 = "알겠어, 생각 좀 해볼게. 구슬로 아가씨를 꼬셔볼까... 아니면 추장의 딸들을 괴롭힐 기발한 방법을 한번 생각해볼까, 하하!";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "한 가지 더 말씀드리죠, 선장님. 추장에 따르면, 우리는 정글에서 적대적인 인디언 부족을 만날 수도 있다고 합니다. 아마도 소수의 식인종일 가능성이 높지만, 만일을 대비하는 게 좋겠지요. 만약 호전적인 부족이라면 무기에 독을 바를 테니, 반드시 부하들에게 해독제를 준비해 주십시오.   저와 제 부하들은 항상 해독제를 넉넉히 가지고 다닙니다. 당신의 해적들은... 해독제를 저에게 가져오면 제가 당신 부하들에게 나눠주겠습니다. 최소한 열두 병은 필요합니다. 당신과 장교들을 위해서도 꼭 몇 병 챙기시기 바랍니다.";
			link.l1 = "좋아. 해독제를 가져올게.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "좋아. 그것들을 내게 줘. 나머지는 내가 알아서 할게.";
			link.l1 = "저기...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "물약 마흔두 개면 충분해. 나머지는 네가 가지고 있어.";
			link.l1 = "좋아...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "선장님, 당신의 인디언들인 하야미와 타고파가 약속한 선물을 너무 오래 기다리다가, 다른 마을로 가서 카셰리를 마시며 춤추러 떠났소. 당신 식의 거래 방식으론 우리에게 득이 될 게 없을 것 같은 예감이 드는군. 유감이지만, 당신은 여기서 빠지시오. 피카르가 원정을 이끌 거요.";
			link.l1 = "그럼 다들 엿 먹어라!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "선장, 이게 뭐야? 괜히 시간만 잔뜩 낭비했잖아! 당신 식으로 일하면 우리한테 득 될 게 하나도 없을 것 같아. 미안하지만, 이제 당신은 빠지시오. 피카르가 원정을 이끌 거야.";
			link.l1 = "그럼 다들 꺼져라!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "선장, 도대체 뭐 하는 거요? 가죽이랑 판자를 구할 시간이 열흘이나 있었잖소. 여기서 멀지 않은 곳에 마라카이보 마을도 있는데! 당신 식으로 일하면 우리 모두 망할 것 같군. 미안하지만, 이제 당신은 여기서 빠지시오. 피카르가 원정을 이끌 거요.";
			link.l1 = "그럼 다들 엿이나 먹어라!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "선장, 미안하지만 나도, 사실 당신도, 진작 라 베가에 있었어야 했어. 당신은 마커스와 나를 잊은 모양이군. 아무튼, 난 떠날 거야. 당신은 당신 할 일이나 계속해. 마커스에게는 내가 다 설명할 테니. 안녕히 계시오, 아쉽군. 난 당신을 더 좋게 봤었는데.";
			link.l1 = "흥...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "그러니까, 내 이해가 맞다면 너희들끼리 싸웠다는 거군. 전리품을 나누지 못해서 그렇지, Charlie Prince?";
			link.l1 = "레프리콘? 네가 여기 있군... 뭐, 별로 놀랍지도 않지. 그래, 그 욕심 많은 놈들이 해적 규율을 짓밟고 날 죽이려고 했어.";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "그래, 놈들이 너를 제대로 두들겨 패놨군, 왕자님. 젖은 똥처럼 생겼어\n그 코드에 대해 뭐라고 했지? 잘 들어, 내가 좀 알려주지. 나는 그 코드의 수호자라는 마커스랑 같이 일해봤어. 그 코드에 침 뱉는 놈들을 수도 없이 봤지. 그중 몇몇은 끔찍한 대가를 치렀고, 몇몇은 그냥 넘어갔어\n네가 원하는 건 뭐든 할 수 있어, 보상이 그만하면 말이지. 특히 아무도 안 보고 있다면 더더욱.";
			link.l1 = "그래... 너도 보물을 찾으러 온 거냐?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "정말 멍청한 질문이군. 내가 여기 히스파니올라 내 고향에서 이렇게 멀리 떨어져서 뭐 하겠어? 그래도 결국 난 너희 모두보다 똑똑하지. 너희 썩은 해적 본성을 잘 아니까. 난 그냥 기다렸지. 너희 쥐새끼들이 서로 물어뜯으며 싸우게 두고, 마지막에 적 하나만 남기되, 상처 입고 지치게 만들었어.";
			link.l1 = "적이라고? 이게 네 후원자의 규율을 따르는 방식이냐?! 그는 이 때문에 사람을 죽인다고!";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "나는 코드 프린스의 지배를 받지 않아, 나는 해적이 아니야. 배도 없어—여기 오려고 겨우 고물선을 빌렸지. 한마디로 그냥 버커니어일 뿐이야. 나는 사냥꾼이고, 들소를 사냥해서 부칸을 만들어. 우리 프랑스 버커니어들이 그놈들의 생계를 망친다고 주장하는 빌어먹을 스페인 놈들 때문에, 나는 마르쿠스에게 의지하고 보호를 받으려 했지. 그래서 가끔 그의 일도 도와주고 있어\n나는 해적은 아니지만, 내 부하들과 나는 싸움을 꽤 잘해. 네가 우리 활약을 봤잖아.";
			link.l1 = "우린 함께 약탈하고 싸웠지, 레프리콘. 서로의 등을 지키며, 목숨을 걸고 서로를 구했잖아. 이 모든 게 너한텐 아무 의미도 없는 거냐?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "솔직히 말해서, 나리, 난 당신이 마음에 든 적이 없어. 당신은 건방진 풋내기지. 술과 타락한 여자들을 좋아하고, Tyrex를 위해 돈 되는 일 몇 번 했다고 스스로를 대단한 해적으로 착각하는 놈이잖아\n게다가, 당신은 본래부터 살육자야. 카르타헤나에서 한 짓이 해적 동맹 내에서 당신의 위상을 높여줬다고 생각하나? 허허, 천만에. 당신 같은 괴물들 사이에서만 통하는 얘기지.";
			link.l1 = "아, 이거 정말 웃기네! 하하하, 진짜 천사가 직접 한 말이잖아! 이 늙은이 자식아!";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "이제 모든 게 정리된 것 같군. 이 소동도 끝낼 때가 됐지. 악마들이 지옥에서 널 너무 오래 기다렸어.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "마음에 드나, 흠?";
				link.l1 = "비켜!";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "그래, 어떻게 생각해?";
				link.l1 = "이게 웃겨? 레프리콘. 이게 뭐야?! 내가 학살을 시키라고 한 적 없어! 아무리 그래도 이건 너무하잖아?! 테락스가 기뻐하지 않을 거야!";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "그럼 왜 그렇게 죄지은 얼굴을 하고 있는 거지? 재미없어? 잘 들어, 앞으로 더 나빠질 거야. 오늘 학살이 그냥 그런 날이라서 일어난 줄 알아? 하, 그래, 그렇게 생각해라. 이런 건 일상이라고. 피카르는 눈 하나 깜짝하지도 않았어. 저놈들한테는 그냥 좋아하는 일 하면서 보내는 평범한 하루일 뿐이거든.";
			link.l1 = "그럼 너는? 그냥 지나가는 거야?";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "나는 해적이 아니야. 그리고 오늘 일에 끼고 싶지도 않았지. 그리고... 메리다의 검게 탄 땅 위에 여자들의 시신이 널린 걸 보고 그렇게 분노한다면, 왜 인디언들에게는 그런 짓을 했지, 왕자?";
			link.l1 = "내가 뭘 어쩌라고? 모든 걸 내팽개치고 마커스한테 기어가서 사과라도 하란 말이야?";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "난 그냥 네가 완전히 적응해서, 티락스의 선장들처럼 생각하고 행동하기 시작한 줄 알았지. 하지만 아니군, 하! 넌 이런 일 하기엔 너무 물러. 네 몫은 마커스에게 주고, 꼬리 내리고 떠나는 게 나을 거야. 이 일은 네 소명이 아니야.";
			link.l1 = "내 일은 내가 결정할 거야, 레프리콘. 그리고 네가 나를 모욕할 권리도 없어. 내 몫은 누구에게도 양보하지 않을 거다. 테락스랑 공평하게 나눌 거야.";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "그래. 하지만 네가 기절하기 전에 떠나는 게 좋겠어.";
			link.l1 = "그거 안 웃기잖아, 젠장.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "그렇다면 그를 잘 모르는 거군. 그래도 오늘 일로 기쁘지 않다면, 내가 제안할 말을 들어봐.";
			link.l1 = "이제 더 뭘 내놓을 수 있겠어?!";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "잘 듣도록 노력하는 게 좋을 거다, 이 녀석.";
			link.l1 = "흠, 말투가 마음에 안 드는군, 루카스. 하지만 좋아, 해 봐.";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "나는 그럴 만한 여유가 있지 - 너보다 오래 살아왔으니까, 왕자. 그래서 사격뿐만 아니라 눈썰미도 날카로워. 내가 뭘 눈치챘는지 알고 싶어?";
			link.l1 = "그냥 말해!";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "여긴 네 자리가 아니야. 그래, 너 잘하고 있어. 점점 나아지고 있지. 하지만 그건 네가 강한 선장이기 때문이지, 이게 진짜 네 운명이라서가 아니야. 네가 어떻게 테락스 쪽으로 돌아섰는지, 왜 그런 건지 난 몰라. 하지만 믿어, 이건 네 운명이 아니야.";
			link.l1 = "나는... 목표가 있어. 뭔지는 말해줄 수 없어.";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "그래서 그 목표에 좀 더 가까워졌나?";
			link.l1 = "아직 아니야.";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "글쎄, 오늘조차도 가까워지지 못했다면 여기서 더 얻을 건 없지. 좋은 사람이야, 왕자 나리. 인디언들을 인간으로 대했지. 그런데 결국 우리랑 여기 있게 된 게 아이러니하군. 내 조언은 이거야: 네 몫은 테락스에게 넘겨서 괜한 문제 피하고, 이 일에서 멀리 떨어져. 아직 기회 있을 때 네 영혼이나 구해.";
			link.l1 = "생각해 볼게.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "타고파가 바다의 아들인 그대를 맞이하오. 산속에 있는 스페인 정착지로 가는 길을 알려주길 원하시오?";
			link.l1 = "맞아. 너는 다른 네 동료들과 달리 우리 말을 잘하는구나.";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "타고파는 야라나우이와 자주 거래를 했지... 우리의 여정 대부분은 강을 따라 이동할 거야. 너희는 롱보트가 필요할 거다. 준비되어 있나?";
			link.l1 = "그래? 잠깐 빌려도 되겠군...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "우리 마을은 작아서, 긴 보트도 몇 척 없고 전부 고기잡이에나 쓸 만한 것들이오. 지금 우리에겐 먼 항해도 견딜 수 있는, 자네네 배에 있는 것 같은 좋은 긴 보트가 필요하오.";
			link.l1 = "흠... 그럼 장선이 여섯 척 필요하겠군. 배에는 그만큼 없는데.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "그럼 만들어 봐라. 너희 백인들은 육지에서 거대한 배도 고칠 수 있다면서, 긴 보트 몇 척쯤은 만들 수 있겠지.";
			link.l1 = "헤, 네 말이 맞는 것 같군, 타고파. 우리를 강으로 데려가라. 여기서 멀지 않기를 바란다?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "그렇지 않아. 따라와.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "내가 말했던 강이 여기야. 여기서부터 여정을 시작할 거다. 네가 배를 만들면 우리가 출발하지.";
			link.l1 = "알겠어, Tagofa. 끝나면 알려줄게.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "배들은 준비됐나, 백인 추장?";
			link.l1 = "그래. 내 부하들이 곧 저 배에 올라탈 거야.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "아주 좋아. 나랑 같이 첫 번째 배에 타. 타고파가 길을 안내할 거야.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "강을 건너는 부분은 끝났어. 여기서 스페인 식민지까지 멀지 않아. 저기 길이 보이니, 그 길만 따라가면 길을 잃지 않을 거야.\n카퐁 사냥꾼들로 가득한 숲을 간신히 피해왔지만, 여기도 그놈들 땅이야. 조심해야 해.";
			link.l1 = "걱정 마라. 그놈들이 추잡하게 칠한 얼굴을 내밀기만 하면 바로 쓸어버릴 테니까.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = "";
			link.l1 = "이봐! 타고파! 저기 봐! 저게 뭐지... 길 한가운데 있는 거? 인디언 물건 같은데.";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "카퐁족의 표시다. 경고야. 더 이상 나아가지 말라는 뜻이지. 카퐁족이 이미 우리를 발견했어.";
			link.l1 = "그리고 우리가 더 나아가면 어쩌지? 놈들이 우리를 공격할까?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "그래, 백인 추장. 네가 위협적으로 보여서 아직 우리를 공격하지 않은 것 같군. 그런데도 너를 위해 표지판을 세웠어.";
			link.l1 = "표식 따위는 집어치워. 우리는 앞으로 나아간다... 모두 잘 들어! 무장해라! 준비해! 경계 태세 유지해! 저 야만인들이 더러운 얼굴을 내밀면, 전부 죽여 버릴 거다!";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "백인 추장과 그의 부하들이 카퐁가들을 박살냈다, 타고파가 감탄하고 있다. 스페인 도시가 가까워. 폭포가 보이는 계곡이 있다. 타고파는 스페인인들에게 가지 않을 거다. 나는 폭포 근처에서 기다릴게.";
			link.l1 = "좋아. 앞으로!";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "우리가 돌아왔소, 백인 추장. 타고파가 약속한 대로 했소.";
			link.l1 = "고맙다, Tagofa. 잘했어.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "타고파는 가야 해. 하야미가 나를 기다리고 있어. 잘 있어라, 바다의 아들아.";
			link.l1 = "행운을 빌지, 셀바의 아들아. 네 아내에게 안부 전해 주게. 그리고 우리를 도와줘서 고맙네.";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "이봐! 넌 누구고, 뭐 하러 온 거야?";
			link.l1 = "메리다로 가서 네네 총독이든, 아니면 그 자리를 대신하는 사람이든 만나서 얘기 좀 해야겠어...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "우리는 메리다에 낯선 자를 들이지 않는다. 나가라!";
			link.l1 = "이봐, 우리는 이틀 동안 죽어라 노 저었고, 인디언 무리들과 싸웠어. 그냥 이렇게 떠날 생각 없어. 다시 말하지만, 네네 마을 우두머리랑 얘기하고 싶다! 그에게... 사업 제안이 있어, 맞아! 우리 모두 합의하면, 네네 마을은 무사할 거다.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "협박이라도 하겠다는 거냐, 라드론?";
			link.l1 = "어떻게 그걸 알아챘지? 아, 맞아, 내가 협박하고 있지. 우리가 여기 온 목적을 평화롭게 얻든 힘으로 빼앗든, 네 마을의 운명을 결정할 영광은 네게 있다네.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "너 같은 피투성이 해적은 메리다에 절대 들어올 수 없어!\n경보다! 적이 성문 앞에 있다!";
			link.l1 = "정말 말도 안 되는 나리로군...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "젠장할 도둑놈들! 우리한테 뭘 바라는 거야?! 여긴 작고 초라한 정착지야. 금도 은도 없어! 도대체 어떻게 우리를 알게 된 거지?";
			link.l1 = "오, 시치미 떼지 마십시오, 각하. 이미 온 세상이 당신의 오팔에 대한 소문으로 떠들썩합니다.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "그리고 너희는... 소문 때문에 이런 신을 모독하는 학살을 저질렀단 말이냐?! 아무도 살려두지 않았지! 짐승들 같으니... 분명히 알아둬라. 광맥은 여기서 멀리 떨어져 있다. 여기서는 얻을 게 아무것도 없다. 썩 꺼져라.";
			link.l1 = "네가 이 신 없는 학살을 시작했지. 민간인들이 네 군인들과 함께 싸웠어. 몇 개의 텅 빈 벽을 지키려고 이런 무의미한 영웅심이 나올 수 있다는 건 절대 믿지 않아.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "이 벽을 세우는 데 얼마나 많은 노력이 들어갔는지 아시오? 우리는 외부 인부를 고용하지 않았소—직접 벽돌 하나하나 쌓았지. 모든 주민이 다 참여했소. 나 역시, 이 두 손으로 직접 했소.";
			link.l1 = "참 감동적인 이야기로군... 그런데 가구는 어쩌지? 그것도 직접 만든 건가? 조각이 아주 훌륭한 의자네. 그리고 탁자도. 찬장도. 이거, 착색한 참나무인가? 아니면 흑단인가? '소박한 정착지'치고는 좀 지나치게 호화로운 거 아니야?";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "욕심이 네 정신을 흐리게 했군, 도둑놈.";
			link.l1 = "일을 복잡하게 만들 필요 없소, 총독 나리. 괜히 후회하게 될 거요.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "나를 고문할 생각이냐, 이 죽일 해적 놈아? 유감이지만, 나는 전능하신 하느님을 믿는다. 네가 너무 심하게 굴면 나는 순교자로 하늘로 올라갈 거다.";
			link.l1 = "흠...";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "내 친구야, 이래선 저자가 입을 열지 않을 거야. 내가 처리할게.";
			link.l1 = "오?";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "나는 저주받은 플랜테이션에서 그 잘난 스페인 놈들이 내게 뭘 했는지 다 기억하고 있지. 원한다면 보여주지, 나리. 그동안 재미있는 얘기도 몇 개 해줄게. 지루할 틈 없을 거야.";
			link.l1 = "근데 너무 흥분하면 어쩔 건데?";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "그 자는 예의를 차릴 생각이 없어. 저런 부류는 내가 잘 알지.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "(신뢰) (명예) (지도력) 오늘은 피를 충분히 봤다, 장. 이건 내가 직접 처리하지.";
				link.l1.go = "merida_head_dobro_1";
				Notification_Perk(true, "Trustworthy");
				Notification_Reputation(true, 50, "low");
				notification("Skill Check Passed", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) Notification_Reputation(false, 50, "low");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "해. 나는 끼어들 생각 없어. 그리고 구경도 안 할 거야.";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "내가 너한테 빚진 게 아니었으면 한마디 해줬을 텐데... 젠장. 가라. 이제 진짜 일이 시작이야.";
			link.l1 = "무리하지 마.";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "원하는 대로 해, 친구. 구경하는 것도 재미있겠군.";
			link.l1 = "너무 일찍 비웃지 마라.";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "네가 피 한 방울 흘리지 않고 이 일을 직접 처리하겠다고? 이 죽일 도둑놈아! 네가 무슨 말을 해도 돌이 하늘에서 뚝 떨어지진 않아!";
			link.l1 = "차라리 그들이 나타나는 게 낫겠소, 총독 나리. 그렇지 않으면 우리는 도시를 완전히 불태우고 당신만 남기고 모두 죽일 거요. 나도 이런 방법은 싫지만, 내 목적을 위해 명예쯤은 희생할 각오가 되어 있소. 반면에 당신의 의무는 메리다의 민간인, 살아남은 병사들, 그리고 일꾼들을 지키는 것이오. 아니면 그들의 고통을 대가로 '순교자로 승천'하는 걸 택하겠소? 내게는 그다지 신성하게 들리지 않는데.";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "젠장...\n저기... 상자 안에 있어. 제발 마을 사람들만은 살려줘!";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "(살금살금) 상자에 다 들어 있나?";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("Skill Check Passed", SKILL_Sneak);
			}
			else
			{
				link.l1 = "나는 약속을 지키지. 안녕히 계시오, 총독.";
				link.l1.go = "merida_head_dobro_5";
				notification("Skill Check Failed (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "지옥에나 떨어져라!\n이 상자에도 이중 바닥이 있군. 전부 챙겨!!";
			link.l1 = "...";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "매끄럽군, 왕자. 너를 얕봐서 미안하다.";
			link.l1 = "만족했어?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "매끄럽군, 왕자.";
			link.l1 = "만족하나?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "더 많아. 하지만... 직접 보게 될 거야. 너 먼저 가, 나는 좀 더 뒤져볼게.";
			link.l1 = "...";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "보석만 손에 넣으면 마을을 떠나겠다고 약속했잖아... 이제 보석도 가졌고 네 놈들의 라드로네스가 우리 집에 불까지 질렀어! 넌 거짓말쟁이에 악랄한 해적이야! 지옥불도 이만큼 뜨겁길 바란다, 이 악당아!!!";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", 착한 나리. 무슨 일로 여기 오셨소?";
			link.l1 = "나는 Tyrex 출신이다. 네 배를 Bridgetown까지 호위하라는 명령을 받았다. 준비됐나?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "드디어군! 그래, 내 선원들은 당장 출항할 준비가 되어 있어!";
			link.l1 = "훌륭하오. 돛을 준비하시오, 선장. 출항하세!";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "도와주셔서 감사합니다, 선장님! 선장님이 곁에 계셔서 저는 마치 요새 성벽 뒤에 있는 것처럼 안전하다고 느꼈습니다.";
			link.l1 = "하, 별말을 다 하네, 친구! 마커스가 다 쏜다. 행운을 빌어, 동료!";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "용감한 선장님께 인사드립니다! 제 소개를 하겠습니다 – 저는 토레로 호의 이그나시오 마르코로, 영국을 위해 일하는 사략선장입니다.";
			link.l1 = TimeGreeting()+", 친구. 선장 "+GetFullName(pchar)+" 대기 중입니다. 무엇을 도와드릴까요?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "오, 너를 알겠어! 나리 "+GetFullName(pchar)+"! 자네의 자금과 후원자들에 대한 소문이 제도 전역에 퍼지고 있더군. 내 제안이 자네에게 꽤 흥미로울 거라 믿네.";
			link.l1 = "무슨 제안?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "술이나 한잔하러 선술집에 가자. 내가 전부 말해줄게. 이건 길거리에서 할 얘기가 아니야.";
			link.l1 = "좋아... 가자!";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "한잔 할까, 선장?";
			link.l1 = "물론이지!";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "헤, 여기선 럼에 물을 정말 안 타는구만...";
			link.l1 = "그리고 손님들에게 썩은 생선 내놓지 마, 알겠지. 그래서 무슨 일이야?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "그대의 솔직함이 마음에 드오, 나리. 자, 묻겠소. 영국과 네덜란드 사이의 무역 전쟁에 대해 알고 있소?";
			link.l1 = "그래, 나도 참가했지. 즐거운 경험이었어.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "그렇다면 설명할 필요 없겠군. 나는 영국의 사략선으로서 그들 편에 서서 이 전쟁을 치르고 있지. 너는 대부분 자유 계약자라 어느 편과 싸우든 상관없겠지...";
			link.l1 = "거의 다 왔지. 하지만 나는 프랑스를 넘지 않아, 미안하다.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "물론이지, 선장! 그럼 바로 본론으로 들어가지. 쿠라사오와 트리니다드 사이에 작은 유인도가 하나 있는데, 지도에는 안 나와 있어... 아주 최근, 정말 얼마 전부터 네덜란드 놈들이 그 섬을 보급과 수리를 위한 임시 정박지로 쓰기 시작했지. 자기들만 그 섬을 안다고 생각하는 것 같더군. 천만에. 허허\n며칠 전에 은화 수송대가... 폭풍을 맞았고, 지금 네덜란드 놈들이 그 섬에서 배를 수리하고 있어. 기함은 돛대까지 잃어서 수리에 시간이 좀 걸릴 거야. 네덜란드 놈들은 수리에 바쁘고, 선원들은 대부분 섬 곳곳에 흩어져 있지...";
			link.l1 = "그리고 갑자기 우리가 나타나서 상황을 구한다는 거야?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "맞아요, 선장님. 나 혼자서는 못하지만, 선장님과 함께라면 얘기가 완전히 달라지지. 위험을 감수하시겠소? 내 배도 훌륭하고, 선원들도 뛰어나며, 경험도 많소. 선장님의 실력도... 칭찬할 만하오.";
			link.l1 = "우리에게 시간이 얼마나 남았지?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "시간은 충분해, 허비하지 말고 바로 출항하자.";
			link.l1 = "그럼 탄약과 무기를 보급합시다, Ignacio Marco 선장. 그리고 출항하지요. 그 섬의 정확한 좌표는 무엇입니까?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12'40 북위, 64'11 서경. 알겠어?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "하! 데자뷔군... 알겠어.";
			else link.l1 = "알겠어.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "'토레로'로 간다. 기다릴게, 선장!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "죽을 뻔한 싸움이었지, 선장? 이제 즐거운 부분이 남았군. 몫을 나누자. 절반은 나랑 내 놈들이 가져가겠다.";
			link.l1 = "좋아, 해보자...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "선장님, 무슨 일이십니까? 우리 은화는 어디 있습니까? 혹시 우리가 잡은 배를 침몰시킨 겁니까?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "흠...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "어쩌다 보니 은은 허비됐지만, 적목은 좀 챙겼네. 나눠 가지자.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "흠... 이거 참 별로군. 훨씬 더 많을 줄 알았는데.";
				link.l1 = "우리에겐 가진 것밖에 없어.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "나쁘지 않네, 나쁘지 않아. 하지만 더 많을 줄 알았는데.";
				link.l1 = "우린 가진 게 이것뿐이야.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "잘했소, 나리. 훌륭한 전리품이군...";
			link.l1 = "이 점에 대해서는 당신 말이 맞소, 선장.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "머리에 큰 문제라도 있는 것 같군. 우리 간다! 얘들아!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "적어도 뭔가 건졌잖아... 얘들아! 가자!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "뭐, 그럼 각자 길을 가자.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "뭐, 괜찮네. 이제 각자 갈 길 가자고. 결국 성공했으니, 헤헷!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "아주 이득이 큰 만남이었소. 아마 이번이 마지막으로 함께 거래하는 일은 아닐 것이오, 선장!";
			link.l1 = "더 뚱뚱한 상인들 찾으면 불러, 헤헤!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "이게 우연은 아니겠지, 선장?";
			link.l1 = "그걸 못 봤다면 영리하다고 할 수 없지. 이 판을 짜 준 값도 받아야겠고. 내가 무슨 말 하는지 알잖아. 그리고 내 친구 장 피카르를 함정에 빠뜨린 것도 빚졌지. 네 계략 때문에 그는 플랜테이션에 팔려갔어... 이그나시오도 놓쳤고. 널 교수형에 처할 거다. 하지만 네 벌을 좀 덜어줄 수도 있어...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "나는 심지어 궁금하군 – 내가 어떻게 해야 네가 나를 불쌍하게 여길까?";
			link.l1 = "정보가 필요하다. 널 내 화물창에 가둬두고, 아바나에서 네 일거리에 대해 얘기해보자...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" 이럴 줄은 몰랐어! 꿈도 꾸지 마라. 바르바존은 내가 배신한 걸 금방 알 거다. 네가 그가 배신자들에게 뭘 하는지 모르는 게 나을 거야. 난 직접 봤으니까.";
			link.l1 = "그래서, 교수형이 더 나은 선택이란 말이냐?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "차라리 전투에서 죽겠어!";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "선장님! 선장님! 빨리요! 스페인 군함대가 우리를 쫓아오고 있어요!";
			link.l1 = RandSwear()+"이럴 줄 알았지... 피카르도 똑같은 일을 겪었어. 밖에 놈들이 얼마나 많았는지 봤어?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "예, 선장님. 배가 세 척입니다. 기함은 갤리온인데, 내가 본 것 중 가장 크고 빠르게 다가오고 있습니다. 나머지 두 척은 코르벳과 제벡입니다.";
			link.l1 = "모두 배에 올라. 아직 도망칠 수 있을지도 몰라.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "하야! 젠장할 얄라나우이 놈, 우리 숲에 들어오다니! 죽여라! 하야!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "이봐! 여기서 뭐 하는 거야, 이 자식아? 아, 남의 물건 훔치고 있었군? 이제 큰일 났다!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "이봐! 모두 거기 멈춰! 안 그러면 산탄포로 다 쓸어버릴 거야! "+RandSwear()+"";
			link.l1 = "우린 지금 아무 데도 안 가. 하지만 잘 들어, 이 친구야 – 네가 한 번에 우리 전부를 죽일 수는 없어. 네가 장전하는 동안 우리 중 몇 놈은 널 갈기갈기 찢어놓을 거야. 지금 당장 얘기하는 게 좋을 거다.";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "여기 책임자인가? 대답해!";
			link.l1 = "나는 선장이야 "+GetFullName(pchar)+". 그리고 여기 레드 울프가 없을 때는 네가 그의 부선장이지, 맞나?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "여기서 뭐 하고 있나, 선장 "+GetFullName(pchar)+"? 여긴 손님을 반기지 않아!";
			link.l1 = "네 이름이 뭐지? 누구랑 얘기하는지 알고 싶거든.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "이름은 로드가르 얀센이다.";
			link.l1 = "여러분, 지금 상황이 깜깜한 것 같군. 이제 더 이상 선장도 없고, 너희 코르벳도 사라졌지. '프레이야'는 히스파니올라 근처에서 스페인 놈들에게 완전히 박살났어. 선원들도 한 명도 남김없이 전부 죽었지...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" 울프릭... 아아악-으아아!!! ... 하지만 네가 진실을 말하고 있다는 걸 내가 어떻게 알 수 있지?";
			link.l1 = "네 전 선장의 항해일지를 내가 가지고 있다! 프레이야의 난파선에서 몇 가지 물건도 챙겼지. 그 항해일지 덕분에 이 섬과 네... 보물까지 찾게 됐다.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "헤! 아직 내 질문에 답하지 않았잖아. 왜 이 낯선 땅에 온 거지?";
			link.l1 = "거짓말할 생각 없어, 친구. 레드 울프가 꽤 큰 재산을 가졌었다고들 하더군. 그 보물이 그의 배에서는 발견되지 않았으니, 내가 찾으러 온 거야. 난 그 보물이 이제 좋은 사람들 손에 들어가야 한다고 생각해. 울프릭한테는 이제 아무 소용도 없잖아.";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "하! 이봐, 실망하게 될 거야. 나도, 선원 누구도 울프의 보물을 본 적 없어. 그에게 물어보는 건 너무 위험했거든.";
			link.l1 = "그럼 네 마을에서 그들을 찾아봐야겠군. 총을 내려놓을래, 아니면 내가 마을을 습격해야겠나? 너에겐 기회가 없어, 로드가. 필요하다면 더 많은 총과 사람들을 데려오겠다.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "우리가 죽기 전에 너희 놈들 중 꽤 많이 지옥으로 데려가 주마! 어쩌면 너도 같이 갈지 몰라!";
			link.l1 = "확실하냐? 너희에겐 선장도 없고, 배도 없고, 구하러 올 사람도 없다. 내가 그냥 떠나버려도, 너희는 곧 굶어 죽게 될 거다!";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "흠... 뭐 좋은 생각이라도 있나?";
			link.l1 = "그래, 맞아. 총에서 떨어지고 네 부하들도 얌전히 시켜. 너희에게 해칠 생각은 없다고 맹세한다. 원한다면 내 선원으로 들어와도 되고, 아니면 우리가 너희를 문명 세계로 데려가 주겠다.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "네 놈 부하들 앞에서, 크게 분명히 맹세해라!";
			link.l1 = "맹세하네! 내 말은 믿으시오: 당신과 당신의 부하들은 해를 입지 않을 것이오.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "약속을 지켜 주시길 바랍니다, 선장님.";
			link.l1 = "나는 항상 그렇게 하지. 너희 중에 몇이나 남았지?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "우리 셋만 남았어. 나머지는 정글에서 너희를 공격하다가 죽었지. 내가 말렸는데도, 듣질 않더군...";
			link.l1 = "그렇군...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "식량이 바닥나기 시작했지. 우리는 앵무새 사냥을 시작했어. '프레이야'는 너무 오랫동안 돌아오지 않았지. 의심이 있었는데, 결국 사실로 드러났어.";
			link.l1 = "신께 감사하군, 내가 보물 사냥을 하기로 결심해서 말이야. 어디에 숨겨놨다고 생각해?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "이미 말했잖아: 아무도 그걸 본 적 없어. 울프릭은 자기 몫을 아주 신중히 다뤘고, 절대 허투루 쓰지 않았지. 우리한텐 공정했어. 하지만 그의 은닉처를 찾으려던 자들은 모두 사라졌어. 원한다면 마을을 마음껏 뒤져봐.";
			link.l1 = "그게 내 계획이야. 레드 울프의 집은 어디지?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "여기 있는 유일한 2층 건물이야.";
			link.l1 = "좋아. 그런데, 자네 직업이 뭐지?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = GetIslandNameByID("IslaMona");
            dialog.text = "나는 목수고, 이 둘은 내 조수들이야. 예전에는 '프레이야'를 수리하고 켈링 작업도 했지. 네 선원으로 쓸모가 있을 거야.";
			link.l1 = "알겠다. 좋아, 너도 끼워줄게. 자세한 얘기는 나중에 하자. 입구에 있는 총을 챙겨라. 그리고 로드가, 내가 은닉처를 찾는 동안 마을에서 나가지 마.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "명령을 내리시겠습니까, 선장님?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "그래. 네 선장의 보물은 이미 찾았지. 그 자가 잘 숨겨 놨지만, 내가 한 수 위였거든!";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason Исла Мона -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "Rodgar, 어떻게 생각해? 이 기지로 우리가 더 할 수 있는 일이 있을까?";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "Rodgar, 도구를 가져왔어. 이미 네게 전달됐어야 해.";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "환영합니다! 여기는 카디스에서 온, 작지만 매우 근면한 공동체의 지도자 로드리고 히메네스입니다. 히메네스 나리께서 기꺼이 우리 땅에 잠시 머물며 건설을 도와주시기로 하셨습니다.";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "Rodgar, 잘 지내나? 나한테 해줄 만한 좋은 조언 있나?";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "Rodgar, 부탁이 있어.";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && PCharDublonsTotal() >=600)
			{
				link.l1 = "너 위해 두블룬을 가져왔어, 근데 당장 술에 다 써버리진 마라.";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "Rodgar, 창고를 확인해 봐. 약품이랑 식량 가져왔어.";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "안녕, Rodgar. 새 정착지에서는 어떻게 지내?";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
			{
				link.l2 = "Rodgar, 내 배를 수리해야 해. 너랑 네 부하들 준비됐냐?";
				link.l2.go = "repair";
			}
			link.l3 = "로드가, 내 배 중 하나를 여기 두고 싶어.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "Rodgar, 내 배 중 하나를 다시 가져가고 싶어.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "이봐, 내가 창고로 쓸 만한 빈 건물 있나?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, 창고를 보고 싶어.";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "Rodgar, 나는 팀 일부를 섬에 남겨두고 싶어.";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "로드가, 내 선원들을 데리고 다시 바다로 나가고 싶어.";
				link.l7.go = "crew_3";
			}// <-- Исла Мона
			link.l99 = "아직 아무것도 없어...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "축하합니다, 선장님. 이제 어떻게 하시겠습니까? 떠날까요?";
			link.l1 = "여기 오래 있었나?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "너무 오래됐지. 울프릭이 나를 여기 책임자로 세운 지 벌써 1년이야.";
			link.l1 = "나는 이 비밀 기지가 너무 가치 있어서 그냥 버릴 수 없다고 결정했다. 이제 이 마을은 내 것이다. 원한다면 너와 네 부하들을 여기 남겨둘 수 있지. 럼주, 식량, 약품 전부 너희 거다.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "그거 참 좋겠네요, 선장님. 이 해변, 이 섬에서의 삶에 익숙해졌거든요.";
			link.l1 = "훌륭하군. 그런데, 그 섬 이름이 뭐지?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "이슬라 모나... 언젠가는 이곳에 집과 건물들을 더 지을지도 모르지... 하지만 그건 나중 일이다. 지금은 네 역할은 그대로지만, 이제 새로운 선장 밑에서 일하게 될 거다.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "좋아. 몸조심하시오, 선장. 그리고 우리에게 식량 보급하는 것 잊지 마시오.";
			link.l1 = "알겠어, Rodgar. 행운을 빌어. 난 La Vega로 항해해야겠어.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//------------------------------------------------------------ Исла Мона ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", not accounting for your woman";
            dialog.text = "말하기 어렵군요, 선장. 고(故) 울프릭은 여기 두어 명 남짓만 두고 떠났었죠. 지금은 우리 셋밖에 없습니다."+sTemp+". 우리가 할 수 있는 게 많지 않다.";
			link.l1 = "여기에 더 많은 사람들이 산다면, 이곳을 제대로 된 정착지로 만들 수 있다는 말이오?";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "섬이 작아서 식민지를 세울 수는 없지만, 정착지는 충분히 만들 수 있어! 여기서 물고기도 잡고, 새나 염소도 사냥하고, 과일도 딸 수 있지. 우리끼리 살아가는 데는 문제없지만, 부자가 되긴 힘들 거야.\n그런데 한 가지 잘 이해가 안 가, 선장. 대체 이걸 왜 필요로 하는 거야?";
			link.l1 = "여기가 내 집이고 내 땅이야, 그리고 내 사람들이지. 내가 이들을 돌보지 않는다면, 나는 대체 뭐가 되겠어?";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "나는 가치 있는 사업에 돈을 투자하고 싶어.";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "이 작은 섬은 이 지역의 중심에 있다. 여기를 완전하고 비밀스러운 군사 기지로 만드는 것이 현명할 거야.";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "너 걱정돼, Rodgar. 너희 모두 지금 완전히 미쳐 버렸잖아.";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "넌 참 이상한 녀석이군. 뭐, 됐다. 적어도 할 일이 생기겠지...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//защита
		break;
		
		case "IslaMona_2_2":
            dialog.text = "넌 참 이상한 녀석이군. 뭐, 신경 쓸 일도 아니지. 적어도 할 일이 생기겠네...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//торговля
		break;
		
		case "IslaMona_2_3":
            dialog.text = "넌 참 이상한 녀석이군. 뭐, 신경 쓸 거 없지. 적어도 할 일은 생겼으니까...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//оружие
		break;
		
		case "IslaMona_2_4":
            dialog.text = "넌 참 이상한 놈이군. 뭐, 신경 쓰지 않겠다. 적어도 할 일이 생겼으니...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//авторитет
		break;
		
		case "IslaMona_3":
            dialog.text = "우선, 아주 특별한 인물들을 찾아야 하오. 이 외딴 황야로 이주해, 바깥세상과 완전히 단절된 채 수년간 여기서 살며 일할 수 있도록 설득할 수 있는 자들이지. 바로 그런 비범한 사람들을 찾아야 하오. 가능하다면 한 명 이상이면 좋겠지. 어쨌든, 아직은 선원들에게 여기 정착하라고 명령할 수도 없으니 말이오. 식민지 주민들도 이미 자리 잡은 집과 안정된 일자리를 버리고 오고 싶어하지 않을 것이오. 그리고 우리도 여기서 부랑자나 문제아들이 필요하지는 않소.\n게다가, 이 섬을 둘러싼 비밀 문제는 언제나 남을 것이오. 누구에게라도 말하면, 곧바로 사냥꾼들이 조사하러 들이닥칠 위험이 생기지.";
			link.l1 = "알겠어, 뭐 좋은 생각이라도 있어?";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "아니요, 선장님. 저는 여기서 너무 오래 지내서 문명 세계와 완전히 동떨어져 버렸습니다.";
			link.l1 = "좋아, 도움이 되네!";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "나는 사람 말고 나무랑 일하지. 그래서 아주 행복해, 하하! 그런데 사람 말고도 여기로 고급 대장장이랑 건축 도구 세트도 가져와야 해. 그런 건 옛 유럽에서만 만들어서 꽤 비쌀 거야. 큰 조선소 주인들한테 물어봐.";
			link.l1 = "모든 게 명확하군. 정리하자면, 이 기지를 더 크게 만들고 싶으면 정착민들과 도구를 더 데려와야 한다는 거지?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "맞아!";
			link.l1 = "뭐 할 수 있는지 알아볼게.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "예, 선장님! 최고급 장비라서 식민지 건설 준비 끝났습니다! 값이 좀 비쌌나요?";
			link.l1 = "한몫 깨졌는데, 그만한 값어치는 했어야지!";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "몇 해 전만 해도 아주 비싸다고 했을 거야. 하지만 지금은... 나도 잘 모르겠어.";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "이미 가진 걸로는 만족하지 못했지? 어쨌든, 앞으로 지출만 더 늘어날 거라는 걸 각오해. 정착민 문제는 해결했어?";
			link.l1 = "아니, Rodgar. 아직 그들을 어디서 찾아야 할지 모르겠어. 결국 이 바다에서 정착지를 세울 주권이 내게는 없으니까.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "이미 가진 것에 만족하지 못했지? 어쨌든, 앞으로 네 지출은 더 늘어날 테니 각오해라. 정착민 문제는 해결했냐?";
			link.l1 = "아니, Rodgar. 아직 그들을 어디서 찾아야 할지 모르겠어. 어쨌든, 이 바다에서 정착지를 세울 주권은 내게 없으니까.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "이 바다에선 매일 혼돈이 지배하지, 선장님. 사람들이 무슨 말을 하는지 잘 들어봐, 숨겨진 기회를 찾을 수도 있으니. 도구들은 내가 당분간 맡아둘게.";
			link.l1 = "알겠어, 그런 정보는 내가 주의해서 살펴볼게.";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("They say some criminals have been cast out to one of the uninhabited islands! It seems they're such fierce monsters that even the executioner and the holy fathers wouldn't want to deal with them! But why do they always bring such people to us?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "스페인 놈들이라고? 농담하지 마시오, 선장. 난 자네가 르 프랑수아에서 빈둥거리는 놈들을 데려올 줄 알았지, 이런 자들은 아니었는데...";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "유럽에서 왔나? 헤헤, 딱 보면 알지. 걱정 마, 곧 익숙해질 거야.";
			link.l1 = "Jimenez, 당분간 내 집에 머물게. 지하실이 있어서 공간은 충분해. Rodgar, 도구도 가져왔고, 정착민들도 데려왔어. 이제 뭐하지?";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "내일 뵙겠습니다, 선장님. 이... 정착민들이 보물을 정리하고 나면 하루 뒤에 다시 이야기합시다.";
			link.l1 = "좋아, 내일 계속하자.";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "선장님, 그 스페인 놈에게 말씀해 보십시오. 그는 이미 자기 일에 완전히 몰두해 있습니다.";
			link.l1 = "알겠습니다, 제가 처리하겠습니다.";
			link.l1.go = "IslaMona_19";
			link.l2 = "무슨 문제라도 있나?";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "선장님, 여기서 몇 년 동안 동료들이랑 빈둥거렸습니다. 이제 스페인 놈들의 부산스러운 움직임이 신경을 거슬리게 하네요.";
			link.l1 = "충돌은 안 돼! 그리고 너랑 네 부하들은 저 여자들 쪽을 쳐다보는 것도 금지다! 적어도, 지금은 말이지... 일이 복잡해지면, 작은 배 타고 며칠 동안 낚시나 하고 와.";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "예, 알겠습니다, 나리!";
			link.l1 = "완벽해. 좋아, 내가 가서 그 녀석이 뭘 하고 있는지 보고 올게.";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "이미 알고 있어, 선장. 스페인 놈이 우리더러 섬을 탐험하라고? 바위 위에서 지도 들고 멍청이들처럼 뛰어다니라는 거야?";
			link.l1 = "맞아, Rodgar.";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "600 더블룬이면 해주지.";
			link.l1 = "미쳤어? 여기 토종 거미나 독사한테 물린 거야? 사람이 없는 섬에서 금 상자를 가지고 뭘 하려고? 묻어둘 거야?";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "가자고요, 선장. 언젠가 우린 이곳을 떠날 텐데, 돈 한 푼 없이 넓은 세상에서 누가 우리를 필요로 하겠어요? 물론, 비상금 좀 숨겨둔 게 있긴 하지만 턱없이 부족하죠. 울프릭은 지난번 일로 나랑 동료들에게 진 빚도 아직 안 갚았고요.\n몇 달씩 해변에서 빈둥거리다가 반년에 한 번 함대 정비하는 건 한 가지 일이지만, 매일 땅에서 저주받은 버커니어처럼 뼈 빠지게 일하는 건 완전히 다른 얘기죠! 그건 진짜 일이고, 일엔 대가가 따르죠. 선장, 당신은 선원들 월급 제대로 주고 있죠?";
			link.l1 = "그럴듯하게 들리네. 600두블론 가져다줄게. 선불로 달라고 하진 않겠지?";
			link.l1.go = "IslaMona_23";
			link.l2 = "다른 제안을 하나 하지. 너는 바다에서 배 따개비나 긁는 게 아니라, 육지에서 일하는 거야. 지금 우리에겐 그런 일이 정말 절실히 필요해.";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "선장님, 지금 당장 시작할 준비가 되어 있습니다만, 제 부하들은 손에 두블론을 쥐어야 훨씬 더 열심히 일할 겁니다. 이 섬에서 미지의 땅 한 조각도 남기지 않겠다고 약속드리겠습니다.";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "좋아. 여기 네 금화다. 바로 술에 다 써버리지만 마라.";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "좋아, 네가 원하는 두블룬을 가져다주지.";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You gave away 600 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "하하! 그 말이 맞아요, 선장님! 아, 그리고 깜빡할 뻔했네요. 이제 여기 사는 사람이 제법 많아졌는데, 먹을 게 필요하죠. 저 여자들 봤어요? 땅에서 살아남는 데 익숙하지 않아서 아무 도움도 안 될 거예요.";
			link.l1 = "설마 내가 너 도와주려고 바커니어들을 더 찾아야 한다는 말은 아니겠지.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
			AddQuestRecord("IslaMona", "8");
            dialog.text = "알겠어요, 선장님! 육지에서 일할 준비 다 됐습니다! 아, 그리고 한 가지 더, 깜빡할 뻔했네요.\n지금 여기 사는 사람들이 꽤 많아졌는데, 먹을 게 필요하답니다. 저 여자분들 봤어요? 땅에서 살아남는 데 익숙하지 않아서 아무 도움도 안 될 거예요.";
			link.l1 = "설마 너 도와주려고 내가 버커니어들까지 찾아다녀야 하는 거야...";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "아니, 우리가 왜 그래야 하지? 우리는 그들 중 가장 유능한 자들을 훈련시키고, 생계를 준비시킬 거야. 하지만 그 멋진 순간이 올 때까지는 네가 우리에게 식량을 제공해야 해. 선상 식량 몇 천 세트면 충분해. 그리고 미래를 위해 약품 백 푼도 필요하지. 이 모든 걸 배에서 내려서 섬에 있는 우리 창고에 옮겨놔.";
			link.l1 = "알겠소. 정찰 임무에 시간이 얼마나 필요하오?";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "이틀이나 사흘이면 끝나겠어, 이미 흥미로운 것들을 좀 찾았거든.";
			link.l1 = "좋아!";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "우리가 끝내자마자 곧장 저 웃고 있는 스페인 놈한테 가. 그 미친놈이 우리 작업에서 뭔가 결론을 내릴 필요가 있거든.";
			link.l1 = "보아하니 벌써 거의 친구가 된 것 같군. 그럼 사흘 뒤에 그를 찾아가 보지. 자, 일에 건배하자. 우리 모두에게 행운이 있기를!";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "이런 젠장! 고맙소, 선장님. 이제 아가씨들을 이 거친 삶에 대비시킬 시간이 생겼군.";
			link.l1 = "해적이 되게만은 하지 마시오! 고맙소, Rodgar";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "선장님! 여기서 사는 게 점점 불편해지기 시작했습니다.";
			link.l1 = "왜 그러지, Rodgar? 가난과 몰락의 매력이 그리운 거야?";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "그렇다고 할 수 있지. 이제 문명이라는 게 여기까지 밀려오고 있어. 나 같은 사람은 그 안에 설 자리가 없어.";
			link.l1 = "자보와 지팡이나 하나 사. 그러면 딱 어울릴 거야.";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "차라리 네 스페인 놈한테 가서 정찰 결과를 얘기해 보자. 미친 생각이 하나 더 있거든...";
			link.l1 = "방금 그와 얘기했어! 좋아, 가자, Rodgar.";
			link.l1.go = "IslaMona_37";
			link.l2 = "그와 함께 일하는 거, 어때?";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "아주 교양 있고 근면한 사람들이야! 그리고 히메네스는 정말 장인이지. 옛날 같았으면 이런 사람들은 금도 많이 받았을 거야. 게다가 그쪽 여자들도 참 예쁘더라...";
			link.l1 = "나는 그런 소리 안 듣겠다, Rodgar! 우리 주인한테 가서 직접 말하자";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "일 못 하면 팔아버리자고. 하지만 여자애들은 남겨둬, 하하! 주인한테 가 보자... ";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "진심이세요, 선장님? 그냥 농담이었어요, 가요...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "당신이 저를 지지해줄 줄 알았어요, 선장님! 가요...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "저 사람 안 웃고 있어요, 선장님...";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "그것도 말이야, 선장. 그건 나중에 얘기하자...";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "저 신사분 말이 맞소, 선장. 우리 중 누구도 정글에서 허리 부러지게 일하진 않을 거요. 일이 더럽긴 해도, 이곳에서 해적 소굴 말고 다른 걸 만들 방법은 없소.";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "선장님, 공장을 지으면 노예들에게 보호가 필요할 겁니다. 내 부하들이 그걸 맡겠소. 그중 한 녀석은 천둥의 토르처럼 총을 쏘지. 사냥용 조준경만큼 일에 동기를 부여하는 것도 없지요. 총 한 자루는 이미 있으니, 이제 두 번째가 필요하오. 아무 머스킷이나 상관없소.";
			link.l1 = "";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "그리고 내 부하들도 똑같은 양의 금화와 좋은 럼주 한 다스가 더 필요해.";
			link.l1 = "한 번에 얼마나 많은 목재를 제공할 수 있지? 그리고 금은 왜 필요한 거야?";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "음, 우선 한가로움 없는 삶은 의미가 없지. 곧 경건한, 헤헤, 카톨릭 신자들도 미쳐버릴 거야. 그리고 둘째로, 섬에 선술집이 있다면 선원 일부를 여기 대기시킬 수도 있지. 알겠지, 사람들을 1년 내내 해변 오두막에서 야만인처럼 공짜로 살게 설득하는 건 꽤 힘든 일이야. 하지만 근처에 선술집, 따뜻한 음식, 음악, 오락거리가 있는 정착지가 있다면... 선원이 육지에서 바라는 게 또 뭐가 있겠어?";
			link.l1 = "창녀들?";
			link.l1.go = "IslaMona_49";
			link.l2 = "술 한잔 할래?";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "맞아, 하지만 문제는 하나씩 해결하자. 먼저 네 집부터 다시 지을 거야...";
			link.l1 = "...";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "그는 그런 생각조차 안 했어, 선장.";
			link.l1 = "고맙네, Rodgar. 이제 이 작은 만에서 더 많은 배를 정비할 수 있게 된 거지, 맞나?";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "안녕하십니까, 선장님! 일에 대해 상의하러 오셨습니까?";
			link.l1 = "아니, 전혀 아니야. 그냥 네 북쪽 사람다운 얼굴이 그리웠을 뿐이야.";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "걸을까? 네 공장을 보여줄게.";
			link.l1 = "앞장서라.";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "히-잇! 선장, 우리 축하하고 있어!";
			link.l1 = "로드가! 로드리고! 젠장!";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "왜 그러십니까, 선장님? 벽 색깔이 마음에 안 드십니까?";
			link.l1 = "이제야 너희 둘이 같은 이름을 가졌다는 걸 알았구나! 하하하! 스페인 놈이랑 해적 놈이, 같은 이름으로 버려진 섬에 선술집을 짓고, 인디언 신들이 모두를 잡아먹고 해 뜨면 세상이 끝날 것처럼 같이 술을 마시고 있네! 하하! 나도 같이 할게!\n";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "하하하! 정말 그렇지! 건배!";
			link.l1 = "건배!";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "술 한잔 할래, 선장?";
			link.l1 = "너 선술집 주인이 되려고 하는 거야, Rodgar?";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "일시적으로야! 특히 스페인 놈들은 해적이 술집을 운영하는 걸 아주 신기하게 여기지, 그들에게는 진짜 이국적이고 모험적인 일이거든. 그래도 전반적으로 여기 분위기는 괜찮아. 만약 이 정착지에 네 선원 중 일부를 예비로 남겨두고 싶으면 나한테 말만 해. 내가 알아서 처리해 줄게.";
			link.l1 = "그런데 그들은 어디에서 살게 될까?";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "간단해 - 해변에 오두막 몇 채 지으면 돼. 그러면 놈들이 선술집에서 해안까지 뛰어다니게 될 거야. 참고로, 이 섬은 3백 명 이상은 수용 못 하니까 앞으로 명심해 둬. 가끔 우리가 럼주랑 와인 좀 가져오라고 할 테니, 선장님이 미리 창고에 물건을 쌓아두면 좋겠어.";
			link.l1 = "명심할게. 자, 동무. 스페인 놈들 좀 즐겁게 해주고 쉬어. 그런데 제발, 마을 전체가 불타버릴 만큼 마시진 마라 - 그런 꼴은 도저히 못 보겠으니까!";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // можно оставлять матросов
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
			// belamour обнулим матросов-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // приведение к 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "선장님! 이렇게 만나서 정말 반갑습니다! 프레이야께 감사해야겠네요, 딱 맞춰 오셨으니!";
			link.l1 = "그래, 또 한바탕 엉망진창에 휘말렸군. 이봐, Rodrigo!";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "사상자는 없었소. 살아남은 스페인 놈들이 먼저 우리에게 와서, 더 많은 불청객을 만날 가능성이 있다고 알렸소. 우리는 그 지역에 있던 식량과 장비를 거의 모두 정착지로 옮기는 데 성공했지. 노예들 문제는 물론 그리 잘 풀리진 않았소.";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "만약 저놈들이 우리를 밖으로 끌어내서 정면 공격을 한다면 어떻게 하지?";
			link.l1 = "그럼 총 없이 움직이는 거다. 마치 행진하듯이 다 같이 문까지 가서 뒤에서 한 방 먹이는 거지. 너는 문을 지키면서 지원해 줘. 그게 다야, 우리 모두 행운을 빌자!";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // встреча с французами
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//запретить драться
		break;
		
		case "IslaMona_70":
            dialog.text = "만세, 선장님!";
			link.l1 = "동의해! 정말 대단했어, 나도 그냥 드러눕고 싶더라. 이봐, 거기다 뭘 넣은 거야?";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "두 번 장전하시오, 선장님. 한 방이면 놈들이 더 이상 싸울 생각 못 하게 될 거요!";
			link.l1 = "그렇게 조심스럽게 다루다가 총이 터질까 봐 걱정되지 않았어?";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "울프릭이 남긴 특별한 부적이 있어. 우리 고향 덴마크에서 온 기념품이지. 모두 선장과 함께 선술집에 갈까? 오늘 하루 다들 지쳐 있잖아.";
			link.l1 = "그래, 그거 좋지. 카드나 한 판 하자 – 네가 가진 기적의 부적을 걸고 내기하자.";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "하하, 오늘처럼 신들린 연주를 들으니, 선장님, 나도 그 선택을 진지하게 생각해 볼지도 모르겠소!";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "선장님, 들으셨습니까? 아직도 귀가 울리네요. 저 애처로운 목소리는 누구죠?";
			link.l1 = "그건 말이지, Rodgar, 아직 끝나지 않은 일이야. 저 자를 공장으로 데려가서 쇠사슬로 묶어 두고, 추가 지시를 기다려.";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "알겠소, 선장님!";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "선장님, 죄수 문제를 해결하러 오셨습니까? 여기서 계속 감시만 하느라 지쳤습니다.";
			link.l1 = "우린 저 놈을 죽여야 해. 위험이 너무 크니까, 달리 방법이 없어. 그렇지 않으면 프랑스 식민지엔 얼굴도 못 들이밀겠지.";
			link.l1.go = "IslaMona_79";
			link.l2 = "그를 그냥 보낼 수는 없어. 그렇지 않으면 프랑스 식민지에 얼굴도 못 들고 다닐 테니까. 저놈을 족쇄에 채워서 공장에서 일하게 해. 죽이는 것보단 낫지.";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "알겠어! 빨리 끝내자. 가시죠, 선장님. 내일 봐요.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "이런 젠장. 너 정말 악랄한 천재구나. 네 적이 되고 싶진 않다. 자, 그럼 먼저 그에게 설명 좀 해야겠군. 가보시죠, 선장님. 내일 봅시다.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;
		
		case "IslaMona_82":
            dialog.text = "정말 학살이었군! 대포를 쏘지 못한 건 아쉽지만, 놈들이 네 매복에 그대로 뛰어들었지 – 정말 볼만한 광경이었어!";
			link.l1 = "그래, 이 땅에 피를 많이 흘렸지. 하지만 이 세상에서 보금자리를 만들려면 다른 방법이 없는 것 같아.";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "너무 신경 쓰지 마시오, 선장님. 운명이 그들을 이슬라 모나로 데려온 것이오. 그리고 한마디 하자면, 운명이라는 게 정말 고약한 년이기도 하다니까!";
			link.l1 = "운명인가, 아니면 그 섬인가?";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "둘 다 제 역할을 했지.";
			link.l1 = "하하! 둘 다 멋지군! 좋아, 용감한 바이킹. 전리품을 챙기고 이 시체들을 치워라. 품위 있게 묻어주자. 어차피 우리 동료들이니까...";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "네, 선장님. 맞아요! 로드리고가 너무 멋지게 말해서 눈물이 다 났다니까요. 성직자들이 왜 저 자식 엉덩이를 장대에 꽂으려는지 이제 알겠어요!";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "로드리고, 내가 바로 저기 침실에서 우리 주교님과 딱 마주쳤지... 그리고 말인데, 산티아고에서 이곳만큼 훌륭한 곳은 없어!";
			link.l1 = "성직자들도 좋아한다면 여기만한 곳이 없지.";
			link.l1.go = "IslaMona_89";
		break
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "그래, 그 악당이자 이단자 로드리고를 진짜 해적으로 만들어 놨지.";
			link.l1 = "그런데 말이야, 로드가르. 왜 스페인 해적은 이렇게 적은 거지?";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = "왜 이렇게 적으냐고? 아, 해적 선장들 말이지? 많지, 물론 많아. 다만 대부분 세비야의 카사 데 콘트라타시온 밑에서 활동하지. 군사 정보기관 같은 건데, 이상하게도 무역소라고 부르더군...";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "그래, 왜 그놈들에게 메시지라도 보내서 불러들이지 않겠어. 뭐, 다들 사략 면허도 있고, 이상주의자들이지. 자기들끼리는 잘 안 털어, 습격이 실패했을 때만 그렇지, 하하! 푸에르토 프린시페에만 들렀다 가고, 목사랑은 맨날 부딪혀.\n요즘은 한 놈이 두드러지더라... 디에고 데 몬토야. 내가 마지막으로 울프릭이랑 출정 나갔을 때, 그 녀석 모험담을 많이 들었지. 너도, 선장, 그 녀석이랑 닮은 구석이 있어. 동시에 아주 다르기도 하고... 에이, 내가 뭔 소릴 하는 거야? 한 잔 더 하고 카드나 한 판 하자.";
			link.l1 = "너 돈 없잖아. 설마 두블룬으로 도박하려는 건 아니지?";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "우리는 각자 1페소씩 걸었어. 스무 점까지 할까? 히메네스, 너도 할래?";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "놀아볼까, 선장?";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "시작해!";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "나도 패스할게, Rodgar. 페소가 있든 없든, 사람들은 이렇게 배를 잃곤 해. 섬이랑 같이 말이지. 너는 여기서 잘 놀아, 나는 좀 더 둘러볼 테니까.";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // игра в карты
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // ставка
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // выход из-за стола
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "패! 그래, 그래, 이제 너랑은 더 이상 안 놀아! 분명히 너, 속였지, 선장! 그리고 이렇게 사기꾼을 그냥 보내주는 건 옳지 않지!";
				link.l1 = "듣고 있어, Rodgar.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "내가 이겼어, 선장. 하지만 그냥 빈손으로 보내줄 순 없지, 하하!";
					link.l1 = "좋아, 이 악당아. 이게 내게 교훈이 되겠군...";
				}
				else
				{
					dialog.text = "내가 이겼어, 선장. 하지만 그냥 빈손으로 보내줄 순 없지, 하하!";
					link.l1 = "좋아, 이 악당아. 이번 일은 나한테 교훈이 되겠지...";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "아, 이봐! 너 덕분에 나랑 내 선원들은 비좁은 선실, 썩은 물, 그리고 머리에 파편이 박힐 위험에서 벗어나 진짜 인생을 살 기회를 얻었어. 자, 여기. 이 부적은 먼 덴마크에서 울프릭이 가져온 건데, 나한테 넘겨주면서... 흠, 자기 지하실을 너무 뒤지지 말라고 했지. 이제 난 더 이상 필요 없어. 하지만 너한텐, 아마 꽤 쓸모가 있을 거야.";
			link.l1 = "고맙네, Rodgar. 정말 쓸모 있는 물건이군. 게다가 아름답기까지 하네...";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "가지고 있어, 로드가. 네가 없었다면 이곳은 존재하지도 않았을 거야. 이걸 네 고향을 떠올리게 해주는 기념으로 삼아.";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("You received 'Thor's Hammer'");
			PlaySound("interface\important_item.wav");
            dialog.text = "마음에 드셨다니 기쁩니다, 선장님. 한 잔 더 하시겠습니까?";
			link.l1 = "너희들은 여기서 쉬고 있어, 내가 한 번 더 둘러보고 올게.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "원하시는 대로! 그럼 이번엔 행운의 여신에게 한 잔 올리지, 하하! 한 잔 더 할까?";
			link.l1 = "너희들은 여기 있어, 내가 한 번 더 둘러보고 올게.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "좋소, 선장. 스페인 놈과의 일도 정리됐고, 우리끼리 축하도 했으니, 두통도 좀 가셨군. 인생 참 좋구먼!";
			link.l1 = "무슨 일 하고 있어, Rodgar?";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "I'll get along with the woman. ";
			dialog.text = "평소처럼 사냥이나 하고, 내... 아니, 우리 선술집도 지켜보고, 플랜테이션에서 노예들 걷어차고 있지. 완벽한 은퇴 생활이야.";
			link.l1 = "너는 나보다 겨우 다섯 살 많을 뿐이야, 로드가. 그리고 너는 어때, 로드리고? 잘 지내?";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "물론이지, 선장님! 우리에게 필요한 건 판자랑 돛천뿐이오. 상륙지로 가서 선원들에게 자재를 준비하라고 명령하시오.";
				link.l1 = "가는 중이다. 빨리 해.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "물론입니다, 선장님. 하지만 제가 보기엔 지금은 선박 수리가 필요 없어 보입니다.";
				link.l1 = "방금 물어봤어...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "가능합니다, 선장님. 하지만 몇 가지 제한이 있습니다:\n이 섬에서 그럴 만한 곳은 두 군데뿐입니다. 그리고 각 배마다 장교 한 명만 남길 수 있고, 그 외에는 아무도 남길 수 없습니다. 여기에 선원들을 머물게 할 자원이 아직 부족합니다. 마지막으로, 1등급 함선을 둘 공간은 없습니다.";
			link.l1 = "알겠어. 여기서 배를 떠날 준비가 됐어.";
			link.l1.go = "shipstock";
			link.l2 = "좋아, 내가 그녀를 준비시킬게.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "선장님, 이미 선장님의 배 세 척이 부두에 정박해 있습니다. 더 이상 자리가 없습니다.";
					link.l1 = "맞아, 내가 깜빡했어.";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "선장님, 이미 일등급 함선이 부두에 정박해 있습니다. 더 이상 자리가 없습니다.";
						link.l1 = "맞아, 내가 깜빡했어.";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "선장님, 당신의 배 두 척이 이미 부두에 정박해 있습니다. 더 이상 자리가 없습니다.";
					link.l1 = "네 말이 맞아, 내가 깜빡했어.";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "선장님, 당신에겐 배가 한 척뿐입니다.";
				link.l1 = "흠... 술을 좀 줄여야겠군...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "여기 두고 갈 배가 어느 것이오?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "잠깐, 마음이 바뀌었어.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "어디 보자...";
			Link.l1 = "아주 좋군.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "잠깐, 마음이 바뀌었어.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "어디 보자...";
			Link.l1 = "아주 좋군.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "잠깐, 마음이 바뀌었어.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "어디 보자...";
			Link.l1 = "아주 좋군.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "잠깐, 마음이 바뀌었어.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "어디 보자...";
			Link.l1 = "아주 좋군.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "잠깐, 마음이 바뀌었어.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "선장님, 전에 말씀드렸듯이 우리 정박지는 일등급 함선 한 척만 수용할 수 있습니다. 그 배는 이곳에 두기엔 너무 큽니다.";
					Link.l1 = "네 말이 맞아, 내가 까먹었어.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "선장님, 일등급 함선은 우리 해안에 너무 큽니다. 이미 말씀드렸잖습니까.";
					Link.l1 = "맞아, 내가 깜빡했어.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0 && !CheckAttributeEqualTo(pchar, "questTemp.IslaMona.Tavern", "complete"))
			{
				dialog.text = "선장님, 장교 한 명을 제외하고 그녀의 모든 선원을 기함으로 데려가십시오.";
				Link.l1 = "아, 맞다! 그렇게 할게!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "그래서, 우리는 여기서 계속 있어야 하는가"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" '라는 이름의 '"+chref.Ship.Name+"'. 맞지?";
			Link.l1 = "그래.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "잠깐, 마음이 바뀌었어.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            LeaveShipIslaMona(&NPChar);
			dialog.text = "좋아, 우리가 그녀를 안전한 항구로 데려다 주지.";
			Link.l1 = "훌륭하군!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "어느 배를 타실 건가요, 선장님?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "잠깐, 마음이 바뀌었어.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "선장님, 당신 함대에는 더 이상 배를 넣을 자리가 없습니다.";
				link.l1 = "흠. 네 말이 맞는 것 같군.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
			if (AttributeIsTrue(NPChar, "StoreWithOff") && FindFreeRandomOfficer() < 1 ) {
				dialog.text = "선장, 당신 선원에 더 이상 장교를 둘 자리가 없는 것 같아요.";
				link.l1 = "네 말이 맞을지도 모르지. 나중에 다시 올 테니, 그동안 여기 잘 지켜서 다른 놈이 내 배를 차지하지 못하게 해.";
				link.l1.go = "exit";
				break;
			}
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "그녀를 데려가는 거야?";
			link.l1 = "그래.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "잠깐, 마음이 바뀌었어.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "여기? 아니. 하지만 울프릭이 이 근처에 큰 헛간을 지었어. 튼튼하게 지었고, 야자잎과 타르칠한 돛천으로 잘 덮여 있지. 자물쇠도 있고, 무역선 열 척을 채울 만큼의 화물을 둘 방도 있어\n지금은 비어 있지만, 네가 살펴보고 싶다면 열쇠는 내가 가지고 있어. 가 볼까?";
			link.l1 = "물론이지! 그런데 이 섬에 쥐들은 어때? 내 창고에 있는 물건들을 망치진 않겠지?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "울프도 대비해 놨어. 본토에서 고양이 두 마리를 데려왔지. 근데 수컷을 깜빡했는지라, 저 미친 암컷 고양이들이 발정기만 되면 엄청 시끄럽게 굴어. 그래도 쥐랑 들쥐는 잘 잡으니까 걱정 마. 선장님, 당신 물건은 해충이나 바람 걱정 없이 안전할 거야.";
			link.l1 = "좋아! 잘 써먹도록 하지. 열쇠는 네가 가지고 있고, 이 창고를 나한테 보여줘.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "따라오십시오, 선장님.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "아...";
			link.l1 = "음... 여자라니... 여기서 뭐 하고 있는 거야?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "오...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "나리! 나리 "+pchar.name+" 제발 죽이지 마! 살려줘! 타이렉스한테 아무 말도 안 할게! 나도 그 짐승이 싫어! 제발 부탁이야, 포르 파보르!";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "이봐, 아가씨! 들었지? 나랑 같이 가. 안 그러면 이 놈이 널 죽일 거야.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "어디로 데려가든, 나리, 내가 함께 가겠소!";
			link.l1 = "좋아, 그럼. 입 다물고 있어. 소리 지르거나 타이렉스를 부르면 죽여버릴 거야. 이름이 뭐지?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "미라벨...";
			link.l1 = "얌전히 있어, Mirabelle. 그러면 너한테도 좋게 끝날 거야. 내 옆에 붙어 있고 아무 소리도 내지 마.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "절대 안 하겠소, 나리.";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "나리?";
			link.l1 = "잘했어, 계집애. 그래서 네가 마음에 들어. 이제 내 배로 간다. 거기서 널 잠시 작은 선실에 가둬둘 거다. 미안하지만, 네가 타이렉스한테 달려가서 뭔가 말하는 건 원치 않거든.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "말도 안 돼, 나리! 난 절대 타이렉스한테 안 갈 거야, 그 자식! 난 걔가 정말 싫어! 정말 미워!!!";
			link.l1 = "이봐! 걔가 너한테 뭘 한 거야?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "많이... 난 그 자가 싫어, 정말 싫어!";
			link.l1 = "알겠어. 우리가 도착하면, 넌 꽤 근사한 집에서 살게 될 거야. 혼자서 말이지. 내 비위를 잘 맞추면 아무도 널 해치지 않을 거다. 이제 장정선으로 가라... 미라벨.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "도착했나, 나리?";
			link.l1 = "그래, 얘야. 여기가 내 마을이고 내 집이야. 이곳은 내 소유지지. 하지만 나는 여기 드물게 오는 손님일 뿐이야—밖에서 할 일이 너무 많거든. 네가 이 집에 머무는 동안 깨끗이 청소해 두어라, 안 그러면 너를 로드가와 그의 목수들에게 넘겨버릴 거다. 섬을 마음껏 돌아다녀도 좋아, 정말 아름답거든. 하지만 어차피 여기서 도망칠 수는 없어.";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "자, 도착했군. 여기가 내 집이야. 이 섬에 있는 모든 것은 내 거지. 자주 오진 않지만, 어차피 나는 배에서 살고 있으니까. 그래도 집을 돌볼 사람은 필요하지. 로드가르가 기꺼이 이 명예로운 역할을 너에게 넘기기로 했어. 마음껏 돌아다녀도 돼, 정글이든 해변이든. 하지만 반드시 동행을 데리고 다녀. 아직 야생 동물들이 있으니까. 어쨌든, 배 없이는 여기서 나갈 수 없어.";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "도망칠 곳이 없어, 나리\n "+pchar.name+". 나는 아무도 없고, 나를 필요로 하는 사람도 없어. 네가 날 창관에 팔지 않는 한...";
			link.l1 = "벽난로 옆에 지하로 이어지는 뚜껑이 있어. 거긴 가지 마라; 동굴로 떨어져 뼈가 부러질 수도 있고, 다시 못 올라와 굶어 죽을 수도 있다. 그러면 내가 괜히 너를 구한 셈이니 아깝지 않겠냐.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <-- legendary edition
            dialog.text = "나는 갈 곳이 없어, 나리 "+pchar.name+". 나는 가족도 없고 목적도 없어. 또다시 사창가에 들어가게 될지도 몰라.";
			link.l1 = "동굴로 이어지는 해치가 있으니, 가까이 가지 마라. 아래는 어둡고 위험하다.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "나는 멀리 떨어져 있겠소, 나리.";
			link.l1 = "위층에는 침실도 있어. 따라와.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "여기야. 집 전체를 다 보여줬어. 전에 네가 살던 타이렉스의 집보다 나쁘지 않지. 마음에 들었으면 좋겠다.";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "네, 나리. 훌륭한 집이군요. 나리께서 안 계실 때 잘 돌보겠다고 약속드립니다.";
			link.l1 = "네가 이렇게 협조적이라서 기쁘군. 정직하게 굴고 있는 거겠지. 솔직하게 말해, 그렇지 않으면 후회하게 될 거야. 착한 아가씨가 되어 내 마음 아프게 하지 마라, 그러면 나도 잘해줄 테니. Charlie Prince는 약속을 지키는 사람이야!";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = "믿어, 자기야. 여기 있는 게 Tyrex가 널 가둬뒀던 그 어두운 창고에 묶여 있는 것보다 훨씬 안전할 거라고 생각해.";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "감사합니다, 나리 "+pchar.name+". 내 동료가 날 죽이지 못하게 해줘서 고맙소. 당신은 내게 정말 친절하군...";
			link.l1 = "헤, 너 웃기네... 이마에 낙인이 있어도 얼굴도 제법 예쁘잖아. 다른 데도 다 멀쩡하길 바라지... 자, 이제 네 선장한테 뭘 할 수 있는지 보여 봐. 바다에서 흔들린 뒤로 몇 시간 푹 쉬자고.";
			link.l1.go = "mirabelle_21";
			link.l2 = "좋아. 이제 그만, 할 일이 많으니. 너는 여기 자리 잡고, 로드가르랑 녀석들도 만나 봐. 내가 돌아오면 더 얘기하자.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <-- legendary edition
            dialog.text = "감사합니다, 나리 "+pchar.name+". 내... 동료가 날 죽이지 못하게 해줘서 고맙소. 정말 친절하군.";
			link.l1 = "헤, 넌 참 웃긴 귀염둥이구나... 흉터가 있어도 얼굴도 예쁘고. 나머지도 멀쩡하길 바란다... 자, 네 선장한테 뭘 할 수 있는지 보여 봐.";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "좋아. 이제 됐네, 나는 할 일이 많아. 너는 여기 정착하고, 로드가르랑 녀석들도 만나 봐. 내가 돌아오면 더 얘기하자고.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Señor "+pchar.name+" 정말 다정하시네요... 진짜 신사이십니다. 유럽에서 온 지 얼마 안 되셨나 보군요.";
			link.l1 = "아첨하지 마, 이 거짓말쟁이 녀석, 난 안 속아. 허, 너 제법이구나, 미라벨! 타이렉스 녀석, 안목이 있네, 허허...";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "나는 아니야. 너는 신사지. 그런데 뭔가 이유가 있어서 일부러 무례하게 구는 거잖아. 흠... 아주 마음에 들었어. 다시 보기를 기다릴게...";
			link.l1 = "아, 그래, 신사라... 행운의 신사라니, 하하! 좋아, 자기야, 당분간 여기서 자리 잡으라고.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "안녕히 가시오, 나리.";
			link.l1 = "...";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <-- legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", 나리 "+pchar.name+"! 다시 만나서 정말 반갑소. 잘 지내셨소?";
			link.l1 = RandSwear()+""+RandPhraseSimple("이런 젠장, 내 영혼도 덜덜 떨리겠군!","오, 내가 휘두르는 저 대담한 검은 깃발 아래에서 살고 죽는 게 더 낫지!")+" 찰리 프린스는 괜찮아, 자기야.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.MirabelleBlock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "달링, 선장을 좀 더 행복하게 해줄 생각 없어?";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "당신을 위해서라면 뭐든지 하지, 나리!";
			link.l1 = RandPhraseSimple("갈고리 준비해!","승선해라!");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <-- legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "음... 나리, 당신은 마법사군요! 당신도 즐거웠길 바라요? 나는 최선을 다했어요.";
			link.l1 = "잘했어, 자기야.";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "이건 사실이 아니야, 아니라고! 나리 "+pchar.name+" 좋고 친절한 사람이야! 악당 해적인 척하는 것뿐이지! 당신이 그렇소, 나리 "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", 나리 "+pchar.name+"! 이렇게 다시 만나서 정말 반갑구나. 잘 지냈어? 왜 그렇게 풀이 죽어 보여?";
			link.l1 = "안녕, 미라벨. 내가 왜 슬퍼 보인다고 생각해?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "음, 딱 봐도 알겠어. 평소 같지 않네. 내가 기운 좀 북돋아줄까? 자, 어서! 내가 정글에서 정말 달콤한 과일을 좀 따왔고, 로드가르랑 그 녀석들이 어제 잡은 생선도 구워서 아직 따끈해.";
			link.l1 = "잠깐. 너랑 얘기 좀 하자.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "물론이지, 나리, 뭐든 말씀만 하십시오. 다 듣고 있소.";
			link.l1 = "말해 봐, 어떻게 타이렉스의 손에 넘어가게 됐지? 그리고 왜 이마에 도둑의 표식이 있는 거야? 두려워하지 마, 나는 절대 너를 해치지 않을 거야. 나는 그저 네 이야기를 듣고 싶을 뿐이야.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "아, 나리! 내 이야기는 짧고 시시해. 난 푸에르토리코에서 태어났어. 아버지는 백인 신사였고, 어머니는 인디언이었지. 아버지는 한 번도 본 적 없어. 어릴 때는 하인이었고, 어른이 돼서는 주인 장신구를 훔치는 어리석은 짓을 했어. 내 거라고는 아무것도 없었으니, 하루만이라도 장신구를 차보고 싶었거든. 당연히 다 들통났지\n재판이 있었고, 난 채찍질을 당하고 낙인이 찍힌 채 산후안 감옥에 갇혔어. 오래 있지는 않았지. 장교 하나가 우두머리와 거래를 해서, 난 금화 몇 닢에 필립스버그의 사창가로 팔려갔어\n거기서 1년쯤 지냈어. 어느 불운한 날, 타이렉스와 그 안경 쓴 비참한 친구가 우리를 찾아왔지.";
			link.l1 = "파스칼 라부아지에...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "그래, 그래, 그 사람 이름은 파스칼 라부아지에 나리였어. 내가 뭐가 마음에 들었는지 모르겠지만, 그들이 다녀간 뒤 얼마 안 돼서 타이렉스가 나를 조안나 부인에게서 사들여서, 나를 상자랑 물건들로 가득 찬 잠긴 집에 가뒀지. 내 인생에서 가장 끔찍한 시간이었어, 산후안 감옥에서 보낸 날들보다도 더. 타이렉스는 바다에 나가지 않는 한 매일 나를 찾아왔고, 그때만이라도 숨을 쉴 수 있었지만, 라부아지에 나리가 올 때마다 나는... 나는... 그게 제일 끔찍했어. 나리\n "+pchar.name+", 제발, 이것에 대해 말하지 않으면 안 될까?\n내가 거기 얼마나 있었는지 모르겠어. 그리고 당신이 와서 그 끔찍한 집에서 나를 데려갔지. 당신이 그렇게 친절해서 정말 다행이었어.";
			link.l1 = "친절하다고? 미라벨, 나도 똑같이 했잖아. 너를 섬으로 데려가서 집 안에 가뒀지.";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "아니오, 나리, 사실이 아니에요. 제가 여기에 갇혀 있다고요? 저는 매일 섬을 산책해요. 이곳은 정말 멋지고 평화로운 곳이에요. 집안일을 많이 해야 하냐고요? 전혀요, 그리고 이제는 익숙해졌어요. 그리고 당신은 타이렉스나 그의 상인 친구와도 달라요. 저는 항상 당신을 보면 기뻐요, 당신은 정말 젊고 잘생겼으니까요. 게다가 신사이기도 하고요...";
			link.l1 = "미라벨, 어느 도시로 데려다줄까? 돈은 충분히 줄게. 어디로 갈래? 아무 식민지나 골라봐.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "나리, 저를 쫓아내시려는 겁니까? 제발 그러지 마십시오, 부탁드립니다!";
			link.l1 = "음... 네가 평범한 삶으로 돌아가고 싶어할 줄 알았거든...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "아, 나리 "+pchar.name+", 그런데 나는 뭐가 남죠? 나는 낙인 찍힌 혼혈이라 결혼도 못 할 거예요. 또다시 창관에 팔려갈 거예요. 제발, 나리, 저를 쫓아내지 마세요. 여기 너무 좋아요; 어디에서도 이렇게 평화롭고 안전하다고 느껴본 적이 없어요. 로드가르와 그 친구들은 좋은 사람들이에요, 우리는 친구고, 그들은 한 번도 저를 다치게 한 적이 없어요—모두 저를 위해 목숨도 걸 거예요. 그들과 함께 있으면 늘 즐겁고 재미있어요! 가끔 해변에서 불을 피우고 제가 삼바를 추기도 해요. 제발, 나리, 무엇이든 할 테니, 그냥 여기 있게 해 주세요!";
			link.l1 = "좋아, 미라벨, 이곳이 그렇게 마음에 들면 여기 있어. 하지만 네가 여기서 죄수는 아니라는 것만은 알아둬. 언제든 나한테 여기서 데려가 달라고 말해도 돼.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "나의 친애하는 좋은 나리, 고마워요! 고마워요! 고마워요! 이런 부탁은 다시는 하지 않을게요 - 이 섬의 죄수로, 그리고 당신의 죄수로 남고 싶으니까요, 히히... 당신은 정말 친절하지만, 오늘은 왠지 슬퍼 보여요! 평소처럼 노래도 안 하고 욕도 안 하시네요.";
			link.l1 = "노래는 할 수도 있겠지만, 더 이상 욕은 안 할게, 미라벨. 그리고... 내가 혹시라도 무례하게 굴었다면 미안해.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "영국 귀족처럼 엄격하고 근엄하게 굴 거예요?.. 아... 나리, 오늘 밤에 춤추고 노래해 드릴까요? 오직 당신만을 위해서요. 이제 저와 함께 가요! 슬픔을 이기는 데 사랑만 한 약은 없으니까요. 정말 많이 그리웠어요.";
			link.l1 = "하! 좋은 지적이야, 아가씨... 가자.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "아, 나리 "+pchar.name+", 오늘은 정말 다정했어요, 음... 제게 만족하셨나요, 나의 사랑하는 카피탄?";
			link.l1 = "모든 게 정말 즐거웠어, Mirabelle.";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", 나리 "+pchar.name+"! 이렇게 다시 만나서 정말 기뻐! 잘 지냈어?";
			link.l1 = ""+LinkRandPhrase("나도 반갑다, 내 딸.","안녕, 미라벨. 넌 항상 똑같구나 – 명랑하고 아름다워서 참 보기 좋네.","안녕, 예쁜이. 정말 눈부시게 아름답구나!")+"나는 잘 지내고 있어. 너도 잘 지내길 바란다.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar,"quest.rodgar")) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "미라벨, 벌써 너와 네 족제비가 그리워. 내 바다늑대에게 키스해 줄래?";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "아, 내 사랑스러운 선장님, 나도 정말 그리웠어요! 어서 와요, 더는 못 참겠으니까!";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason Исла Мона
		case "mirabelle_44":
			dialog.text = "나리 선장님! 선장님 "+pchar.name+"! 너무 기뻐! 네가 우리를 구해줄 거야!";
			link.l1 = "나도 반갑구나, 미라벨. 자, 손실은 어땠어?";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "선장님, 선장님, 감사합니다! 정말 최고이시고, 가장 친절하십니다! 저를 괴물들로부터 구해주셨을 뿐만 아니라, 새로운 삶도 주셨습니다! 우리 모두에게!";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "선장 나리!";
			link.l1 = "너도 안녕, 이쁜이. 심심하지는 않지?";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "아, 선장님! 그 끔찍한 집에서 저를 구해주신 이후로 제 삶에 색과 기쁨이 찾아왔어요.";
			link.l1 = "행복하냐?";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "물론이지! 그리고 이 기쁨을 너와 함께 나누고 싶어... 네 방, 위층에서 기다릴게.";
			link.l1 = "대단한 여자네...";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "선장 나리!";
			link.l1 = "너도 안녕, 이쁜이. 심심하진 않았지?";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "아, 선장님! 그 끔찍한 집에서 저를 구해주신 이후로 제 삶에 색과 기쁨이 깃들었어요.";
			link.l1 = "행복하냐?";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "매우 그렇지! 그런데...";
			link.l1 = "알겠소, 나에게 뭔가 물어보고 싶은가?";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "네, 선장님! 저... 어떤 남자와 제 행복을 나누고 싶어요...";
			link.l1 = "그가 신경 쓸까?";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "아니에요, 아니에요, 선장님. 우리 함께라면 분명 행복할 거예요, 그건 확실해요. 다만... 허락해 주시겠어요?";
			link.l1 = "너야말로 누구보다 이걸 받을 자격이 있어. 하지만 내가 너희 둘을 결혼시켜주진 않을 거니까, 그런 말은 꺼내지도 마!";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "하하! 나리, 정말 고맙소! 고마워요, 선장 나리. 세상 사람들이 당신에 대해 뭐라고 하는지 나는 모르겠지만, 나는 언제나 당신을 가장 친절하고 명예로운 분으로 여겨왔소.";
			link.l1 = "행운을 빌어, Mirabelle.";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "피에 굶주린 도둑놈들! 뭐, 어차피 우리 전달자는 이미 포르토 벨로로 가고 있어. 곧 우리 함대가 도착할 테니...";
			link.l1 = TimeGreeting()+", 폐하. 이렇게 아름다운 저택에서 뵙게 되어 영광입니다. 우리가 떠난 후에도 이 저택을 계속 지키시길 바랍니다. 제 입장이라면 함대에 기대지 않을 것이며, 저희도 여기서 사흘 이상 머물 생각은 없습니다. 귀하께서도 포르토 벨로의 고귀한 돈들이 이렇게 빨리 도와주러 오지 않을 거라는 사실을 잘 아시리라 감히 말씀드리겠습니다. 그러니 본론으로 들어가시지요, 어떻습니까?";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "벌써 거래 얘기야? 창밖 좀 봐! 네 졸개들이 거리랑 집에서 무슨 짓을 하고 있는지 좀 보라고!";
			link.l1 = "오, 폐하, 이건 당신이 협조하지 않으면 저들이 할 짓에 비하면 아무것도 아닙니다. 저 자들이 어떤 놈들인지 아시겠지요...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "나는 그 해적 찰리 프린스가 얼마나 악질인지 잘 알고 있다! 그의 상사가 누군지도 알고 있지! 때가 되면, 우리는 히스파니올라에 있는 너희 도적 소굴을 불태울 거다! 얼마냐?";
			link.l1 = "말을 낭비하지 마시오, 총독 나리. 25만 페소나 내놓는 게 좋을 거요.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "뭐?! 네 건방짐은 끝이 없구나! 이건 강도질이야!";
			link.l1 = "이건 당연히 강도질이지. 그게 아니면 뭐겠어? 네 놈들 우두머리들이랑 상인, 무역상들 다 모아. 금도 큰 궤짝에 모아놔. 안 그러면... 너희랑 네 백성들한테 훨씬 더 끔찍한 일을 겪게 해주지.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "빌어먹을 해적 놈! 개자식! 이단자! 꺼져버려!\n";
			link.l1 = "네 더러운 입 때문에 몸값을 30만으로 올리겠다.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "지옥에서 타버려라, 개자식아!!!";
			link.l1 = "350,000. 계속하시겠습니까?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "도시에 그런 돈은 없어!";
			link.l1 = "거짓말이군. 그럴 리가 없어. 여기서라면 최소 백만은 모을 수 있겠지만, 유감스럽게도 그럴 시간이 부족하네. 그러니 내가 친절하고 관대하게 굴지. 얼마인지 알 테니, 가서 그 돈을 구해 오게.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "다시 말하지만, Charlie Prince. 카르타헤나에는 그런 돈 없어!";
			link.l1 = "오... 어쩜 그렇게 둔할 수가 있지. 커틀러스! 주변을 샅샅이 뒤져서 보이는 놈들 전부 여기로 데려와. 철저히 수색해! 우리는 당분간 여기서 기다리겠네, 나리...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "이봐, '고집쟁이' 나리! 아직도 카르타헤나 같은 멋진 도시에서 돈을 걷겠다는 생각 안 바꿨어?... 무슨 일이야, 왜 갑자기 그렇게 심각해졌어?! 괜찮아? 물이라도 가져다줄까?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "내가 알기로는, 이 두 여인은 네 아내와 딸이지, 맞나? 세 번째 아가씨는 하녀처럼 보이는데, 네가 별로 신경 안 쓰는 것 같으니 우리가 해치지 않을 거다. 하지만 이 두 미녀는 내 동료인 나리 커틀라스의 관심을 끌 수도 있겠군. 그가 마음에 들어 하는 것 같아, 나리. 그래서 어쩔 건데? 몸값을 치를 생각이냐?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "나... 시간이 좀 필요하겠어.";
			link.l1 = "아하! 이제야 제대로 말하는군! 그럼 여기서 누가 개자식이지? 내 부하들이 네 시민들을 괴롭힐 땐 신경도 안 쓰더니, 네 여자 둘은 완전히 다른 문제란 거냐? 감히 나랑 흥정하려고 했어, 이 멍청아? 찰리 프린스한테 덤비면 어떻게 되는지 똑똑히 보여주지!";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "가서 그 빌어먹을 몸값을 모아 와라. 35만, 한 푼도 깎지 마라. 하루밖에 없다. 우리는 여기서 와인 마시고 이 고운 여자들이랑 어울릴 거다... 서둘러라, 친구야. 안 그러면 내 옆에 있는 이 친구, 커틀라스 나리랑 내가 네 미녀들한테 반해버릴지도 모르지, 그럼 그 여자들도 몸값을 내야 할 거다. 앞으로! 행진!\n";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "네 피 묻은 돈이나 가져가라, Charlie Prince!";
			link.l1 = "몸값을 모아왔나? 훌륭하군! 하지만 한 시간 늦었소, 나의 친애하는 총독 나리. 이 한 시간이 나와 커틀라스에게 우리 인생이 이 아름다운 분들 없이는 너무나도 지루할 거라는 걸 깨닫게 해주었지. 이분들은 우리에게 정말 친절하고 수다스러웠거든...\n";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "너... 너!";
			link.l1 = "아, 일 때문에 너무 긴장했군, 친구야. 농담이었어... 커틀라스! 가자, 출발한다!";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "오, 이 사람이 바로 찰리 프린스구만, 악명 높은 해적이자 스페인 남부 해역의 공포라니!";
			link.l1 = RandSwear()+"헤, 내가 토르투가에서 그렇게 인기 있는 줄은 몰랐는데. 이름이 뭐지, 귀여운 아가씨?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "내 이름은 카밀라야.";
			link.l1 = "카밀라... 프랑스에 있을 때 그 이름을 가진 소녀를 알았었지. 아주 오래전 일이야!";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "(웩) ... 젠장... 미안해, 공주님, 오늘 밤엔 왕자가 꽤 취했거든. 그래서... 음... 나한테 왜 온 거야?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "여러 가지 이유 때문이지. 아니면 아무 이유도 없을지도 몰라.";
			link.l1 = "이런, 이건 너무 복잡하군. 너, 참 알 수 없는 아가씨로구나.";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "모든 아가씨에게는 비밀이 하나쯤 있어야지.";
			link.l1 = "네가 이 수수께끼를 풀어달라는 것 같은데? 아니야? 나는 아가씨들의 수수께끼 푸는 데는 선수라니까, 진짜야! 선술집에 가서 포도주 한잔 할까? 내가 최고로 대접해 줄게!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "음... 난 터프한 남자가 좋아. 하지만 아래층에서 취한 천민들 옆에서 와인 마시진 않을 거야. 방 하나 잡아, 거기서 마시고 얘기하자.";
			link.l1 = RandSwear()+"너 참 매력적이야! 따라와!";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "어서... 따라라, 숙녀분을 기다리게 하지 말고!";
			link.l1 = "물론이지, 내 사랑!";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "음... 생각 좀 해봐, 내가 이렇게 찰리 프린스랑 단둘이서 훌륭한 와인을 마시고 있다니...";
			link.l1 = "나랑 이 항해를 정말 즐기게 될 거야, 약속하지! 찰리 프린스는 자신에게 순종하는 숙녀들에게는 다정하고 친절하지. 순종할 거야, 공주님?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "히히... 당연하지, 자기야! 네 약속은 정말 유혹적으로 들려, 알지?";
			link.l1 = "그럼, 시간 낭비하지 말자고, 이쁜이?";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "오! 마음에 들어! 진짜 사내들이군!..";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			if(bSFW) PlayStereoSound("sex\sex_sfw.wav");
			else PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "음...";
			link.l1 = "마음에 들었어, 내 공주님?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "물론이지! 너도 나를 마음에 들어했길 바란다.";
			link.l1 = "헤! 이제 내 머리까지 맑아진 기분이야!";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "왕자님, 부탁이 있습니다. 도와주시겠습니까?";
			link.l1 = "너를 위해서라면 하늘의 별도 따다 주겠어, 하하! 계속해.";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "라 베가에 가서 타이렉스를 만나야 해. 난 그가 두렵지만, 너희는 같이 거래하잖아. 제발 나를 그에게 데려다줘.";
			link.l1 = "이것 좀 봐! 그런데 이렇게 상냥하고 여린 아가씨가 왜 규약의 수호자를 만나고 싶어 하는 거지?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "이 연약하고 귀여운 아가씨가 돈을 좀 벌고 싶어 해. 돌아가신 아버지랑 오빠들이 별로 남겨준 게 없거든. 타이렉스가 이 문제를 해결해 줄 수 있어.";
			link.l1 = "정말이야? 어떻게? 스페인 갈레온선에 대한 단서라도 찾으려고? 하하!";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "대상과 도시를 약탈하는 건 너처럼 강한 남자들의 일이야, 자기야. 마르쿠스에게 맡길 다른 일이 있어. 그자는 정보를 사고파는 놈이지? 나한테 뭔가 있는데... 내가 직접 쓸 수는 없지만, 마르쿠스라면 쓸 수 있을 거야. 난 그냥 조금만 나눠 받아도 충분히 만족해.";
			link.l1 = "흥미롭군! 더 말해 봐.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "음... 잘 모르겠는데...";
			link.l1 = "아, 좀 그러지 마. 나를 티렉스의 오른팔이라고 생각해. 지금까지 그 녀석을 위해 꽤 많이 파헤쳐 줬으니까, 믿어도 돼. 네 정보가 그만한 가치가 있다면 내가 직접 사겠어.";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "좋아. 더 얘기해주지. 하지만 돈을 받기 전엔 자세한 건 없어. 알겠어, 자기야?";
			link.l1 = "알겠어, 예쁜이. 찰리 프린스는 동료를 배신하지 않아... 무슨 말인지 알지, 하하하! 말해 봐, 다 듣고 있으니까.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "... 우리 아버지는 상선 스쿠너의 선장이셨어. 어느 날, 아버지는 어떻게든 마인의 정글 깊숙이 숨겨진 오래된 스페인 광산 정착지에 대해 알게 되셨지. 20년 전에 지진으로 파괴되어 광부들은 그곳을 버리고, 비밀 통로들도 잊혀졌어. 단 하나만 빼고. 아버지가 그걸 찾으셨지\n아버지는 내 형제들과 안내인을 데리고 그곳에 가셨고, 수년 전에 채굴되어 제련된 금으로 가득 찬 장소를 발견하셨어. 금이 아주 많았지. 적어도 백만 페소는 됐어. 아버지는 금을 옮길 인원을 데려오려고 배로 돌아왔는데, 그 배가 사라진 걸 알고 충격을 받으셨지. 일등항해사가 반란을 일으켜 아버지와 내 형제들을 무인 해안에 버리고 떠난 거야\n아버지와 형제들은 작은 배를 만들어 해안을 따라 항해하며 사람이 사는 곳을 간절히 찾았지만... (흐느낌) 폭풍이 그들을 덮쳤고 내 (흐느낌) 형제들은 죽었어. 아버지는 간신히 살아남아 집으로 돌아오셨지만, 오래 살지 못하셨어. 형제들의 죽음이 날마다 아버지를 좀먹었으니까. 돌아가시기 전에, 아버지는 지도를 만들어 내게 주셨어\n아버지는 내가 결혼하면 남편이 그곳에 가서 금을 가져오고, 우리는 왕처럼 살라고 하셨어. 물론 그렇게 할 거야. 하지만 난 내 남편이 저주받은 정글에 다시 들어가는 걸 절대 두지 않을 거야! 다시는 안 돼! 백만 페소라고 아버지는 말씀하셨지만, 그건 내 몫이 아니야. 그런 보물은 오직 가장 강하고 뛰어난 남자들만 가질 수 있어 – 마커스 타이렉스 같은 남자들 말이야. 그래서 내가 그를 만나러 가는 거야.";
			link.l1 = "그 지도 얼마에 팔 생각이야?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "이백 개의 금화 더블룬이지. 상금에 비하면 아무것도 아니야. 타이렉스라면 분명히 이 조건에 동의할 거야. 그 녀석은 크라수스만큼이나 부자거든.";
			link.l1 = "헤! 이게 다 속임수라면 어쩔 건데?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "내가 자살하러 온 것처럼 보여? 타이렉스를 건드리겠다고? 자기야, 차라리 가난하게 사는 게 죽는 것보단 낫지. 그러니까 나 거기로 데려가 줄 거야? 제발...";
			link.l1 = "지도는 어디 있지? 나한테 보여줄 거야?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "내 신부가 그것을 안전하게 보관하고 있지. 200두블룬을 주면 너에게 보여주겠다.";
			link.l1 = "좋아! 내가 사겠다. 선술집에 있는 낯선 놈들은 때때로 이런 쓰레기에도 훨씬 더 비싼 값을 부르지.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "그래? 정말이야, 자기야? 라 베가에 안 가게 돼서 정말 행복해! 솔직히 말해서, 나는 마르쿠스가 무서워. 그리고 너도 사실 좀 무섭긴 해... 하지만 마르쿠스보단 덜해.";
			link.l1 = "이렇게 귀여운 아가씨가 나를 두려워할 필요 없어. 돈은 어디로 가져가면 되지?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "거래를 하자꾸나: 우리 교회에서 아침 열 시부터 오후 한 시까지 아무 날이나 나를 찾아오게. 이 신성한 장소의 보호 아래 있으면 내가 훨씬 더 안전하게 느낄 테니. 그곳에서 거래를 마무리하자.";
			link.l1 = "아직도 나를 두려워하나? 하하! 걱정 마, 카밀라. 내가 너를 배신할 일은 없어. 찰리 프린스가 이백 두블룬 때문에 그렇게 비열해질 놈이 아니지, 게다가 나는 네가 곤란할 때 도와주고 싶으니까.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "훌륭해. 좋아, 잘생긴이, 기다리고 있을게... 오늘 밤 너랑 함께한 시간 정말 고마워! 우리가 만나서 정말 행복해!";
			link.l1 = "곧 보자, 이쁜이.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "그래서? 돈 가져왔어, 자기야?";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "그래. 여기 네 금화다, 이제 지도를 내놔.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "나는 바로 그 뒤에 있어.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "고마워, 자기야... 자, 받아. 내 아버지의 명예를 걸고 맹세하는데, 이 지도는 가짜가 아니야. 네가 가야 할 곳으로 정확히 안내해 줄 거야...";
			link.l1 = "좋아, 자기야. 지난번처럼 우리 거래를 축하하는 게 어때?";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "그러고 싶지만, 나리, 지금은 신부님께 고해성사를 준비하고 있어서 어떤 유혹도 멀리해야 하오. 다음에 하도록 하지.";
			link.l1 = "이봐, 나 놀리는 거냐, 아가씨. 좋아! 시간 낭비할 틈 없어: 곧 출항해야 하니까. 네 아버지의 지도가 진짜로 나를 금까지 이끌어 준다면 보상은 두 배로 쳐주겠다고 맹세하지.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "정말 너그럽구나, 자기야. 좋은 항해 되길 바라!";
			link.l1 = "요호호!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "네 놈들 때문에 내 아버지와 형제들이 죽었다. 카르타헤나를 공격한 네 놈들 때문에 그곳 모든 가정이 슬픔에 잠겼다. 이제 네가 두려워하기를 바란다. 우리가, 카르타헤나 시민들이 네 놈들의 짐승 같은 자들이 거리와 집에서 흥청거릴 때 느꼈던 그 두려움만큼 말이다. 지옥에서 불타게 될 거다, 찰리 프린스.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "이 세상에서 내가 이렇게나 기쁨을 느끼는 일은 상자 안의 쥐들이 서로 물어뜯는 걸 지켜보는 것뿐이지!\n가장 강하고 역겨운 쥐만이 살아남아. 그다음엔 그놈을 그냥 쥐어짜면 돼...";
			link.l1 = "아르! 너 누구야?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "나는 돈 엔리코다. 영국 놈들은 나를 폭스라 부르고, 네덜란드 놈들은 보스라 부르며, 프랑스 놈들은 르노라 부른다. 하지만 나는 내 스페인 별명, 소로가 더 마음에 든다. 나는 평범한 백성들, 가장 약한 이들을 괴롭히고 공포에 빠뜨리는 악인들을 벌한다.\n오늘 이 재판에서는 마르쿠스 타이렉스의 네 해적, 대담한 제프리, 커틀라스 펠리, 요정 루크, 그리고 찰리 프린스를 심판할 것이다. 이 도적들은 메리다와 카르타헤나에서 벌어진 학살의 책임자들이다. 마지막 놈, 잘생긴 장이라는 자는 여기 나타나지 않았다. 네 패거리 중 가장 영리한 놈인가 보군.";
			link.l1 = "뭐라고?!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "너는 쓰레기야, Charlie Prince. 하지만 바보는 아니지. 난 이미 다 알아냈어, 내 생각엔. 이건 전부 너를 위한 함정이었어. 내가 가짜 지도, 문서, 말, 그리고 금은보화의 약속으로 꾸민 거지. 나는 너희 모두를 이 지하 감옥으로 유인해서, 서로를 파멸시키게 만들었어. 그 역겨운 본성들, 즉 시기, 탐욕, 비열함, 그리고 양심 없음에 이끌려서 말이야. 이건 정말로 응보였지!\n";
			link.l1 = "카밀라... 그 여자애 뭔가 수상하다고 진작 알았어야 했는데!";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "카밀라라는 이름의 소녀는 아버지와 형제들과 함께 카르타헤나에서 평화롭게 살고 있었지. 그녀는 곧 결혼할 예정이었는데, 네놈들과 그 악마들이 도시를 습격했어. 네 해적들이 그녀의 소중한 사람들을 모조리 죽였고, 그래서 그녀는 반드시 복수하겠다고 맹세했지. 그 역할을 감당하는 건 그녀에게 너무나 힘든 일이었어. 심지어 가족을 죽인 그 개자식과 잠자리를 가져야 했지. 그 순간 그녀가 어떤 심정이었을지 상상하기조차 끔찍하다\n불쌍한 그 소녀는 며칠 동안 교회에서 용서를 구하며 기도했어. 네가 준 피 묻은 두블룬을 네 공격으로 가장 큰 고통을 받은 피해자들에게 기부했지. 지금은 수도원에 있어, 가엾은 영혼이. 네놈이 그녀의 인생을 망쳐놨다, 이 쓰레기야! 생각해 봐라! 네가 강간하고 과부로 만든 카밀라, 이사벨라, 로시타가 얼마나 많은지! 네놈들이 죽이고 고문한 후안, 카를로스, 페드로가 또 얼마나 많은지!\n메리다를 기억해라! 마을 우두머리에게 불태우지 않겠다고 약속해놓고, 결국 온 마을을 불바다로 만들었던 일을!";
			link.l1 = "나 그런 뜻 아니었어! 내가 관저를 나설 때 이미 불길이 사방에 번지고 있었어. 내가 이렇게 하라고 시킨 적 없어...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "네 해적들이 저지른 짓에 책임이 있지. 죽은 자들이 네 목에 매달려 있고, 곧 너를 지옥으로 끌고 갈 거다!";
			link.l1 = "그럼 오라고! 뭐야? 나랑 싸워! 이게 네가 원하는 거잖아?! 그럼 붙자!";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "아니, Charlie Prince. 무기를 잡으려 하지 마라, 소용없다... 널 죽이는 건 식은 죽 먹기지만, 네놈 같은 개자식에게는 빠른 죽음으론 부족하지. 넌 이 감옥에서 영원히 썩게 될 거다. 네가 들어온 문은 바깥에서 돌로 막혀 있고, 내 뒤의 문도 곧 막힐 거다. 게다가 튼튼한 쇠창살이 그 문을 지키고 있지. 그래, 이 두 개의 문 말고는 나갈 길이 없다\n뭐야... 내가 모든 문을 잠갔는데!";
				link.l1 = "무슨 일이야...";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "아니, Charlie Prince. 무기 꺼내지 마, 소용없으니... 널 죽이는 건 식은 죽 먹기지만, 네놈 같은 개자식에게는 빠른 죽음으론 부족하지. 넌 이 지하 감옥에서 영원히 썩게 될 거다. 네가 들어온 문은 바깥에서 돌로 막혀 있고, 내 뒤의 문도 곧 막힐 거다. 게다가 튼튼한 쇠창살이 지키고 있지. 끝이야, 이 두 개의 문 말고는 나갈 길이 없다\n아래에는 물이 있으니, 네가 저지른 짓을 곱씹을 시간은 충분할 거다. 여기서 혼자, 어둠 속에서, 굶어 죽거나 미쳐버리기 전에 네가 저지른 죄를 뉘우칠지도 모르지\n마지막으로 한 가지 더 - 아래에 있는 보물은 가짜다. 금괴는 색칠한 납덩이에 불과해. 두블룬은 진짜지만, 몇 개밖에 없어. 상자 안의 돌을 가릴 만큼만 있지. 해적에게 딱 어울리는 결말 아니냐? 너희는 가짜 보물을 두고 서로를 죽였지, Prince. 이제 작별이다. 아직 기도할 줄 안다면, 네 죄 많은 영혼을 위해 기도해라, Charlie Prince...";
		// belamour legendary edition -->
				link.l1 = "나 방금 마르쿠스 타이렉스의 선봉대를 전부 죽였어! 이런 녹슨 쇠창살 따위가 날 막을 수 있을 것 같아?! 네 머리로 이걸 박살내주지!";
				link.l1.go = "enrico_5a";
				link.l2 = "어쩌면 내가 그럴 만했을지도 몰라. 하지만 포기하지 않을 거야, 들리냐?! 방법을 찾아낼 거다, 난 항상 그래왔으니까!";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "맞아, 이 문은 오래됐어도 믿을 만하지. 문을 내리지 않아줘서 고마워—그랬으면 내가 좀 늦었을 거야. 하지만 오래 걸리진 않았을 거다.";
			link.l1 = "에르퀼 통작, 대머리 가스통! 너 같은 놈이야말로 왕자랑 그 졸개들 편을 들 줄 알았지. 여기서 너까지 만나게 되다니, 운도 좋군.";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "운이 좋다고? 죽고 싶어서 그러는 거라면야... 하지만 네가 그럴 생각은 없는 줄 알았지. 그 자와 맞서기보단 굶겨 죽이려고 내버려뒀으니까.";
			link.l1 = "나를 겁쟁이라고 몰아? 참 어리석군. 내가 왕자에게도 말했듯이, 죽음은 그에게 너무 쉬운 벌이야. 그는 나와 상대도 안 되지.";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "그리고 너는 나한테 상대도 안 돼, 돈.";
			link.l1 = "열 해 전이라면? 물론이지. 지금은? 거의 아니야. 게다가...";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "게다가 뭐? 왜 그렇게 뜸을 들여? 뭐, 네가 그 가면을 쓴 걸 보니... 나를 너무 일찍 포기하는 거 아니냐?";
			link.l1 = "문을 부쉈군, 하지만 힘만으론 나한텐 안 통해. 반사신경은 어떤가? 시력은? 넌 한쪽 눈뿐이잖아. 난 아직 두 눈 다 멀쩡하지.";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "뭐, 지금은 그렇지. 헤헤.";
			link.l1 = "포르토 벨로를 위해서라면, 너는 그 왕자보다 더 끔찍한 운명을 받아 마땅하다!";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "오, 내가 뭘 했는지 들었군? 너희들끼리 한동안 그 얘기 떠들겠지. 그럼 내가 어떤 일을 겪었는지도 알겠네.";
			link.l1 = "넌 늙었어, 톤자그. 이번엔 네 오만함이 너를 망하게 할 거야. 그리고 그래, 그냥 소문만 들은 게 아니야 - 카르타헤나랑 메리다는 네 짓이지. 포르토 벨로처럼 말이야.";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "칭찬으로 받아들일 수도 있었겠지만, 아니야, 내 짓이 아니야. 멀리서 보면 비슷해 보일 수도 있겠지. 하지만 너무 허술하잖아. 뭐, 그렇다고 해도 포르토 벨로에서도... 사건들이 있었지.";
			link.l1 = "사건들?! 그날 한 사람이 죽었지... 그리고 네가 그 학살을 시작한 걸 생각하면, 네가 모두를 직접 죽이지 않았다 해도 난 여전히 너를 탓해. 모든 '사건'에 대해 네 책임이라고 본다.";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "한 사람이라고? 그날 많은 이들이 죽었어. 누구를 말하는 거지?";
			link.l1 = "정말이지, 그런 말을 할 수 있다면 너에겐 심장이 없는 거야! 하지만 대답해 주지. 네가 죽이지 말았어야 할 사람, 내 아버지 돈 데 라 베가. 그분이 살아 계셨다면, 나는 결코 이런 길을 걷지 않았을 거고, 너희 모두도 아직 살아 있었을 거다.";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "입 다물어, 꼬맹이. 내 사랑하는 아내도... 거기서 죽었어.";
			link.l1 = "위로라도 바랐나? 그런 건 못 받아. 그건 네게 내린 신의 벌이야. 그래도 심장은 있긴 하네, 아주 작고 새까만 놈으로. 내 칼로 그걸 찾아내주지.";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "아, 내 마음에 대한 호들갑이군. 나보다 더한 걸 봤다고 생각한다면 착각이야.";
			link.l1 = "내가 그냥 돈이나 흥청망청 쓰는 망나니 부잣집 도련님이라고 생각하나? 알아둬라. 나는 도박이나 여자한테는 두블룬 한 푼도 안 썼다! 전부 너 같은 놈들과 싸우는 데 쏟아부었고, 내 인생을 그 일에 바쳤다!";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "그래서 뭐 어쩌겠다는 거야? 별로 성공한 것 같지도 않은데. 무역로엔 여전히 해적들이 들끓고 있어. 너 혼자서 십자군 놀이나 하고 있지. 걔네들은 한 무리나 되는데.";
			link.l1 = "누군가는 해야 해. 최소한 누군가는. 그리고 어쩌면, 해적 선장 한 놈만 죽여도 몇몇 목숨은 구할 수 있을지도 몰라.";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = "어리석군. 이상주의자지. 그리고... 어떻게 보면 고귀하기도 해, 네 방식만 아니었다면 말이지. 네 적들처럼 비열하잖아. 결국, 너도... 별반 다를 게 없어.";
			link.l1 = "나한테 설교하지 마! 명예란 그 법을 따르는 자들의 것이지. 너를 이해한다. 나도 너처럼 생각한다. 그리고 나는 벌을 내린다.";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "네 말이 맞아. 너한테 뭘 가르치는 건 의미 없지. 그러니 우린 평화롭게 헤어질 수 없겠군. 하지만 난 너 따위엔 전혀 관심 없어, 돈 엔리코. 넌 내 시간조차 아깝다.";
			link.l1 = "무슨 말이...";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
            dialog.text = "괜찮으십니까, 선장님? 조심하라고 경고했었지요. 내 촉을 믿었어야 했는데.";
			link.l1 = "그래, 괜찮아. 고마워, Hercule. 그냥 좀...";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "...놀랐어? 인정하는 거 두려워하지 마. 네 나이에 이런 상황이면 당연한 거야. 게다가 그 돈은 꽤 교활한 놈이거든.";
			link.l1 = "응. 그런데, 그 자가 너를 두려워하는 것 같더라. 그게 좀 놀라웠어. 하지만 덕분에 정신이 들었지. 그런데, 그 자 아직 살아 있나? 그런 것 같아. 그 자를 등지고 서 있으면 안 돼.";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "살아있지만, 기절했어. 이제 정신을 차리고 있군. 몸통이 아니라 머리를 노렸어야 했는데 – 알고 보니 저 귀족 이달고가 코트 아래에 가볍지만 튼튼한 흉갑을 입고 있었어. 허, 플리트우드조차도 그냥 얇은 포르푸앵만 입었었지. 아니었으면 여기 이미 피웅덩이가 생겼을 거야.";
			link.l1 = "어떻게 여기까지 오게 된 거지? 저 녀석이랑 같은 곳에서 온 거야?";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "지금 그럴 시간 없어. 곧 다시 일어날 거야. 일단, 이 문부터 들어 올리자.";
			link.l1 = "우리가... 뭐라고?? 그래, 네가 헤라클레스일 수도 있겠지, 하지만...";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "내 젊은 시절 동료들은 다들 강인하게 단련됐지. 이 경첩들은 핀이 짧아. 자, 도와줘, 선장. 내가 헤라클레스라 해도 이제 나이 좀 먹었거든.";
			link.l1 = "좋아, 셋에 맞춰! 그리고 들어 올려!";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // окружили Зорро
            dialog.text = "내 모든 계획을 망치고 이겼다고 생각하나? 물론 예상치 못한 일이긴 했지만, 그래도 나는 많은 것을 이미 대비해 두었지!";
			link.l1 = "네 옷 밑에 입은 얇은 큐라스 마음에 드는군. 왜 그걸 입고, 위에 제대로 된 갑옷은 안 입었지? 그냥 코트 자랑하려고 그런 거야?";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "나는 처녀가 아니오, 왕자 나리. 내 이유는 순전히 실용적이오 – 전신 갑옷은 내 움직임을 너무 제한하거든. 누구나 자기 방식이 있는 법이지.";
			link.l1 = "그런데도 나는 여기 있지, 프랑스인으로서 이미 큐라스를 입는 데 익숙해졌어, 스페인 놈들과는 다르게 말이지. 아이러니하군. 자, 이제 어쩔 거지? 우리를 함정에 빠뜨리지도 못했잖아. 모든 걸 준비해뒀다면서... 결투도 네 계획에 있었나? 아니면 이 칼과 큐라스는 진짜 싸움 말고 다른 데 쓰는 건가?\n";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "너도 나를 겁쟁이라고 부르려는 거냐? 내가 말했듯이, 너는 결투에서 죽을 자격이 아니라 오래도록 고통받을 자격이 있다. 네 영혼이 이 땅에서 네 죄를 모두 견디고 깨달을 시간조차 없다면, 그게 무슨 소용이겠느냐?";
			link.l1 = "지옥으로 가는 길은 선의로 포장되어 있다지... 그런데 피해자들을 괴롭히면 네 영혼도 더럽혀지지 않겠어?";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "절대 아니지. 결코 없어. 나는 내 자신과 내 신념에 끝까지 충실하니까.";
			link.l1 = "아하, 우리랑은 다르다는 거군. 우리가 얼마나 명예도 없는 비열한 쓰레기인지 그렇게 떠들어댔으니... 네 기대에 부응해 주지. 우리가 직접 상대해 주겠다. 같이.";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "당신께 제안이 있습니다, Don Enrico 나리. 지금 이 자리에서 결투를 신청하오. 귀하와 같은 귀인에게, 나 또한 귀인으로서.";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "흠. 그렇지 않으면 네가 버틸 수 없겠지. 톤자가 까다롭겠지만... 먼저 너부터 처리하마.";
			link.l1 = "그 사람이 네가 그렇게 하게 둘 것 같아?";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "너? 귀족이라고? 어쩌면 “왕자”일지는 모르겠지만, 네 피에 귀족의 피 한 방울도 흐르지 않는 것 같은데.";
			link.l1 = "너는 내게 진짜 이름을 밝혔지. 나도 내 이름을 밝히겠다. 나는 샤를 드 모르다. 그리고 우리는 서로의 명예를 충분히 모욕했으니, 이제 각자가 결투를 요구할 권리가 있지. 각오해라, 돈 엔리코.";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "하지만 나중에 네 선택을 후회하지는 마라.";
			link.l1 = "내 인생에서 많은 결정을 후회했지만, 이번만큼은 아니야. 각오해라!";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // после победы над Зорро
            dialog.text = "괜찮으십니까, 선장님? 저 고귀한 이달고가 단순히 흉갑만 입은 게 아니라 칼에도 독을 발랐더군요. 자, 이걸 받으십시오. 저는 정글을 걸을 때 항상 이 약을 몇 개씩 가지고 다닙니다. 언제 뱀이 물지, 아니면 인디언이 독화살을 쏠지 모르니까요.";
			link.l1 = "고맙네, Hercule. 나는 괜찮아. 자네가 제때 와줘서 정신을 차릴 수 있었지.";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "별 말씀을. 가자, 내가 여기서 데리고 나갈게 – 그가 입구를 돌로 막았다고 했어. 내가 다른 길을 찾았어, 지름길이야.";
			link.l1 = "말해 봐, 에르퀼... 포르토 벨로에서 정확히 무슨 일이 있었던 거지? 그리고 언제였어?";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "오늘은 그 얘기할 기분 아니야. 하지만 언젠가, 와인 한 잔이나 더 센 술을 마시면서 말할 수도 있겠지.\n지금은 여기서 나가자 - 꼬마 말이 맞아, 나도 늙어가는구나. 배에서 좀 쉬고 싶어.";
			link.l1 = "그럼 길을 안내해.";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "말해 봐, 형제여 - 어떻게 이렇게 끔찍한 괴물이 되어 버린 거지? 내가 해적들과 친해지라고 했을 때, 도시를 불태우고, 무고한 시민을 죽이고, 여자들을 고문하라는 뜻은 아니었어. 전쟁조차도 명예와 품위를 지키며 할 수 있는 법이야\n넌 우리 집안의 수치다. 아버지가 여기 안 계신 게 다행이야. 네가 해적이자 도적이 됐다는 걸 알았다면, 부끄러워서 돌아가셨을 거다!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "형제야! 형제야!\n내 말 들리나?\n두 개의 문 중 하나 뒤에 통로가 있어. 그 문은 열 수 있어. 열쇠가 네 근처에 있어!\n계단에서 찾아봐. 계단에서!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "하하하, 이봐, 내 용감한 악당! 왜 그렇게 침울해 있냐? 바다도 있고, 금도 있고, 럼주도 있고, 여자들도 있는데, 뭐가 더 부족하냐? 우리 처음 만났던 거 기억나지? 그때 내가 말했잖아 - 나는 화약 냄새도 두려워하지 않고 피를 강처럼 흘릴 줄 아는 놈이 필요하다고. 넌 내 모든 기대를 뛰어넘었어! 이제 진짜 해적이 됐구나, Charlie Prince! 하하하!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "진짜 피에 굶주린 해적이군! 아-아-하-하!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "우하하하하하하!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "너 누구야? 여기서 뭐 하는 거지? 빨리 대답해!";
			link.l1 = "나는 파데이 출신이야, 검은 뼈 한 묶음 받으러 왔어. 그가 미리 말해뒀어야 했을 텐데.";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "하! 겉모습은 신경 쓰지 마, 친구. 우리가 널 알아봤지; 그 모스크바 놈이 아주 자세하게 설명해줬거든. 그리고 가격에 기분 상하지 말라고도 하더군. 선금까지 계산하면, 네가 갚아야 할 건 은화 만 냥이야. 금화로 내면 오십 두블룬이면 되고. 자, 어떻게 할 거냐? 질질 끌지 마!";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "나는 50두블론을 내겠다. 그게 더 이득이지.";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "나는 10,000페소를 내겠다.";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "미안하지만, 지금은 노예를 살 여유가 없어.";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "좋군. 네 부하들에게 신호해서 물건을 가져가게 해.";
			link.l1 = "물론이지.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "훌륭하군. 네 부하들에게 신호해서 물건을 가져가라고 해.";
			link.l1 = "물론이지.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("Fifty slaves shipped to "+PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		
		case "SlavesTrader_X":
            dialog.text = "그래, 네가 원한다면 그렇게 하지. 이 물건은 언제나 사는 사람이 있을 거야. 또 보자, 친구.";
			link.l1 = "안녕히 가십시오.";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		// диалог Гаспара Златозубого Xenon
		case "GasparGold_meeting":
            dialog.text = "안녕하시오, 선장. 내가 틀리지 않았다면 자네가 Charlie Prince 맞지? 걱정 마시오, 내 벽에는 귀가 없으니. 솔직히 자네 이름 따위엔 관심 없소. 중요한 건 자네가 추천받고 왔다는 거고, 그 말은 우리가 거래할 수 있다는 뜻이지.";
			link.l1 = "너도 안녕, 가스파르 ‘골든투스’. 뭐, 사실 네가 뭐라고 불리든 난 별로 신경 안 써. 잡동사니 좀 살 생각 있다던데?";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		// ---> andre39966, Фриплейный Гаспарито
		case "GasparGold_meeting_sandbox":
			dialog.text = "환영합니다. 제 이름은 가스파르 파르망티에입니다. 무슨 일로 오셨습니까?";
			link.l1 = "안녕, 가스파르. 나는 선장 " + GetFullName(pchar) + "야. 이 지역 선술집 주인이 보냈어. 너 잡동사니를 사들인다고 들었는데?";
			link.l1.go = "GasparGold_meeting_01";
			link.l2 = "안녕, 황금이빨. 반짝이는 건 뭐든 산다고 들었어? 천둥에 맹세코, 우리 잘 어울릴 거야.";
			link.l2.go = "GasparGold_meeting_wrong";
		break;

		case "GasparGold_meeting_wrong":
			dialog.text = "실례지만, 다른 사람과 착각하신 것 같군요. 경비를 부르기 전에 이곳을 떠나주시죠.";
			link.l1 = "으... 알았어...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gaspar_sandbox_repeat";
		break;

		case "Gaspar_sandbox_repeat":
			dialog.text = RandPhraseSimple("이미 떠나달라고 말씀드렸을 텐데요.", "쓸데없는 얘기할 시간 없습니다. 저를 그냥 내버려 두시죠.", "당신의 무례함에 놀랐군요. 계속 귀찮게 하실 겁니까?");
			link.l1 = "진정해, 친구. 선술집 주인에게서 왔어.";
			link.l1.go = "Gaspar_Alternative";
			link.l2 = "더 이상 거짓말하지 마! 네가 보석 사는 거 다 알고 있어!";
			link.l2.go = "Gaspar_Angry";
		break;

		case "Gaspar_Angry":
			dialog.text = "그런 일은 하지 않는다고 이미 말했습니다. 내쫓기기 전에 당장 나가시죠.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gaspar_sandbox_repeat";
		break;

		case "Gaspar_Alternative":
			dialog.text = "그렇다면 이야기가 다르군요, 선장님. 제대로 찾아오셨습니다. 자, 보석을 좀 팔고 싶으신가요?";
			link.l1 = "흠, '내 거'라고 하긴 좀 그렇지. 헤헤.";
			link.l1.go = "GasparGold_01";
			NextDiag.TempNode = "GasparGold";
		break;
		// <--- andre39966, Фриплейный Гаспарито
		
		case "GasparGold_meeting_01":
            dialog.text = "맞아. 나보다 더 좋은 값을 제시할 사람은 없어. 뭐, 전당포 놈들이 혹시 그럴 수도 있겠지만, 걔네들은 많이 사지도 않지. 네가 팔고 싶은 건 뭐든 다 살 준비가 되어 있어. 귀중품을 굳이 직접 가져올 필요도 없어. 내 뒷문이 외딴 부두로 이어지거든. 네 배에 쌓아둔 잡동사니도 마음껏 나한테 팔아도 돼.";
			link.l1 = "좋군! 만나서 반갑다.";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "그건 내 개인적인 일이야. 더 이상 캐묻지 않는 게 좋겠군. 모든 건 내가 잘 처리하고 있으니, 나랑 거래해도 위험은 없어. 나머지는 네가 신경 쓸 일이 아니야.";
			link.l1 = "뭐, 위험이 없는 게 제일 중요하지! 그런데 또 물어보고 싶은 게 있어...";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "무엇을 도와줄까? 남는 진주나 보석을 처분하고 싶어? 아니면 금, 은, 보석류도 괜찮아? 전부 내가 사주지.";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "이봐, 장물아비로 사는 건 어떤 기분이야? 관리들이 두렵지 않아?";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "여기 뭐가 좀 있는데... 현찰로 바꾸고 싶어.";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "좋아, 그럼 교환하자. 두블룬이냐, 페소냐?";
			link.l1 = "페소로 하자 - 두블룬까지는 필요 없어. 일반 돈은 어디서나 받아주니까.";
			link.l1.go = "GasparGold_peso";
			link.l2 = "맞췄군 - 내가 딱 필요한 건 두블룬이야. 그러니 두블룬으로만 팔 거다.";
			link.l2.go = "GasparGold_dub";
			link.l3 = "지금은 팔 물건이 없어. 그냥 네가 값진 물건을 살 준비가 되어 있는지 확인하고 싶었을 뿐이야. 다음에 또 보자!";
			link.l3.go = "exit";
		break;
		
		// окно торговли
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// Диалоги после угроз вождю индейцев Кумване
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "아직도 겁주려고 하는 거야, 선장? 밖에서도 네 협박 소리가 들리더라.";
			link.l1 = "그놈들이 내게 선택지를 주지 않았지. 내가 타고파의 아내에게 선물을 주며 그의 도움을 청했어. 그런데 그녀는 내 말조차 들으려 하지 않더군. 이제 족장이 직접 그놈들과 얘기하게 두지. 만약 그가 저 고집불통 녀석들을 정신 차리게 못 한다면, 내가 직접 그의 심장을 가슴에서 꺼내버릴 거야. 그런데, 야하후가 누구지?";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = "인디언들과의 관계를 망치지 말았어야지. 우리 해적들에게는 칼과 배밖에 동맹이 없어. 하지만 이게 네 결정이라면, 어쩔 수 없지. 그리고 야하후는 사악한 악마야. 그에 대해 더 아는 건 없어.";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "설득에 시간 낭비하는 건 어리석은 짓이야, 레프리콘. \n 아니면 그 풍부한 전리품을 포기하고 인디언들과 좋은 관계나 유지하고 싶다는 거냐?";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "나는 둘 다 갖고 싶어.";
			link.l1 = "양쪽에 발을 걸치고는 이번엔 통하지 않아. 이제 그만 싸워, 이미 모든 게 끝났으니까. 내일 추장이 타고파의 결정을 우리에게 알릴 거야, 그리고 난 그가 날 실망시키지 않길 바란다. 그렇지 않으면... 극단적인 조치를 취해야 할 테니. 물론, 그러고 싶진 않다만.";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //разрешить отдыхать
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "자, 어떻게 되어가고 있나? 안내인은 구했나?";
			link.l1 = "아니, 장, 우리는 안 될 것 같아. 추장과 부족 전체가 카퐁족을 마치 악마가 향을 두려워하듯 두려워하고 있어. 우리 계획은 포기해야 할 것 같군.";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "이런 상황 전개에 Terrax가 기뻐하지 않겠군.";
			link.l1 = "네 생각에 내가 이렇게 된 게 엄청 기쁘기라도 할 것 같아? 겁쟁이 로코노 놈들은 카퐁족이랑 엮이고 싶어 하지도 않아. 설득이든 보상이든 아무것도 통하지 않거든.";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "그럼 협박을 써야겠군. 놈들한테 마을을 모조리 불태워버리고, 살아남은 자들은 누군가 우리를 안내할 때까지 고문하겠다고 전해.";
			link.l1 = "장, 너 완전히 미쳤냐? 나는 죄 없는 사람들 집에 불을 지를 생각 없어. 그리고 그들을 고문할 생각은 더더욱 없고.";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "찰스 프린스는 모범적인 후원자야. 너한테서 이런 다정한 면을 볼 줄은 몰랐어.";
			link.l1 = "이건 다정함이 아니야, 잘생긴 녀석. 좋아, 우리가 인디언 놈을 반쯤 죽게 고문하면, 그놈은 복수심에 우리를 카퐁족 손아귀로 곧장 이끌고는 자기만 아는 길로 사라지겠지. 나는 내 사람들 목숨을 그런 식으로 걸지 않아.";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "그렇다면, 레프리콘이랑 나는 이만 간다. 마라카이보 플랜테이션에서 날 구해준 대가로 은화 오만을 주지. 원래는 새 배를 사려고 모아둔 돈이야. 그리고 한 가지 충고하자면, 한동안 마르쿠스 눈에 띄지 않는 게 좋을 거다. 잘 있어라, 찰스 프린스.";
			link.l1 = "잘 가, Jean.";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
		// Тонзаг
		case "Nemezida_Tonzag_1":
            dialog.text = "이제 이 근처에 있는 놈들이 전부 몰려올 거야! 저 나무들을 폭파한 게 정말 좋은 생각이었는지 확신하시오, 선장?";
			link.l1 = "젠장! 모두가 도끼로 일했으면 더 나았을지도 모르겠군... 하지만 이제 와서 다 소용없지.";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "맞아. 가진 걸로 어떻게든 해야지. 준비해.";
			link.l1 = "너도, 에르퀼.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "아직도 이쪽으로 오고 있어. 그럼 이것들도 처리할까?";
			link.l1 = "만약 저놈들이 끝도 없이 몰려온다면 어쩌지? 우린 이런 골치 아픈 일 하러 온 게 아니잖아.";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "그래, 모든 일엔 끝이 있지... 하지만 네 말이 맞아. 후퇴하자. 그리고 빨리.";
			link.l1 = "서두르자!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "너무 집요해서 결국 우리를 따라잡았군. 여기 길이 있으니, 들어갈까? 그쪽이 방어하기 더 쉬울 거야.";
			link.l1 = "잠깐, 에르퀼. 저 소리 들려? 이미 안에 누가 있어. 너랑 녀석들은 여기서 처리해. 나는 안으로 들어가서 보물 뺏기기 전에 움직일게 – 아무나 우연히 들어갔다고는 생각 안 해.";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "좋아. 하지만 조심해, 뭔가 불길한 예감이 들어.";
			link.l1 = "너도! 난 저쪽으로 갈게.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // на берегу
            dialog.text = "뭔가 할 말 있소, 선장? 배까지 오는 내내 깊은 생각에 잠겨 있었잖소.";
			link.l1 = "그래, 맞아. 요즘 내가 뭘 하고 있는지 계속 생각하게 돼. 테락스에 대해서도... 그리고 그게 나를 어디로 이끌었는지도. 내 동생을 구하는 데 조금이라도 가까워졌나? 아니면 집에 돌아갈 수 있게 된 건가?..";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "흠. 좋은 질문이군. 그럼 네 대답은 뭐지?";
			link.l1 = "질문이 하나 더 있어. 전에 의미 없었다면, 또다시 의미 없겠지? 테락스는 날 도와주지 않을 거야. 내 형제 일도, 토르투가 일도 말이야.";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "아마 아닐 거야. 그건 그에게 쓸모가 없어. 이제야 그걸 깨달았다니 놀랍군. 그런데 다음 질문은 뭐지?";
			link.l1 = "대체 왜 내가 테락스 뒤를 졸졸 따라다니면서, 그놈 대신 위험한 일만 도맡아 했던 거지?!";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "이제야 제대로 된 질문이군. 괜찮은 질문이야. 이번엔 대답할 수 있겠어?";
			link.l1 = "결심에 더 가깝지. 오늘은 운이 좋았어. 하지만 또 운이 따를까? 언제 멈춰야 할지 아는 게 중요해. 그리고... 자신을 존중하는 것도. 이제 충분하다.";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "테락스와의 동업을 끝내기로 한 건가?";
			link.l1 = "그래. 난 더 중요한 일이 있어. 가족, 친구들. 그들과 함께라면 내 목표를 이룰 수 있어. 이런 식으론 아니지. 설령 그렇게 된다 해도... 마르쿠스와는 아닐 거야. 난 내 스스로 주인이 될 거고, 내 결정을 내가 내릴 거야.";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "내가 한때 따랐던 그 남자가 또 말을 하고 있어. 다시는 잘못된 놈들이랑 엮이지 마. 한때 내 흥미를 끌었던 그 잠재력을 헛되이 쓰지 마라.";
			link.l1 = "알겠어, 에르퀼. 그리고 다시 한 번 고마워. 이번엔 정말로 내 자신을 깨닫게 해줘서 고마워. 나는 더 이상 왕자의 하수인이 아니야. 나는 샤를 드 모르, 자랑스러운 귀족이지. 배에 타자 - 우리 둘 다 피곤하잖아.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// Книппель
		case "Nemezida_Knippel_1":
            dialog.text = "정말 엄청난 폭발이었소, 나리 – 내 선미에 키펠이 날아왔지! 발키리에서 쏜 일제사격 소리랑 똑같았소. 하지만 저쪽 녀석들도 그 소리를 들은 것 같아...";
			link.l1 = "걔네가 눈치챘으면 그건 걔네 문제지. 아무도 여기 오라고 한 적 없어. 한 번 혼쭐내 줄 준비됐지, 찰리?";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "언제든 준비됐습니다, 나리!";
			link.l1 = "좋아. 바로 시작하자.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "두려운데, 곧 손님이 더 올 것 같습니다, 선장님. 명령을 내려주십시오.";
			link.l1 = "우린 정글 더 깊숙이 들어가서 숨자. 저놈들 전부를 막아낼 방법도 없고, 애초에 그럴 생각으로 온 것도 아니니까.";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "예, 나리.";
			link.l1 = "그럼 출발하자!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "우릴 찾아냈어요, 선장님! 하지만 여기서 숨을 수 있습니다 – 이 길이 어딘가로 이어지는 것 같아요, 그런데 이미 누가 와 있는 것 같습니다.";
			link.l1 = "우린 숨지 않는다! 보아하니 다른 놈들도 보물을 눈치챈 것 같군. 계획은 이렇다:\n내가 먼저 가서 무슨 일이 벌어지는지 보고 올 테니, 너는 여기서 녀석들을 놈들과 함께 막아!";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "예, 나리.";
			link.l1 = "훌륭해. 이제 내려가겠어! 여긴 네가 잘 처리하겠지.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // на берегу
            dialog.text = "크흠... 괜찮으신가요, 나리?";
			link.l1 = "찰리! 지금 와서 내 걱정이라니, 참 좋은 때 골랐구나. 말 아껴둬라. 버틸 만하냐? 널 배에 두고 더 많은 사람을 데려올 걸 그랬어...";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "아, 그냥 긁힌 정도입니다, 나리. 좀 피곤하군요. 그렇게 싸워본 건 젊었을 때도 없었소! 하지만 놈들에게 제대로 한 방 먹였으니, 영원히 산탄포 소리가 귓가에 맴돌 거요!";
			link.l1 = "왕립 해군, 옛 방식이군! 사자처럼 싸웠구나, 찰리. 하지만 아직도 간신히 서 있잖아. 허세 부리지 마라 – 상처가 얼마나 심한 거지?";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "별일 아니오, 선장님, 그냥 탈진일 뿐이오. 뒤쪽 입구가 거의 바로 무너져버려서, 우리는 오랫동안 저 놈들을 막아내야 했소. 결국 나는 혼자 남아 상처를 입었지. 그래서 이리로 와서 길을 뚫고 응급처치를 받으려 했소.";
			link.l1 = "알겠어. 오늘 네 할 일은 다 했지. 나는... 실패했어. 우리 모두 누군가의 장난에 속아서 서로 싸우게 됐고—보물조차 없었어. 그리고 바보는 나만이 아니었지.";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "실패했나?.. 하지만 살아 있군, 나리. 무슨 일이 있었나? 도망친 건가?";
			link.l1 = "아니, 그래도 좀 뛰긴 했지. 미안하다, 친구야. 하지만 그 안에서 무슨 일이 있었는지는 아무에게도 말하지 않을 거야 – 가장 가까운 친구들에게도 말이야. 하지만 필요한 결론은 이미 내렸어.";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "무슨 결론을 말하는 거요, 나리? 난 항상 당신의 논리를 이해하는 건 아니오. 내 철학은 간단하오 – 좋은 컬버린포와 돛대에 사슬탄 한 방이면 충분하지.";
			link.l1 = "말해 봐, 너도 최근에 내가 그랬던 것처럼 스페인 놈들을 죽여 본 적 있겠지. 네가 왕립 해군에 있었을 때 말이야. 그리고 나중엔 플리트우드랑 같이.";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "내가 그랬지. 스페인 놈들, 네덜란드 놈들—다른 놈들도 많았어. 딕이 한 번 말했듯이, 우리 일은 위험하고 힘들거든. 그런데 왜 묻는 거야? 무슨 말이라도 하려는 거야?";
			link.l1 = "설명해 줄게. 하지만 먼저, 다른 질문이 있어. 네가 하고 있는 일과 그 이유에 대해 한 번이라도 의심해 본 적 있니, 찰리?";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "흠. 나는 내 행동이 왕실을 위한 것이라고 스스로에게 말했지. 명령을 걱정하는 건 고생만 남는 일이야 - 어차피 따라야 하거든.";
			link.l1 = "왕관... 뭐, 너도 나름 이유가 있었겠지. 난 그것조차 없었어 – 미셸이 테락스에게 접근하라고 시켰거든. 하지만 그 모든 희생이 가치 있었을까? 나나 그에게 도움이 되었을까? 그래, 그래, 우리 모두 돈들을 좋아하진 않지... 하지만 우리도 다 같은 인간이잖아.";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "무슨 말을 하려는지 이제 좀 알 것 같소, 나리.";
			link.l1 = "좋아. 말해 봐, 플리트우드가 떠났을 때 더 이상 네덜란드 상인들에게 포를 쏘지 않아도 돼서 기뻤나? 그들 중에는 정직한 사람들도 있었지.";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "생각해 본 적 없었어요, 선장님. 하지만 이건 확실히 말씀드릴 수 있습니다 - 언제나 선장님과 함께 복무하는 게 즐거웠습니다, 나리. 내가 거짓말한다면 목에 니펠을 감고 저주받아도 좋소!";
			link.l1 = "하하하, 좋아. 그런데 이것 좀 말해 봐 - 명령을 따르던 네가 더 힘들었을까? 아니면, 억지로 한 게 아닌 내가 더 힘들었을까?";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = "모르겠소, 나리...";
			link.l1 = "나도 그래. 하지만 상관없어. 중요한 건 이제 더 이상 테락스와 엮이고 싶지 않다는 거야. 이제 정말 끝이야. 찰리 프린스는 없어. 이제부터는 샤를 드 모르뿐이야.";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "하지만 이게 네가 형제를 구하려고 세운 계획의 일부 아니었어?";
			link.l1 = "그랬지. 하지만 결국 아무런 도움이 되지 않았어. 그러니 앞으로 그런 일을 또 하게 된다면, 그땐 오직 내 결정으로 할 거야. 그리고 정말로 내 목표에 가까워질 때만 할 거다.";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "무슨 일을 하는지 알고 있길 바라오, 선장. 테락스처럼 되지 않길, 아니면 교수대에 오르지 않길 바라오.";
			link.l1 = "나도 그러길 바라. 하지만 확실한 건 이제부터 내 목표와 이익이 우선이라는 거야. 이제, 네 상처부터 치료하자.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Лонгвэй
		case "Nemezida_Longway_1":
            dialog.text = "폭발 소리가 주목을 끌었소, 선장님. 적 부대가 우리 쪽으로 다가오는 것 같소.";
			link.l1 = "젠장! ...그 나무들을 더 잘 처리할 방법이 있었을 것 같아? 너라면 어떻게 했겠어?";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = "모르겠어. 하지만 지금 뭘 해야 할지는 알지 – 저 놈들을 처리해야 해.";
			link.l1 = "그래, 알겠다. 우리도 딱 그렇게 하도록 하지.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "새로운 사람들이 도착했습니다, 선장님.";
			link.l1 = "그래, 나도 눈치챘어. 고마워, 롱웨이. 하지만 저 놈들 상대할 시간 없어. 정글로 후퇴하자 – 어쩌면 우리를 놓칠지도 몰라.";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "흠, 물론 우리가 처리할 수 있겠지만, 네 말대로 하자.";
			link.l1 = "우린 이 싸움 필요 없어, 그러니까 가자.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = "놈들이 절대 포기하지 않고 우리를 잡으려 들 거예요, 선장님! 내가 말했잖아요, 진작에 저놈들을 죽였어야 했다고. 저 동굴에 매복을 할까요? 하지만 이미 누가 있는 것 같긴 한데요.";
			link.l1 = "여기서 놈들과 함께 매복을 준비하는 게 낫겠군! 내가 절대 놓치지 않을 건 그 보물이야. 누군가 이미 그 보물 소문을 들은 것 같은데... 그러니 내가 직접 확인하러 가야겠다.";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "조심하십시오, 선장 나리. 아무리 위대한 용이라도 한때는 금 산 위에서 죽은 적이 있다는 것을 기억하십시오.";
			link.l1 = "명심할게, Longway. 오늘은 우리 모두 죽지 않도록 해보자.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // на берегу
            dialog.text = "선장 나리, 거기서 무사히 빠져나오신 것 같군요.";
			link.l1 = "놀랐나, 롱웨이? 사실 나도 좀 놀랐어. 살아남은 건 너 하나뿐인 것 같군. 그런데 어떻게 살아남았지?";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "덩치 작은 고양이 떼가 호랑이를 이길 수 없지. 뱀들이 둥지를 틀어도 용을 쓰러뜨릴 순 없어. 백인들 중에서 나와 맞설 만한 자는 드물다.";
			link.l1 = "하지만 기억해둬, 롱웨이. 개떼도 사자를 찢어놓을 수 있지.";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "이제 대인 선장께서 롱웨이에게 지혜를 나누시나? 진작 내 조언을 들었으면 좋았을 텐데.";
			link.l1 = "금산의 용에 대해 말인가? 맞아, 나도 거의 용이 될 뻔했지—실은 거의 죽을 뻔했어. 하지만 금산에서는 아니었어—그런 건 없었거든. 대신 내가 찾은 건, 똑같이 중요한 다른 것이었지.";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "다음번엔 '거의'로는 부족할 수도 있소. 무엇을 찾으셨소, 선장님?";
			link.l1 = "그래, 이제야 알겠어. 내가 찾은 건... 지혜였지. 경험, 이해, 그리고 결단이었어. 말해 봐, 롱웨이, 우리 요즘 뭘 하고 있었지?";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "우린 해적이다. 이제 네 새로운 주인인 테락스 경을 위해 일하지. 밀수, 마을 약탈, 살인, 구출, 그리고 그의 사람들을 돕는 일까지.";
			link.l1 = "그 사람은 내 주인이 아니야, 알지. 그런데 젠장, 네가 너무 정확하게 다 말해버렸잖아! 내 자존심도, 내 체면도 다 잊고, 꼭 강아지처럼 그 사람만 따라다녔지.";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "롱웨이가 이해합니다, 선장님. 저 역시 소중한 목표를 위해 명예와 자존심, 존경심까지 잊고 반 메르덴과 로덴부르크 밑에서 일했었지요.";
			link.l1 = "말해 봐, 그 일로 스스로를 비난하나? 자신을 미워하나?";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "비난하냐고? 가끔은. 미워하냐고? 아니. 나는 내가 누구인지 알고, 기억하지. 내 목표, 내 길잡이 별도 기억해. 인생에서 그보다 중요한 건 없어. 너는 목표가 있나?";
			link.l1 = "너처럼 인도해 주는 별은 아니지만, 그래도 중요한 목표였지, 맞아 – 내 동생을 구하는 거였어. 하지만 그 목표에서 벗어나 버렸어. 그리고 그런 실수는 다시는 할 수 없어.";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "천조국에서 온 또 다른 지혜를 나누어 주지. 완전히 선하거나 악한 사람은 없어. 모든 이에게는 음, 즉 어둠과 무지, 그리고 양, 즉 빛과 지혜가 함께 존재하지. 그 균형은 누구에게나 달라지기 마련이야.";
			link.l1 = "그러니까, 내 양(陽)은 샤를 드 모르야. 그리고 내 음(陰)은 찰리 프린스지. 하지만 언젠가는 샤를 드 모르조차 어둡고 힘든 결정을 내려야 할지도 모르겠군.";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "그게 인생이지요, 선장 나리. 누구나 어둡고 밝은 선택을 하게 마련입니다.";
			link.l1 = "그러나 왕자의 가면이 내게 거의 달라붙을 뻔했지. 하지만 벗어던질 거다. 샤를 드 모르트는 귀족이지, 심부름꾼이 아니야. 이제부터는 달라질 거다. 내 자존심과 품위를 되찾겠다. 이제부터 나는 내 스스로의 주인이다.";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "Longway가 당신의 결정을 찬성합니다, 선장 나리.";
			link.l1 = "고맙다, 롱웨이. 그런데 말이지, 자유 선장이 되지 않은 걸 후회한 적은 없나? 네 말대로 '주인'인 나를 섬기면서 말이야?";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "흠. 롱웨이는 자기 배를 지휘하는 걸 그리워하고 있지. 하지만 나는 너를 알아보겠어. 보통의 백인 야만인들과 달리 나에게 존중과 지혜를 보여줬으니 말이야. 어쩌면 나는 다른 삶을 원할지도 모르지. 하지만 너를 도운 걸 후회하지는 않아.";
			link.l1 = "그 말을 들으니 기쁘군, Longway. 이제... 이곳과 음의 길을 떠나자. 그리고 우리 삶에 양을 더 들이자고. 내가 제대로 이해한 거 맞지?";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "그래, 맞아. 이제부터는 훨씬 더 나은 도를 따르길 바란다.";
			link.l1 = "다오?";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "길이지, 선장 나리. 또는 본질이라고도 하지. 하지만 우리 경우엔, 길이야.";
			link.l1 = "내 앞길이 어떻게 펼쳐지든, 이제는 진정 중요한 것에서 다시는 벗어나지 않을 거야. 이곳을 떠나자, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Тичингиту
		case "Nemezida_Tichingitu_1":
            dialog.text = "찰스 선장, 이쪽으로 많은 사람들이 오고 있어요. 당신의 연기 신호에 끌려온 거예요. 그리고 분명 우리 편은 아니에요.";
			link.l1 = "아, 네가 말한 대로 그냥 '연기 신호'였으면 좋았을 텐데, 정글 전체에 울려 퍼졌어. 어쩔 수 없군 – 우리 스스로를 지키자. 분명히 전대가 뒤에서 덮치는 꼴은 보고 싶지 않으니까.";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "그래, Charles 선장. 먼저 공격하라!";
			link.l1 = "공격해! 탄약 아끼지 마!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "더 온다! 사람들이 더 몰려온다.";
			link.l1 = "정글로 도망가자, Tichingitu! 숨어서 때를 기다리자. 나는 싸우러 온 게 아니라 보물을 찾으러 왔어!";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "필요하다면, 정글에 매복을 설치할 수 있어.";
			link.l1 = "맞는 말이야. 이제 움직이자 – 빠르되 조용하게.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "찰스 선장, 저기 보세요! 앞에 통로가 있습니다. 그리고 그쪽에서 발소리랑 목소리가 들려요.";
			link.l1 = "누가 보물에 대해 또 알아낸 거야? 젠장! 너도 우리 뒤에서 나는 소리 들리냐? 따라잡힌 것 같군. 티칭기투! 내가 앞을 살펴보고 올게. 너는 녀석들이랑 뒤를 막아!\n";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "우리가 해볼게! 너는 가!";
			link.l1 = "너만 믿는다!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // на берегу
            dialog.text = "찰스 선장! 살아남으셨군요! 티칭기투가 이 소식을 들으면 기뻐할 거예요.";
			link.l1 = "고마워, 친구야. 나도 기쁘다. 내가 살아남았고, 네가 무사해서 다행이야. 분대 전체에서 남은 건 너뿐인 것 같구나.\n많이 있었냐? 정말 잘 막아냈더라.";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "많이 있지. 하지만 내 전사는 우리 마스코그 마을에서 가장 뛰어난 전사 중 하나야. 거기서 무슨 일이 있었지? 찾던 보물은 발견했나?";
			link.l1 = "아니야, 티칭기투. 우리가 속았어 – 보물은 없었어. 요즘 우리가 다 같이 해온 일에 대해 어떻게 생각해?";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "우리가 뭘 해왔지, Charles 선장?\n항해했지. 네 적들을 무찔렀고.";
			link.l1 = "내 말을 못 알아듣는 것 같군. 그럼 말해 봐, 부족에서 쫓겨난 게 슬프냐? 돌아가고 싶어? 형제들이 그립냐?";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "물론이지, 친구들과 가족이 그립다. 하지만 돌아가라고? 이제 내 고향은 더 이상 존재하지 않아... 그녀 없이는. 게다가, 그 사악한 코요테, 주술사 놈도 있잖아!";
			link.l1 = "미안해, 그 얘기를 꺼낼 생각은 아니었어. 있잖아, 나도 얼마 전에 말하자면 부족에 들어갔거든. 나 같은 선장들로 이루어진 부족 말이야. 그런데 결국엔, 그저 바다의 늑대인 척하는 승냥이 떼였다는 걸 알게 됐지...";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = "그래서 어떻게 된 거야? 이제 우리 뭐하지?";
			link.l1 = "좋은 질문이군. 나도 그 자칼들 사이에서 자칼이 될 뻔했지. 그러니 이젠 충분해. 내 친구들과 내 선원들, 그게 바로 내 '무리'야.";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "티칭이투는 네가 부족을 찾았다니 기쁘다고 하네, Charles 선장.";
			link.l1 = "고마워, 친구야. 꼭 하고 싶었던 말이었어. 너랑 나, 우리 둘 다 각자의 주인이자 부족이지. 이제 정말 중요한 일로 돌아갈 시간이야.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Айронс
		case "Nemezida_Irons_1":
            dialog.text = "누가 오고 있어! 그리고 소리로 봐선, 우리랑 추수감사절을 같이 즐기러 오는 건 아닌 것 같아.";
			link.l1 = "젠장, 뿌리들! 좋아, 이제 저 악당들을 처리해야겠군 – 보물을 배로 옮길 때 당하는 것보단 지금이 낫지.";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "맞았어. 준비됐지?";
			link.l1 = "물어볼 필요도 없었지. 우리가 선택권이 있는 것도 아니잖아.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "런던 빈민가의 쥐처럼 사방에 깔렸습니다, 나리! 어쩌시겠습니까 - 여기서 버티며 놈들과 총질을 할까요?";
			link.l1 = "지금이 아니야, 물러서! 우리는 싸우러 온 게 아니라 보물을 찾으러 왔어!";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "헤, 난 이의 없어.";
			link.l1 = "그럼 속도를 올려!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "이봐, 선장, 저길 봐 - 이 길이 어딘가로 이어지는 것 같아. 그리고 저쪽에서 들리는 소음을 보니 꽤 시끌벅적한 것 같은데!";
			link.l1 = "혹시 다른 놈이 보물 소문을 들은 건가? 토미, 들리냐? 놈들이 우리를 따라잡았어. 좋아, 나는 앞으로 갈 테니, 너희는 여기서 제대로 환영해 줘라!\n";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "이제 들리기 시작했군! 저게 누구든 간에, 서두르는 게 좋을 거야, 흐흐. 안 그러면 우리가 여기까지 고생해서 온 의미가 뭐가 있겠어?!";
			link.l1 = "아, 그렇게 되면 정말 싫겠어.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // на берегу
            dialog.text = "아, 당신이군, 선장! 그래, 살아남았네. 솔직히 말해서 기대 안 했어. 그래도 기쁘다니까, 오해하지 마, 헤헤.";
			link.l1 = "나도 예상 못 했어, 거짓말 안 할게. 하지만 네가 살아남았다는 사실에는 전혀 놀랍지 않아. 도망친 거야?";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "나한테 너무하군! 토미 아이언스는 절대 도망치지 않아! 그냥 지원군을 데리러 돌아올 뿐이지. 하지만 그럴 필요도 없었어 – 내 놈들과 내가 직접 처리했거든. 물론, 또다시 살아남은 건 나 혼자뿐이지만, 헤헷...\n";
			link.l1 = "이번에는 지원군을 데리러 갔어야 했을지도 몰라. 하지만 나는... 나는 도망쳤어.";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "도망쳤어? 허, 또 나를 놀라게 하는구나. 하지만 사실 나는 일이 끝나자마자 바로 너한테 달려가고 싶었어! 어떤 지원군보다 내가 더 낫다는 거 알지. 그냥...";
			link.l1 = "무슨 일이야, Tom?";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "젠장, 내가 이리저리 헤매는 사이에 네 뒤쪽 입구가 바위에 막혀버렸어. 난 통과할 수가 없었지. 그걸 치우는 데 너무 오래 걸려서 거기서 널 도와주지도 못했다니, 참 창피하군. 애들을 데려와서 바위를 옮기려고 돌아가는 길을 찾다가 나 혼자 좀 길을 잃기도 했어... 내가 돌아왔을 땐, 넌 이미 돌아와 있었지.";
			link.l1 = "그래, 오늘 나한테 무슨 일이 있었는지 말하는 게 창피할지도 모르지.";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "그리고 무슨 일이 있었어? 겁내지 말고 말해 봐. 근데 웃긴 일이면, 나 웃을 거니까 알아둬. 그게 당연하지 않겠어? 친구란 어깨를 내주고, 웃으면서 팔꿈치로 툭 치는 거지.";
			link.l1 = "그래, 위로는 참 잘하는군. 말해 봐, 토미. 해적질이 좋다고 했지. 나랑 다시 그 일로 돌아오게 되어 기뻤어?";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "이렇게 말할게. 내가 해적이든 아니든, 내가 진짜로 좋아하는 건 모험이야! 내 대답이 마음에 안 드는 것 같군. 이런 일, 이런 큰 문제들은 사실 내 알 바가 아니거든.";
			link.l1 = "나를 만족시키지 않는다는 건 아니야. 하지만 내가 얘기하고 싶었던 건 그게 아니었어. 있잖아... 티락스랑 어울리면서 내 목표에서 완전히 벗어났다는 걸 깨달았어. 그리고... 찰리 프린스는 용감한 해적 선장이 아니라 그냥 시다바리 같은 놈이었어, 알겠냐, 톰? 이 정도면 충분해.";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "알겠어. 그래서 네가 테락스한테 그렇게 휘둘리는 걸 보고 놀랐던 거야. 너답지 않아 보였거든.";
			link.l1 = "그때 나는 정말로 찰리 프린스였을지도 모르지. 하지만 우리가 다시 해적질을 할지 말지는 내가 결정한다! 그리고 그건 오직 내 이익에 진짜 도움이 되고 내 목표에 가까워질 때만이다!";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "이제야 제대로군! 하지만 한마디 하자면, 찰리 프린스든 샤를 드 모르든 결국 너잖아. 그래서 너랑 있으면 항상 지독하게 재미있었지!";
			link.l1 = "그 말을 들으니 기쁘구나, Tommy.";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "기억해, 거의 아무도 너 자신 말고는 도와주지 않아. 남들이 대신 결정하게 두느니, 혼자라도 네가 좋아하는 일을 하는 게 낫지!";
			link.l1 = "맞아. 나도 테락스랑 있을 때 딱 그랬지. 앞으로 또 누굴 따르게 되더라도, 그건 제대로 된 조건일 때뿐이야. 더 이상 빌어먹을 심부름꾼처럼은 안 할 거라고!";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "네 말이 맞아! 이제 여기서 나가자 - 내 다리가 벌써 후들거린다.";
			link.l1 = "이봐, 그 말 내가 하려고 했는데, 하하. 하지만 네 말이 맞아, 가자. 우리 앞에 중요한 일이 많이 남았어, Tom. 이런 일 말고.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Алонсо
		case "Nemezida_Alonso_1":
            dialog.text = "선장님, 우리에게 손님이 온 것 같습니다! 여기 우리만 있는 게 아니네요.";
			link.l1 = "딱 우리가 필요했던 거군... 좋아, 지금 처리하자. 나중에 두면 더 골치 아플 테니까.";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "예, 선장님.";
			link.l1 = "준비해!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "놈들이 점점 더 많아지고 있어!";
			link.l1 = "그럼 더 이상 계속할 필요 없지! 후퇴해! 놈들을 따돌리고 바로 보물로 간다!";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "예, 선장님!";
			link.l1 = "비켜, 비켜!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "선장님, 여기 입구가 있는 것 같습니다! 그리고 누군가 이미 안에 들어가 있어요.";
			link.l1 = "잘 들어, 우리를 누가 따라왔어. 나는 안으로 들어가서 확인해 볼 테니 너희는 여기서 자릴 지켜. 엄호해라, 이놈들아!";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "예, 선장님!";
			link.l1 = "자리를 지켜라. 행운을 빌지, 우리 모두에게!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase("도둑이군! 경비병들, 저 자를 잡아라","도둑이군! 경비병들, 저 여자 잡아!")+"!!!","믿을 수가 없군! 내가 잠깐 한눈판 사이에 내 물건을 뒤지고 있잖아! 거기 서, 도둑놈아!!!","경비병들! 도둑이야! 도둑을 잡아라!!!");
			link.l1 = "아아악, 악마다!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
		
		// <-- legendary edition
	}
}
