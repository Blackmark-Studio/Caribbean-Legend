// диалоги Уракана, Канека и прочих индейцев ица
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "필요한 것 있습니까?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// ица-горожане
		case "itza_ctz":
			dialog.text = LinkRandPhrase("또 다른 창백한 얼굴이군... 위대한 신부께서 네 심장을 도려내는 걸 기뻐하시겠지...","창백한 얼굴은 테야살로 오는 법을 알지만, 아무도 그 도시를 떠나지 못한다!","놀랍군, 창백한 얼굴이여. 아직도 영혼의 땅으로 가지 않았구나... 걸을 수 있을 때 걸어라, 곧 네 조상들을 보게 될 테니.");
			link.l1 = LinkRandPhrase("흠, 두고 보자...","나를 겁주려 들지 마라, 붉은 피부의 전사여. 난 그것보다 더한 것도 봤으니.","가 봐, 가 봐. 애들 좀 겁줘 보라고.");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("위대한 카빌이시여, 제 적과의 전투에 축복을 내려주십시오!","위대한 카빌과 위대한 쿠쿨칸께서 우리에게 친히 강림하셨도다. 고대 마야 시대에도 이런 일은 없었소!","우리는 쿠쿨칸과 카빌 사이의 위대한 전투에 대한 전설을 우리 아이들에게 전해주지!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// Уракан - вождь ица
		case "urakan":
			dialog.text = "너는 위대한 전사다, 창백한 얼굴이여. 우리는 너의 피를 신들에게 바친다. 너는 품위 있게 죽는다.";
			link.l1 = "진정해라, 붉은 피부의 전사야. 네 카넥이 나를 쿠쿨칸이나 그 누구에게도 제물로 바치게 두지 않을 거다. 네 전사들은 나를 잡지 못했다. 그들 모두 전투에서 쓰러졌지.";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "그래, 너그러운 전사여, 창백한 얼굴이군. 하지만 너는 수백 명의 타야살 이차 전사들을 감당할 수 없지. 그런데, 흥미로운 말을 하는구나. 위대한 카넥과 쿠쿨칸에 대해 어떻게 알게 되었지?";
			link.l1 = "음, 내가 맞혀보지... 너는 카넥이 아니니까, 이름이 우라칸이고 사제 카넥의 아들이겠군?";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "네 입은 진실을 말하는구나, 창백한 얼굴이여. 나는 우라칸이다, 그리고 놀랐다네.";
			link.l1 = "이걸 보면 더 놀라게 될 거야... 봐.";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "오, 신들이시여! 창백한 얼굴이 가면을 썼다면, 때가 온 것이오... 그대가 바로 쿠쿨칸께서 말씀하신 자로군. 그분께서는 그대가 타야살에 도착하면 우리더러 그대를 그분께 데려오라 명하셨소. 그분은 이미 그대가 온 것을 알고 계시오.";
			link.l1 = "쿠쿨칸?! 그가 테야살에 있다고?";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "그래, 하얀 전사여. 케찰코아틀이 타야살로 온다. 곧 그는 조상들에게 빛을 가져다주기 위해 떠날 것이며, 마야의 위대한 도시로 갈 것이다.";
			link.l1 = "젠장! 그러니까, 그 자가 이미 여기 와 있군...(목소리를 낮추며) 우라칸, 나는 모든 걸 알고 있어. 네가 진실의 수호자와 함께 크살 차를 보내서 크소체아템과 쿠쿨칸의 가면을 찾게 한 게 바로 너라는 걸...";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "당신의 눈에서 놀라움과 함께 의심도 보이는군, 위대한 추장 우라칸. 쿠쿨칸이 마음에 들지 않는 것 아닌가?";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "모든 이차 전사들은 위대한 쿠쿨칸께서 오신 것을 기뻐하고 있소, 하얀 전사여. 그대는 쿠쿨칸 앞에 서야 하오. 그분께서는 여러 밤 동안 그대를 기다리셨소. 그는 위대한 예언자요. 모든 것을 미리 아시지. 날으는 뱀에게 가시오, 다른 길은 없소. 우리는 그대가 타야살을 떠나는 것을 허락하지 않을 것이오.";
			link.l1 = "쿠쿨칸이 시간의 문을 통과하는 순간, 너희 모두, 네 자신까지도 존재를 멈추게 된다는 걸 모르겠어?\n그리고 가장 재미있는 건, 네가 다른 모습, 다른 육체로 다시 태어나게 된다는 거지... 어쩌면 평범한 전사로, 아니면 불구나 거지로 태어날 수도 있어...";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "가거라, 창백한 전사여. 쿠쿨칸은 이차 전사들의 대사원에 있을 것이다. 다리를 곧장 건너 큰 피라미드가 보일 때까지 가라.\n사원의 아래쪽 문으로 들어가 성소로 다가가라.";
			link.l1 = "좋아. 나는 쿠쿨칸에게 가겠다, 우리가 이 만남을 피할 수 없다는 걸 알았으니. 하지만 경고는 했으니 명심해라.";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// экспа за бой
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "가거라, 하얀 전사여. 쿠쿨칸이 너를 기다리고 있다.";
			link.l1 = "가는 중이야...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "이것이 현실이 되었소! 당신이 쿠쿨칸과 싸우는 모습을 보고, 나는 당신이 바로 카빌임을 알았소. 당신은 내 아버지와 쿠쿨칸 때문에 죽음에 처한 이차족을 구하기 위해 타야살에 오셨소. 내 아버지, 위대한 사제 카넥은 오래전에 죽은 마야 조상들의 이름으로 이차족을 파멸로 이끌었소.\n나는 오랜 세월 이차족을 지켜온 전쟁추장 우라칸이오. 타야살을 살아서 떠난 창백한 얼굴은 단 한 명도 없었소. 내 전사들과 나는 이차족이 앞으로도 오랫동안 안전하게 살아남을 수 있도록 지켜왔소. 나는 내 백성 모두를 희생시키고 싶지 않소.";
			link.l1 = "그건 알고 있었소, 우라칸. 그래서 내가 다리에서 도와달라고 부탁했지.";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "위대한 카빌의 눈을 피할 수 있는 것은 아무것도 없다네. 우라칸이 자네의 진정한 정체를 알아보지 못한 것을 용서해 주게.";
			link.l1 = "걱정 마시오, 우두머리. 나는 쿠쿨칸의 인간 화신을 물리쳤소. 하지만 우리 앞에는 또 다른 중요한 임무가 있소 - 과거로 통하는 문을 닫아야 하오. 이 부자연스러운 시간의 구멍을 반드시 봉인해야 하오. 나를 도와줄 수 있겠소?";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "우라칸이 무엇을 도와줄까, 오 카빌?";
			link.l1 = "너는 크사틀 차를 진리의 수호자와 함께 크소체아템과 쿠쿨칸의 가면을 찾으러 보냈지. 그러니 그 가면이 시간의 문을 닫는 데 쓰일 수 있다는 것도 알고 있겠군. 네 아버지가 그 이야기를 해주더냐?";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "아버지는 말씀하지 않으신다. 나는 지식과 지혜의 신전에서 기록을 연구한다. 하지만 우라칸에게는 많은 것이 불분명하다. 어쩌면 카빌이라면 이해할 수 있을까?";
			link.l1 = "정확히 무엇을 알아냈지?";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "나는 그것을 외워 두었네. 그 글에는 이렇게 쓰여 있지: \n '해가 비를 거슬러 떠오르고, 불이 그들 사이 삼각형을 이루면, 토힐의 다리를 맞부딪쳐 시간의 제단 위에서 쿠쿨칸의 가면을 불태우라. 그리고 이츠아마의 시간의 문을 세상 끝날까지 봉인하라.'";
			link.l1 = "뭐야.";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "그래.";
			link.l1 = "예수님... 문을 보여주소서.";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "그들은 쿠쿨칸 신전에 있어. 하지만 그곳의 문은 잠겨 있지. 오직 우리 아버지만이 그 문을 잠그고 열 수 있어. 아버지께서 쿠쿨칸 신전의 문을 여실 때 이렇게 말씀하시지:\n  
"태양은 오고 가고, 물은 떨어졌다가 가라앉고, 불은 타올랐다가 사그라들고, 전쟁과 평화는 번갈아 오지만, 오직 하늘만이 영원하다. 시간 위에는 오직 하늘만이 있을 뿐이다."";
			link.l1 = "흥미롭군... 그걸 기억해 두고 우리가 뭘 할 수 있을지 보자고...";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "나는 여기, 아래쪽, 시간의 제단 근처에 머문다.\n나는 타이살의 모든 피라미드와 건물을 내부에서 다 보았다.\n열쇠들을 찾아라. 나는 여기 남아 있겠다.";
			link.l1 = "중요한 질문이 있으면 꼭 당신에게 오겠소.";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// экспа за бой
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "위대한 카빌에게 우라칸이 조언이나 행동으로 도울 수 있겠소?";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "내가 발견한 이 석판을 한번 봐. 내가 어디서 찾았는지로 보아, 네 아버지와 관련이 있었던 게 틀림없고, 분명 평범한 물건이 아니야...";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "나는 대사원의 꼭대기에서 또 다른 입구를 찾았지만, 봉인되어 있더군. 어떻게 안으로 들어갈 수 있지? 내가 찾는 것이 그 안에 있을지도 몰라.";
				link.l1.go = "treasure";
			}
			link.l9 = "지금은 아무것도 없어, 우라칸. 나 혼자 알아서 할게...";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "신의 석판이야. 아버지께서는 여러 조각을 가지고 계시고, 그분께 매우 소중한 것들이지. 고대 타야살의 건축가들이 이 석판을 사용해 숨겨진 장치를 작동시키고, 문을 열고 닫으며, 심지어 마법 의식까지 행했어.\n제자리에 두면 작동하는데, 그게 바로 아버지께서 하시는 일이야. 하지만 나도 너처럼 전사라서, 제대로 다루는 법은 몰라. 어쩌면 카빌이 알지도 모르겠군?";
			link.l1 = "반드시 진상을 밝혀낼 거야...";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "여기가 타야살 보물의 문이오. 그곳에는 이차 인디언들의 재물이 잠들어 있소. 오직 내 아버지만이 안에서 이 문을 열고 닫을 수 있소. 그분 없이는 아무도 보물 방에 들어갈 엄두를 내지 못하오. 나조차도 그렇소.";
			link.l1 = "네 아버지는 입구를 어떻게 열었지?";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "아버지께서 말씀하시길: '어떤 보물이든 양면이 있다. 이 두 면을 아는 자만이 타야살의 보물에 들어설 수 있다.' 이것이 무슨 뜻인지는 나도 모르네. 어쩌면 카빌이 짐작할 수 있지 않을까?";
			link.l1 = "이것도 우리가 해결할 거야...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "해냈군요, 위대한 카빌이시여! 이제 이차의 백성들은 안전합니다. 저는 카넥의 아들 우라칸으로서, 당신께서 내리신 영예에 결코 누를 끼치지 않을 것이며, 당신의 이름으로 타야살을 비열한 백인들의 침략으로부터 반드시 지키겠습니다.";
			link.l1 = "믿을 만하군, 두목. 자, 이제 축하할 수 있겠어. 우리가 쿠쿨칸의 배신자 같은 계획을 막았으니 말이야. 이제 그는 다시는 시간의 혁명을 일으키지 못할 거야.";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "위대한 카빌께 영광을! 나와 내 세대에게 타야살에서 두 신을 목격한 것은 큰 영광이오. 우리는 이 역사를 우리 아이들을 위해 기록하오. 그들은 타야살에서 신들의 전투에 대해 알게 될 것이오! 카빌께 영광을! 영광이여!";
			link.l1 = "술이 필요하군...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// Канек - жрец ица
		case "kanek":
			dialog.text = "너는 지금 깃털 달린 뱀, 창백한 얼굴이여, 위대한 쿠쿨칸의 혼이 인간의 육신에 깃든 존재 앞에 서 있도다. 네가 그의 화신의 아버지를 통해 그의 형제가 된 것은 행운이며, 내가 그의 어머니, 곧 그를 낳은 여인의 아버지인 것도 행운이로다. 이는 큰 영광이다. 어쩌면 그래서 네가 강한 전사가 되어 아직 살아 있는 것일지도 모르지.\n하지만 네 시간도 곧 끝나리라, 창백한 얼굴이여. 우리는 새로운 시대, 위대한 마야의 시대를 시작할 것이다. 우리만의 힘을 세우고, 다시는 창백한 얼굴들이 우리 세계에 들어오지 못하게 할 것이다. 곧이니라. 나, 사제 카넥이 직접 가서 의식을 시작하겠다!";
			link.l1 = "훌륭하군...";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "우라칸, 우리 주인님 말씀 들었지. 이제 항복해!";
			link.l1 = "위대한 자들이 서로 싸울 때는, 우리 같은 평범한 인간들은 한쪽에 물러서서 멀리서 지켜보는 게 낫지요, 아버지...";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "뭐?! 정신 차려라, 아들아!";
			link.l1 = "이 자는 쿠쿨칸의 형제이자 위대한 전사요. 나는 그에게서 카빌 그 자체의 현신을 보았소! 저런 신을 버틸 수 있는 자는 그밖에 없소. 신들의 결투에서 빈둥거릴 틈 따윈 없소, 아버지! 그리고 쿠쿨칸에게 제물을 바치면, 내 전사들이 카빌에게 피를 바칠 것이오!";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "정신이 제대로 박혀 있나, 우라칸?";
			link.l1 = "수년 동안 나는 우라칸의 이름을 이어받아, 카빌의 이름으로 우리 땅을 외지인들의 침략으로부터 성공적으로 지켜 왔다네. 수백 명의 외지인들이 우리 곤봉 아래 쓰러졌고, 그 누구도 타야살을 떠난 적이 없었지. 하지만 내 평생 이렇게 강하고 빠른 전사는 처음 본다네, 저 창백한 얼굴 말일세. 만약 그가 쿠쿨칸을 쓰러뜨릴 수 있다면, 그는 바로 카빌의 혼이 깃든 화신일 것이오!";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
