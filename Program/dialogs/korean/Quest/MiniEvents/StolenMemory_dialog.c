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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
		break;

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "아가씨, 당신이 미소 짓지 않으면 포르토프랭스의 매력도 사라진다고들 하더군요.\n오늘이 바로 그런 날인 것 같습니다.\n솔직하게 여쭙겠소, 무슨 걱정거리라도 있으신가요?";
			}
			else
			{
				link.l1 = "아가씨, 당신의 아름다움과 우아함에 대한 소문이 내 귀에까지 들렸소. 그런데 직접 보니 소문이 오히려 부족할 정도로군요. 포르토프랭스도 당신이 미소 짓지 않으면 매력이 사라진다는 말도 들었습니다. 오늘이 바로 그런 날인 듯하군요. 감히 당신의 기분을 흐리게 한 그 악당의 이름을 말씀해 주시오. 내 명예를 걸고 그 자에게 결투를 신청해, 당신의 고운 얼굴에 다시 미소를 되찾아 드리겠소.";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "아, 마드모아젤, 당신의 관심이 참으로 감동적이군요... 솔직히 말해, 당신의 걱정이 내 마음을 움직입니다. 하지만 안타깝게도, 내 슬픔의 원인은 단순한 대화로는 풀릴 수 없는 것이오. 누구의 잘못도 아니고, 그저 아무리 굳센 이라도 어쩔 수 없는 상황 때문이오.";
				link.l1 = "상황이라구요? 장담하건대, 아가씨, 제게는 "+GetFullName(pchar)+" 어떤 장애물도 넘지 못할 것은 없지. 무슨 일이 있었는지 말해 봐—내가 도울 수 있을지도 몰라.";
			}
			else
			{
				dialog.text = "오, 나리, 정말로 친절한 말씀의 달인이시군요. 고백하자면, 거의 저를 미소 짓게 만드실 뻔했습니다. 하지만, 유감스럽게도 결투로는 제 문제가 해결되지 않아요. 오늘 제 하루를 어둡게 한 것은 악당이 아니라, 나리처럼 용감한 신사조차도 극복할 수 없는 상황이랍니다.";
				link.l1 = "상황이요? 친애하는 마드모아젤, 선장 "+GetFullName(pchar)+" 어떤 폭풍도 견딜 수 있지! 만약 내가 실패한다면, 맹세컨대 처음 마주치는 놈의 모자를 씹어 먹겠어!";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "정말 그렇게 원한다면, 무슨 일이 있었는지 말해 주겠소. 하지만 먼저, 이 대화가 우리 둘만의 비밀로 남을 거라는 약속을 해 주시오.";
				link.l1 = "나에게 맹세코 약속드리오, 아가씨. 무엇을 말씀하시든 우리 둘만의 비밀로 지키겠소, 설령 그 비밀을 바다 밑바닥까지 가져가야 한다 해도.";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+", 그대는 정말로 가장 근심 많은 숙녀조차도 기쁘게 하는 재주가 있군요. 하지만 부디, 죄 없는 행인들의 모자만은 살려주시길. 정말로 원하신다면, 무슨 일이 있었는지 말씀드리겠어요. 다만 내 말은 우리 둘만의 비밀로 남겨주겠다고 약속해 주세요.";
				link.l1 = "제 목숨이 위협받더라도, 마드모아젤, 당신이 내게 하는 모든 말은 절대적으로 비밀로 지키겠다고 맹세합니다.";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "좋소. 내 방에서 목걸이가 사라졌네... 하지만 단순한 장신구가 아니라는 점을 이해해 주게. 그 목걸이는 내 마음속에 소중한 자리를 차지한 이가 내게 준 것이었네. 그것이 없어진 상실감은 단순한 소유물의 손실보다 훨씬 깊은 상처로 느껴지네\n누가 이런 일을 저질렀을지 오랫동안 고민해 보았지만, 결국 한 가지 결론에 도달했네. 두렵게도 내 하인들 중 한 명이 아닐까 싶네. 오직 그들만이 내 사적인 방에 들어올 수 있고, 그런 귀중한 물건을 탐낼 수도 있으니 말일세. 하지만 감히 이 사실을 공개적으로 밝힐 수는 없네...";
			link.l1 = "정말로 민감한 일이군, 특히 비밀을 원한다면 더더욱 그렇지. 하지만 내가 도우려면, 그토록 비밀을 지키려는 이유를 알아야 하오. 우리가 맞닥뜨릴 위험을 모른다면, 나도 모르게 우리 둘 다 위험에 빠뜨릴 수 있소. 누구를 피해야 하는지, 어떤 위협이 그림자 속에 도사리고 있는지 말해 주시오.";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "자유롭게 말할 수 없소? 그렇다면, 아가씨, 나는 그저 행운을 빌어주는 것 말고는 더 해줄 수 있는 게 없겠구려. 나는 음모나 비밀스러운 일에는 취미도 재주도 없소. 내 생각엔, 이 문제는 도시 경비대의 도움을 받으면 금방 해결될 일이오. 하지만 그대는 이 혼란한 바다에서 더 위험한 길을 택한 것 같구려.";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "솔직하게 말할 수 없소? 그렇다면 용서를 구해야겠군, 마드모아젤, 이 비밀의 안개 속에서 나는 완전히 무력해지는구려. 나는 은밀한 일이나 음지의 거래에는 별로 흥미가 없소. 그대의 곤란은 아주 단순해 보이오. 도시 경비대가 해결할 간단한 문제지. 그런데도 그대는 이 일을 유럽 왕실의 궁정에나 어울릴 음모로 엮으려는 듯하구려.";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "이게 그 유명한 선장 "+GetFullName(pchar)+" 역경을 마주하면 어떻게 하지? 조금만 복잡해져도 도망치는 건가? 네 재능은 럼통을 세거나 부두 상인들과 말싸움이나 하는 데 더 어울릴지도 모르겠군. 내가 바라는 건 단 하나다. 네게 명예가 조금이라도 남아 있다면, 내가 말한 것은 반드시 비밀로 지켜라. 그럼, 안녕히 가시오, 선장.";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;
		
		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Juli_5":
			dialog.text = "현명하게 말씀하시는군, "+GetAddress_Form(NPChar)+". 그렇다면 진실을 말하겠어요. 이 목걸이는 우리 삼촌의 분노를 사는 남자에게서 온 것이에요—이 섬의 프랑스령 총독이지요. 삼촌께서는 그 사람과의 모든 접촉은 물론, 이름조차 입에 올리는 것조차 금지하셨어요. 만약 삼촌이 이 선물의 출처를 알게 된다면, 그 여파는 저뿐만 아니라...\n";
			link.l1 = "더 말하지 마시오, 마드모아젤. 완벽히 이해했소. 안심하시오, 당신의 목걸이는 최대한 은밀하게 되찾아 드릴 것이며, 당신의 비밀은 용이 보물을 지키듯 철저히 지킬 것이오.";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "진심으로 감사드립니다, "+GetSexPhrase("Monsieur "+pchar.lastname+"",""+pchar.name+"")+". 이런 혼란스러운 시기에 그대의 용기와 이해심이 내 마음을 따뜻하게 해주오. 내 비밀이 그대의 손에 안전하게 지켜질 것이라 전적으로 믿소. 이 미묘한 모험에 행운의 바람이 그대의 돛을 가득 채우길 바라오.";
			if (pchar.sex == "woman")
			{
				link.l1 = "행동하는 자에게는 행운이 따릅니다, 아가씨. 안심하십시오—조수(潮水)가 해변으로 돌아오듯, 반드시 당신의 목걸이를 되찾아드리겠습니다.";
			}
			else
			{
				link.l1 = "용기 있는 자에게는 행운이 따르오, 마드모아젤. 내가 당신의 소중한 목걸이를 되찾는 즉시, 마땅히 있어야 할 그 우아한 손에 돌려드리겠소.";
			}
			link.l1.go = "Juli_7";
		break;

		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;

		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "아, 선장님, 돌아오셨군요! 소식이 있습니까? 제 목걸이를 되찾으셨기를 기도했습니다. 제발 그렇다고 말씀해 주세요.";
				link.l1 = "이제 걱정 끝이야, 줄리. 목걸이를 되찾았고, 네 여린 손에 제자리를 찾아주게 되어 이보다 더 기쁠 수 없어.";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "아, 선장님, 돌아오셨군요! 소식이 있습니까? 제 목걸이를 되찾으셨기를 간절히 바랍니다. 제발 그렇다고 말씀해 주세요.";
				link.l1 = "실망시켜서 유감이오, Julie. 수색은 계속되고 있소. 하지만 희망을 가지시오—당신의 소중한 목걸이를 되찾아 줄 때까지 나는 어떤 수단도 가리지 않을 것이오.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Starpom_1":
			dialog.text = "안녕하시오, 나리. 무슨 일로 우리 배에 오셨소?";
			link.l1 = "나는 트리스탄 르니에르 선장을 찾고 있다; 그의 주머니를 두둑하게 해줄 제안을 가지고 왔다.";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "나는 트리스탄 르니에 선장과 중요한 사적인 일로 꼭 이야기해야 하오—개인적인 일인 것, 이해하시겠지.";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "선장님은 육지로 나가셨소, 유감이지만. 급한 일이면 마을 어딘가에서 찾아볼 수 있을 것이오.";
			link.l1 = "혹시 그의 목적지를 아시오? 이 항구에 올 때 자주 들르는 곳이라도 있소?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "선장님은 육지로 나가셨소, 유감이지만. 일이 급하다면 마을 어딘가에서 찾아볼 수 있을 것이오.";
			link.l1 = "그의 목적지를 아시오? 이 항구에 올 때 자주 들르는 곳이라도 있소?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "실례했습니다, "+GetAddress_Form(NPChar)+", 하지만 선장님께서는 자신의 동정에 대해 함구하십니다. 제가 아는 것은 몇 시간 전에 그분이 하선하셨다는 것뿐입니다.";
			link.l1 = "그 정도만으로도 도움이 되네. 도와줘서 고맙소.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;

		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "도대체 넌 누구냐? 무슨 권리로 내 사적인 방에 무단으로 들어오는 것이냐?";
				link.l1 = "나는 선장이오 "+GetFullName(pchar)+". 그리고 나는 중요한 일로 왔소.";
			}
			else
			{
				dialog.text = "그대는 누구시오, 아가씨? 오늘 밤에 초대한 기억이 없는데. 하지만 고백하자면, 예상치 못한 손님이 때때로 더... 흥미롭기도 하오. 이런 아름다운 분께서 내 누추한 거처에 오신 이유가 무엇이오?";
				link.l1 = "나는 선장이오 "+GetFullName(pchar)+". 그리고 내 방문은 즐거움이 아니라 사업 문제와 관련된 것이오.";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "사업 때문인가? 도대체 어떤 일로 이렇게 무례하게 끼어드는 것이오?";
				link.l1 = "아주 간단하오. 그대가 내가 찾으러 온 목걸이를 가지고 있지.";
			}
			else
			{
				dialog.text = "사업 때문이라고? 흥미롭군... 그대처럼 매력 넘치는 숙녀가 내 개인 방까지 찾아올 만큼 급한 상업적 일이란 대체 무엇이오?";
				link.l1 = "달콤한 말 따위는 집어치우시오, 나리. 나는 그대가 가진 목걸이를 받으러 왔소. 그리고 그래, 그 목걸이가 네 손에 있다는 것쯤은 정확히 알고 있지.";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "하! 목걸이라고? 사실 최근에 그런 걸 하나 손에 넣었지. 그런데 그게 너랑 무슨 상관이냐? 설마 처음 보는 놈이 달라고 한다고 내 물건을 내줄 거라 생각하는 건 아니겠지?";
			}
			else
			{
				dialog.text = "목걸이? 그렇소... 최근에 그런 장신구를 손에 넣었지. 그런데 선장, 내게 정당하게 속한 이 보석을 어떻게 넘겨받겠다는 것이오?";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "이 조각에 대해 오천 페소를 드릴 준비가 되어 있습니다. 이 금액이면 똑같이 훌륭하거나 어쩌면 더 근사한 장신구도 살 수 있을 겁니다. \n한편, 이 특별한 목걸이는 그 어떤 금전적 가치보다도 소중히 여기는 사람에게 돌아가게 될 것이오.";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "솔직하게 말하지, 나리. 이제 선택지는 거의 없네. 목걸이를 순순히 넘기고 살아서 다시 항해할 것인가, 아니면 저항하다가 네 시체에서 내가 직접 가져가게 할 것인가. 선택은 자네에게 달렸지만, 서두르는 게 좋을 걸세.";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				dialog.text = "오천이라고? 그래, 선장, 꽤 설득력 있게 흥정하는군. 자, 그 깜냥한 물건 가져가. 그렇게 중요하다면.";
				link.l1 = "그대의 지혜는 그대의 관대함에 버금가오, 나리. 이 결정, 후회하지 않을 것이오.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				Notification_Skill(true, 25, SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "나는 이 목걸이를 처음 보는 돈 많은 부랑자에게 팔려고 산 게 아니오! 이건 내 아내에게 줄 선물이니, 더 이상 이 문제로 말하지 마시오. 내가 사람들을 불러내기 전에 당장 내 앞에서 꺼지시오!";
				link.l1 = "신사의 합의를 거부한다면, 내가 원하는 것을 덜 문명적인 방법으로 취할 수밖에 없겠군.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				Notification_Skill(false, 25, SKILL_COMMERCE);
			}
		break;
		
		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "아르... 이 건방진 놈아... 네 유치한 협박 따위가 날 겁줄 거라 생각하나? 하! 네가 누구를 상대하는지 전혀 모르는군!";
				link.l1 = "네가 누구든 상관없어. 그냥 목걸이 내놓으면 난 떠날 거야. 아니면, 너한테 아무 의미도 없는 장신구 때문에 정말 죽을 각오가 된 거냐?";
				link.l1.go = "Captain_4_leadership_2";
				notification("Check passed", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "나는 이런 녀석이랑 흥정하려고 이 목걸이를 산 게 아니야! 이건 내 아내에게 주려고 산 선물이었고, 네가 끼어들 자리가 아니지. 우리가 내쫓기 전에 당장 꺼져라!";
				link.l1 = "순순히 내놓지 않겠다면, 힘으로 빼앗아 가겠다.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Skill not high enough (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "저주받을 그 목걸이도, 너도 다 저주해주마! 가져가. 가져가고, 내가 마음 바꾸기 전에 썩 꺼져.";
			link.l1 = "현명한 결정이오! 잘 가시오.";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+", 당신 덕분에 내 마음에 다시 기쁨이 찾아왔어요! 당신은 목걸이뿐만 아니라 내 영혼의 한 조각까지 돌려주셨군요. 당신의 고귀함은 존경받아 마땅하며, 당신의 용맹함을 내가 만나는 모든 이들에게 꼭 전하겠다고 약속하겠습니다!";
			link.l1 = "부디, 아가씨, 명예를 위해 돌려준 게 아닙니다. 당신의 미소만이 내가 진정으로 바라는 보상이에요.";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "당신은 정말 겸손하시군요, "+pchar.name+". 하지만 제발, 이 더블룬 상자를 받아주십시오. 당신이 제 선물을 받아주셨다는 사실만으로도, 저는 당신께 진정으로 합당한 감사를 드렸다고 느낄 수 있을 것입니다.";
			link.l1 = "부탁이오, 마드모아젤, 더 이상 고집하지 마시오. 당신의 따뜻한 말이 어떤 두블룬 상자보다 내게 더 소중하오.";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "그것이 당신께 평안을 준다면, 마드모아젤, 선물은 받겠소. 하지만 알아두시오, 나는 보상을 바라고 이런 일을 한 것이 아니오. "+GetSexPhrase("그대의 인정","그대의 감사")+" 이 더블룬들보다 내게 훨씬 더 소중해.";
			link.l2.go = "Juli_24_chest";
		break;
		
		case "Juli_24_nobility":
			dialog.text = "완전히 깜빡했는데—목걸이를 훔친 사람이 누군지 알아?";
			link.l1 = "내가 아는 건, 아가씨, 상인이 지젤이라는 사람에게서 그걸 받았다는 것뿐이오. 그리고 상황을 보아하니, 그녀가 팔려는 보석이 이번이 마지막이 아닐지도 모르겠군.";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "완전히 깜빡했네—목걸이를 훔친 사람이 누군지 알고 있나?";
			link.l1 = "내가 아는 건, 아가씨, 상인이 지젤이라는 사람에게서 그걸 받았다는 것뿐이오. 그리고 정황상, 그녀가 팔 계획인 보석이 이게 마지막이 아닐 수도 있겠군.";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "지젤? 하지만 그 애는 내 하녀야! 의심은 했었지... 하지만 믿고 싶지 않았어. 가장 끔찍한 건, 제대로 벌을 줄 수도 없다는 거야. 내 비밀을 폭로할 수도 있으니, 그건 절대로 용납할 수 없어.";
			link.l1 = "그럼 어떻게 할 거야? 그냥 그녀가 계속 네 걸 훔치게 내버려 둘 거야?";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "아니, 당연히 아니지. 먼저, 그 여자가 더 이상 내 근처에 없도록 할 거야. 그다음에 벌을 주되, 마치 다른 데서 벌이 내려진 것처럼 보이게 방법을 생각할 거야.";
			link.l1 = "여인의 교활함은 위험한 무기요, 특히 그대처럼 세련되고 예리한 이의 손에 쥐어지면 더욱 그러하오. 내 생각에 그대의 하녀는 이미 승부가 끝났다는 사실조차 모르고 있을 것이오—그것도 자기에게 불리하게 말이오.";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "아, 선장님... 속임수를 쓰고 싶진 않지만... 때로는 꾀만이 유일한 길일 때도 있소.";
			link.l1 = "그래, 줄리. 너를 두고 떠나기 싫지만, 의무가 날 부르고 있어. 내 선원들을 내가 아니면 누가 돌보겠어?";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "다시 만날 때까지, "+pchar.name+". 우리 항구에 자주 들러 주십시오. 우리 도시는 정말로 부족합니다\n "+GetSexPhrase("그대처럼 고귀하고 용감한 이들.","그대처럼 마음이 고귀하고 용기가 대단한 숙녀분들.")+"";
			link.l1 = "과찬이십니다, 아가씨. 당신의 아름다운 도시에 다시 올 기회를 절대 놓치지 않겠다고 약속드리죠. 다음에 또 뵙겠습니다.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;
		
		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+"! 이런 뜻밖의 만남이군! 아직도 바다를 정복하고 있나?";
						link.l1 = "만나서 반갑소, 아가씨. 나는 할 수 있는 한 잘 버티고 있소만, 바다는 여전히 변덕스럽게 굴고 있소. 그리고 그대는—조금은 평온한 시간을 보내고 있소?";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "아, 선장님 "+pchar.lastname+", 다시 만나서 정말 반갑소! 모든 일이 잘 되고 있기를 바라오?";
						link.l1 = "나도 반갑소, 마드모아젤. 사업이란 언제나 시간과 노력이 드는 법이지만, 이런 만남이 하루를 환하게 밝혀주지. 그쪽은 요즘 어떻게 지냈소?";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Captain "+pchar.lastname+", 또 돌아왔군? 우리 초라한 마을에서 아직도 네가 금화 몇 닢에 팔아먹지 않은 사람이 남아 있단 말이냐?";
						link.l1 = "아가씨, 당신의 마음은 이해하지만, 나는 옳다고 믿는 대로 행동했소. 때로는 올바른 결정이 상처를 주기도 하니, 당신을 아프게 한 것이 유감이오.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Captain "+pchar.lastname+", 또야? 네 탐욕이 그렇게 끝이 없어서 우리 마을을 가만두지 못하고 다음 희생자를 노리는 거냐?";
						link.l1 = "아가씨, 내 행동이 당신께 상처를 준 것 같아 미안하오. 하지만 나는 내 양심에 따라 행동했소.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "요즘은 모든 게 조용하고 평온합니다—아무도 이 평화를 깨지 않지요. 우리 항구에 자주 들러 주십시오, 선장님. 상점이든 그 밖이든, 원하시는 건 뭐든 여기서 찾으실 수 있을 겁니다.";
			link.l1 = "고마워요, 아가씨. 앞으로 더 자주 들르도록 할게요. 당신네 마을엔 아직도 기분 좋은 놀라움이 많이 남아 있을 것 같아요.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
		case "Juli_33":	
			dialog.text = "당신 덕분에, 선장님, 이제 제 나날이 훨씬 평화로워졌습니다. 꼭 다시 찾아와 주시길 바랍니다.";
			link.l1 = "물론이죠, 아가씨. 당신네 마을은 언제나 가장 좋은 인상을 남깁니다. 다음에 또 뵙겠습니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Captain "+pchar.lastname+", 또 만났군. 신기하지 않아?";
					link.l1 = "오늘은 운명이 우리 만남에 미소를 짓는 것 같군요, 아가씨.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Captain "+pchar.lastname+", 또다시 우리의 길이 교차한 것 같군.";
					link.l1 = "정말 그렇소, 아가씨. 다시 뵙게 되어 기쁩니다.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "우리가 좀 자주 마주치는 것 같군, 선장. 아니면 이미 배신한 사람들에게서 떨어질 수가 없는 건가?";
					link.l1 = "아가씨, 우리의 만남은 순전히 우연이지만, 당신의 씁쓸함은 이해합니다. 언젠가 당신도 내 이유를 이해하게 되길 바랄 뿐입니다.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "지금 또 뭘 원하지? 설마 네 운이 그렇게까지 나빠서 우연히 만난 건 아니겠지. 아니면 네 수치를 다시 떠올리게 하려고 온 거냐?";
					link.l1 = "아가씨, 방해하거나 지난 상처를 건드릴 생각은 전혀 없었소. 이번 만남은 정말 우연이오.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;

		
		
		
		
		
		
		
	}
}