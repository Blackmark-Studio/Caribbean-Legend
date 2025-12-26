void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
		
		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "무슨 용건이오, "+GetAddress_Form(NPChar)+"? 미안하지만, 지금은 새 주문을 받지 않아. 일이... 너무 많거든...";
			link.l1 = "그런가? 최근에 카드놀이에서 아주 귀중한 걸 잃었다고 들었는데, 사실인가?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "글쎄, 자랑하러 온 거라면 줄 서. 너 없이도 비웃고 싶어하는 놈들 충분히 많으니까. 하지만 그 누구도 나를 도와주겠다고 한 적은 없어. 내 운명은 실낱같이 매달려 있고, 전적으로 하비에르 카스티요에게 달려 있어. 사람들은 내 불행을 비웃는 것밖에 관심이 없지.";
			link.l1 = "나는 남의 불행을 비웃는 그런 사람이 아니야. 어떻게 된 일인지 말해 봐. 내가 도와줄 수도 있잖아.";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "도움? 누가 너한테 그런 걸 줘야 하지? 나는 절대 안 줄 거다. 네 행복도, 불행도 네가 직접 만드는 거야... 그러니 피해자인 척 그만하고, 그냥 네가 한 일의 결과를 받아들여. 그게 당연한 거니까.";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "그날 저녁이 이렇게 치명적일 줄은 몰랐지. 에우헤니오 데 라 토레 제독님이 직접 내게 큰 주문을 맡긴 뒤, 럼 한 잔 하려고 선술집에 들렀을 뿐이었어. 그런데 꽤 취한 채로 카드나 한 판 하자며 자리에 앉았지. 그때 하비에르가 나를 노리기 시작했어\n처음엔 운이 내 편이었지 – 제법 큰돈도 땄고. 하지만 운을 믿기 시작하자 상황이 완전히 뒤바뀌었어. 하비에르는 내 잔에 럼을 계속 따라줬고, 나는 계속 졌지. 처음엔 가진 돈을 다 잃고, 그다음엔 자재비로 따로 챙겨둔 돈, 그리고 결국엔 내 전 재산까지 다 날렸어\n이미 얼마나 잃었는지 깨달았을 땐, 물러설 수 없을 만큼 늦었지. 오직 한 가지 생각뿐이었어 – 어떻게든 다 되찾아야 한다는 집착. 그러다 내 책을 걸었지. 그 악당 하비에르는 그걸 겨우 오천 페소로 쳤어\n물론 그 책은 훨씬 더 비싼데, 흥분에 눈이 멀어서 그냥 받아들였지. 그리고... 그 다음은 이미 알고 있겠지. 난 졌어. 이런 일은 처음이야. 내 생각엔 그 자식이 뭔가 약을 탄 것 같아.";
			link.l1 = "그런데, 내가 어떻게 도와줘야 한단 말이오? 자네가 직접 테이블에 앉았고, 직접 재산을 걸었으며, 직접 전부 잃었잖아. 이제 와서 결과를 받아들이기 싫은 건가? 그리고 그 책이 대체 뭐가 그리 귀해서 그렇게 애통해하는 거지?";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "이 책은 내가 가진 것 중 가장 소중한 것이오. 수세기 동안 대장장이 스승에서 제자에게 전해진 비밀이 담겨 있지. 내 대장간의 심장이자, 내 기술의 영혼이라네. 이미 잃어버린 것에 대해서는 마음을 정리했소. "+GetAddress_Form(NPChar)+", 하지만 그 책을 잃은 걸 어떻게 받아들여야 하지? 하비에르에게 몸값으로 오천 페소를 제안했어\n그 책을 되찾으려고 빚을 질 각오까지 했지. 그런데 그가 뭐라고 했는지 알아? 십만 페소를 달라고 하더군! 십만이나, "+GetAddress_Form(NPChar)+"! 그런 돈은 없어. 그런데도 그자는 값을 깎아주지도 않고 할부로도 안 된다고 해. 내가 애원까지 했는데... 그냥 비웃더군. 보아하니 당신은 "+GetSexPhrase("용감한 사내, 뱃사람... 어쩌면 선장일지도 모르지. 그리고 네 무기도 그냥 장식으로 달려 있는 건 아니군","보통 여자가 아니고, 분명 어떤 남자에게든 접근할 수 있는 사람이야")+"\n제발 하비에르와 이야기해 주십시오. 어쩌면 당신 말이라면 듣고 빚 상환을 미뤄줄지도 모릅니다. 이 책이 없으면... 제 삶엔 아무 의미가 없습니다. 대신, 제가 다시 일어서게 되면 언제든 좋은 가격에 질 좋은 재료를 팔아드릴 수 있고, 어쩌면 선장님을 위해 특별한 것도 만들어드릴 수 있습니다.";
			link.l1 = "뭐, 이야기하는 건 어렵지 않지. 어떻게 될지 두고 보자고. 하지만 먼저 내 소개부터 하지. 내 이름은 "+GetFullName(pchar)+", 내 배의 선장이오.";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("그리고 나는 세바스티안 코르도바다...","여자가 자기 배의 선장이라니? 그런 이야기는 들어본 적 있지만, 실제로 만나서 대화해본 적은 없어.")+" 만나서 반갑소, 선장 "+pchar.lastname+". 그리고 고맙소. 요즘은 남의 불행을 비웃는 자들이 도와주려는 이들보다 더 쉽게 보이오. 내 책이 정말 돌아온다면 맹세하오: 다시는 도박 따위 하지 않겠소.";
			link.l1 = "아직 나한테 고마워할 일 없어. 먼저 내 일부터 처리하고, 시간이 남으면 하비에르하고 얘기하지.";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "안타깝지만, 자네가 너무 늦은 것 같군. 하비에르는 내가 생각했던 것보다 훨씬 빨랐어\n이미 그 책의 구매자를 찾았지 – 프랑스의 명장 총기 제작자인 에티엔 르누아르야. 만약 제독이 내 실수로 그런 보물이 프랑스인의 손에 들어갔다는 걸 알게 되면... 내 목이 날아갈 거야. 감옥살이는 오히려 가벼운 벌이지.";
			link.l1 = "흠... 좋아. 네 문제 바로 해결해 줄게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "Captain "+ pchar.lastname +"! 하비에르와 얘기해 봤어? 소식 있어?";
			link.l1 = "아직 아니야, 하지만 지금 바로 선술집으로 가는 중이야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "내 말은 끝났어"+GetSexPhrase("","")+". 그리고 꽤 성공적으로 끝났지. 하비에르는 급히 이 세상을 떠났지만, 그 전에 네 책을 돌려줬어. 여기 있다.";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 이게 나한테 얼마나 큰 의미인지 상상도 못 할 거야! 네 덕분에 이제 모든 주문을 다 처리할 수 있어, 심지어 제독 일을 맡아도 문제없지! 아쉽게도 돈은 없지만, 그래도 널 위해 보상을 준비했어\n자, 이 흉갑을 가져가. 원래는 어떤 돈을 위해 만든 거지만, 그 양반은 좀 기다려도 되겠지. 그리고 네가 직접 뭔가 만들 생각이 있다면 쓸 만한 재료도 좀 있어.";
			link.l1 = "감사합니다, "+npchar.name+", 정말 후하시군요!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "그리고 자네가 재료가 필요하면 언제든 들르게. 내 물자는 한 달에 한 번씩 들어오니, 항상 자네에게 쓸 만한 게 있을 거야 – 게다가 값도 좋지. 나는 약속을 지키는 사람이네.";
			link.l1 = "반드시 그럴게! 자, "+npchar.name+", 몸조심해. 난 이만 가볼게, 할 일이 있어서.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "Captain "+ pchar.lastname +"! 하비에르와 이야기해 봤어? 소식 있어?";
			link.l1 = "있잖아... 그 책은 내 손에 있었어. 하지만... 사정이 그렇게 돼서 팔려버렸지.";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "뭐라고?! 너... 그걸 팔았다고?! 내 책을?!";
			link.l1 = "카드 게임에서 잃어버린 그 책 말이오. 하비에르가 약속했던 그 프랑스인에게 팔렸소.";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "하지만... 이제 끝장이야. 책은 프랑스 놈들 손에 있고, 제독의 명령도 이행 못 했어... 내 인생은 망했어... 나... 난 끝장이야!";
			link.l1 = "스스로 궁지에 몰렸군. 이번 일에서 좋은 교훈을 얻길 바라지. 잘 가라.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\English\tavern\Igroki v Tavernah-01.wav"); 
			dialog.text = "이봐, "+GetSexPhrase("선원","귀요미")+", 카드로 운을 시험해 볼래? 자리에 앉아, 여기 판돈은 순하니까... 적어도 초보자한테는 말이야.";
			link.l1 = "내가 찾던 사람이 바로 너라는 느낌이 드는군. 예전에 세바스티안도 이렇게 꾀어서 뼛속까지 털어먹었지, 안 그래? 나는 그의 책을 되찾으러 왔다.";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_2":
			dialog.text = "좋아, 훌륭하군. 십만 내놓으면 가져가도 돼. 나한텐 그 책 필요 없어, 집게하고 망치도 구분 못 하거든.";
			link.l1 = "오천 줄게 – 그건 네가 대장장이를 이겼을 때 네가 직접 정한 값이야.";
			link.l1.go = "OZ_Shuler_3";
		break;
		
		case "OZ_Shuler_3":
			dialog.text = "하! 나를 바보로 아나? 그 책의 진짜 가치쯤은 나도 잘 알고 있지. 십만, 한 푼도 깎지 않아. 아니면 프랑스 놈들한테 넘기겠어 – 돈이라면 걔네는 거리낌 없으니까.";
			link.l1 = "네가 스페인 설계도를 프랑스에 팔아넘기는 걸 당국이 모른 척할 거라고 생각하나? 그 사실을 알게 되면 제독이 분노할 거다.";
			link.l1.go = "OZ_Shuler_4";
		break;
		
		case "OZ_Shuler_4":
			dialog.text = "아, 그만 좀 해. 당국은 책 한 권에 신경 쓸 여유 없어, 지금도 골치 아픈 일 투성이니까. 그리고 제독 말이지? 그래, 프랑스 놈들 진심으로 증오하긴 해. 하지만 난 그 자식 기다릴 생각 없어 – 그 정도 돈이면 신세계 어느 식민지에서도 환영받는 손님이 될 테니까.";
			link.l1 = "그럼 거래를 하자. 네 돈은 받게 될 거야, 하지만 당장은 아니지. 대장장이가 빚을 할부로 갚을 거고, 오늘 그 책은 내 선장으로서의 명예를 담보로 그에게 돌아간다. 너한테는 달라지는 게 없어 – 그는 계속 돈을 갚을 거고, 너는 페소 한 푼도 잃지 않을 거야.";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "내 말이 안 들리나 보군. 분명히 말했잖아 – 지금 당장 돈이 필요하다고. 일주일 뒤도, 한 달 뒤도, 대장장이가 돈을 모을 때도 아니고, 바로 지금이야. 이 썩은 섬에서 최대한 빨리 떠날 생각이거든. 그러니 전액을 지금 내 손에 쥐여주든가, 아니면 그 책은 프랑스 놈들한테 넘길 거다. 그러면 네 선장 체면은 제독의 형리한테 잡혀다 바치게 되겠지.";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "이렇게 해보지: 한 판 하자고. 내 십만 대 책 한 권. 네가 이기면 이 섬을 부자로 떠날 수 있어. 네가 지면 내가 그 책을 가져간다. 아니면, 혹시 패 한 번 만져본 적도 없는 놈들이랑만 놀아?\n";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;
		
		case "OZ_Shuler_6_No_Money":
			DialogExit();
			Notification_Money(false, 100000, "peso");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			Notification_Skill(true, 30, SKILL_SNEAK);
			}
			else
			{
			Notification_Skill(false, 30, SKILL_SNEAK);
			}
		break;
		
		case "OZ_Shuler_6":
			dialog.text = "하! 나는 부자가 될 필요 없어 – 이미 부자거든! 나한테 돈을 잔뜩 가져다줄 일을 왜 굳이 위험을 감수해야 하지?";
			link.l1 = "오, 오, 하비에르 카스티요 본인이 놀기가 두려운가? 나는 여기서 이렇게 생각했는데\n"+GetSexPhrase(""," 너")+", 너는 그냥 술 취한 얼간이들 등쳐먹는 사기꾼이 아니라, 노련한 선수였지.";
			link.l1.go = "OZ_Shuler_7";
			Notification_Money(true, 100000, "peso");
			Notification_Skill(true, 30, SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "난 무섭지 않아, 그냥 이미 필요한 건 다 가지고 있는데 굳이 테이블에 앉을 이유가 없다고 생각할 뿐이야.";
			link.l1 = "아, 이봐, 처음으로 누가 카드 안 봐주니까 벌벌 떨고 있는 거 다 보여. 내가 맞혀볼까? 이렇게 급하게 나가려는 건 창피해서지? 여기 있는 사람들 다 이미 네가 술 취한 바보보다 센 놈은 못 이긴다는 거 알아챘거든?";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "감히 어디서 까불어?! 너랑 같은 식탁에 앉으려 하지도 않는 놈들도 내가 때려눕혔어! 우린 배 한 척 살 만큼 판돈도 굴렸고, 플레이어마다 그런 오만한 선장 하나씩 상대했지! 한 판 붙자. 카드 한 장에 오천, 각자 십만씩, 돈 떨어지는 놈이 지는 거다. 누가 누구를 이기는지 보자고.";
			link.l1 = "말은 그만하고, 행동부터 하자. 거래지.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "악마야! 그럴 리가...";
			link.l1 = "뭐야, 남이 이기니까 별로 재미없지?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "너 사기꾼이잖아! 내가 아무것도 못 본 줄 알아? 절대 네가 날 속이게 두지 않을 거야! 차라리 널 갈기갈기 찢어버리겠다.";
			link.l1 = "속임수라고? 하하! 져본 적이 없어서 그런 소리 하는 거지, 친구. 그렇게 죽고 싶어서 안달이 났다면 내가 도와주지. 무기 들어!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "하! 그래, "+GetSexPhrase("친구","귀요미")+", 털리는 기분이 어떤가"+GetSexPhrase("","") +"? 오만은 두 번째 행복이라던데, 너한테는 해당 안 되겠군.";
			link.l1 = "자만하지 마라. 그냥 운이 좋았을 뿐이야.";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "지는 놈들은 항상 그렇게 말하지. 뭐, 너도 한 판 했으니\n"+GetSexPhrase("","") +" – 네가 졌다"+GetSexPhrase("","") +", 너무 기분 나빠하지 마라. 만약 또다시 십만을 찾게 된다면, 다시 한 번 운을 시험해 봐도 되지... 하지만 결과가 달라질 것 같진 않군...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "안녕하세요, "+GetAddress_Form(NPChar)+". 무슨 일로 찾아오셨소?";
			link.l1 = "안녕하시오. 나는 선장이오 "+GetFullName(pchar)+", 그리고 Javier Castillo에 대해 당신과 이야기하고 싶소.";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "흠... 그 악당이 너한테도 돈을 빚졌다면, 긴 줄을 설 각오를 해야 할 거다. 하비에르는 빚을 갚는 데 전혀 서두른 적이 없어. 하지만 만약 그 녀석이 돈을 손에 넣는다면, 나한테 먼저 갚게 될 거야 – 이미 다른 선택지는 없다는 걸 확실히 해뒀거든.";
			link.l1 = "다행히도 나는 그 사람의 채권자가 아니오. 그가 당신에게 얼마나 빚졌소? 그리고 구체적으로 어떤 조치를 취했소?";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "그 자의 빚 전체는 십오만 페소다. 지금까지 만 페소만 갚았는데, 그걸로 충분하다고 생각한 모양이지. 하지만 내가 금방 그게 착각이라는 걸 알게 해줬지. 내 부하들이 추가로 이만 페소를 받아냈다. 나머지는 일주일 안에 갚아야 하고, 기한이 거의 다 됐어. 다행히도 곧 책을 팔아서 꽤 큰돈을 받을 거라는 소문을 들었지.";
			link.l1 = "정말로 그가 너한테 돈을 갚을 거라고 생각해? 내가 보기엔 진지하게 기대하지 않는 게 좋겠어. 하비에르는 돈만 손에 쥐면 바로 여기서 도망칠 거라는 걸 숨기지도 않아.";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "그 점은 알고 있습니다, 선장님. 안심하십시오, 이미 그가 돈을 내지 않고는 도망칠 수 없게 해두었습니다.";
			link.l1 = "상황을 잘 통제하고 있군. 하지만 경험상, 조금 더 조심하는 게 나쁠 건 없지. 나는 말이지, 이런 일에 좀 전문가거든."+GetSexPhrase("","ess")+" 빚을 받아오는 일입니다. 제가 대신 나서게 해주신다면, 돈을 되찾아드릴 수 있습니다.";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "유감이오, 선장님. 이 빚을 회수하는 데 이미 너무 많은 비용이 들고 있어서, 당신의 서비스까지 지불할 여유가 없소...";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", 그건 걱정하지 않아도 돼. 나도 이 일에 관심이 있으니, 무료로 도와줄게.";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "실례지만, 정확히 어떤 일에 관심이 있으십니까?";
			link.l1 = "그 녀석이 카드판에서 부리는 몇몇 수작은 그냥 넘어갈 수 없는 것들이라고만 해두지.";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "글쎄, 나한테 아무런 비용이 들지 않는다면 굳이 거절할 이유는 없지. 다만 한 가지, 선장 – 너무 지나치게만은 하지 말아주게. 그 악당이 빚을 갚기도 전에 저 세상으로 가버리면 내겐 아무 소용도 없으니.";
			link.l1 = "걱정 마, Felipe. 내가 신중하게 행동할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! 이렇게 빨리 해결한 건가?";
			link.l1 = "아직은 아니오. 하지만 내가 노력하고 있소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "아, "+GetSexPhrase("선장","귀요미")+" 건방진 놈! 또 왔냐? 뭐야, 돈 몇 천 더 잃고 싶어서 온 거냐?";
			}
			else
			{
				dialog.text = "또 왔어? 분명히 말했지: 돈을 내놓든가 아니면 꺼져.";
			}
			link.l1 = "말투 좀 고쳐, 하비에르. 그리고 돈주머니 꺼내. 나 그냥 온 거 아니야. 펠리페 알라르콘에게 진 빚, 잊은 건 아니겠지? 이제 내가 그 사람 대신 왔다. 선택해. 지금 당장 빚 갚을 건지, 아니면 네가 저 세상 간 다음에 네 주머니에서 돈을 뒤져야 하는지.";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "젠장할! 지금 거래 중인 거 안 보여? 몇 시간 후에 다시 와라 – 그때 얘기하지.";
			link.l1 = "내 말 못 들은 것 같군. 분명히 말했잖아. 지금 당장 돈이 필요하다고. 일주일 뒤도, 한 달 뒤도, 네가 돈을 겨우 모았을 때도 아니고, 바로 지금이야. 12만 페소, 한 푼도 깎지 않아. 책은 5천으로 쳐줄 용의가 있어.";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("이 더러운 놈","이 망할 놈아")+"! 나를 그렇게 쉽게 상대할 수 있다고 생각한다면, 그게 네 쓸모없는 인생에서 가장 큰 실수다.";
			link.l1 = "두고 보자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "정말 장관이군... 인정할 수밖에 없네, "+GetAddress_Form(NPChar)+", 정말 즐거웠소. 검을 아주 훌륭하게 다루는구려. 내 소개를 하겠소 – "+GetFullName(npchar)+". 그리고 이 불쌍한 친구가, 내가 틀리지 않았다면, 하비에르 카스티요인가?";
				link.l1 = "그래, 바로 그 사람이야. 그리고 나는 선장이오 "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "정말 장관이군... 인정할 수밖에 없네, "+GetAddress_Form(NPChar)+", 정말 큰 기쁨을 주었군. 칼 솜씨가 대단하네. 상황이 이렇게 돌아가다니 참 우습지 – 내가 그토록 먼 길을 온 책이 이렇게 뜻밖에 주인이 바뀌었으니 말이야. 하지만 빈손으로 여기서 떠나지는 않기를 바라네.";
				link.l1 = "흠... 그 책을 얼마로 평가하십니까?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "보시다시피, 선장님, 저는 한 권의 특별한 책을 위해 꽤 먼 길을 왔습니다... 그런데 지금 그 책이 선장님 손에 있는 것 같군요. 진심으로 우리가 합의에 이를 수 있기를 바랍니다 – 빈손으로 이곳을 떠나고 싶지는 않으니까요.";
			link.l1 = "흠... 이 책의 가치를 얼마나 쳐 주겠소?";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "오, "+GetAddress_Form(NPChar)+", 나는 진정으로 희귀한 것들의 값을 잘 알지. 팔만 페소다. 이보다 후한 금액은 없을 것이니, 내 말을 믿으라. 이런 제안을 다시는 받기 힘들 거야.";
			link.l1 = "음, 그 책이 정말 귀한 건 사실이고, 내가 부탁한 것도 인정하지"+GetSexPhrase("","") +" 순전히 호기심에서 물어본 것뿐이오. 나는 한 인간의 운명을 거래할 생각이 없소. 유감이오, 나리, 거래는 없을 것이오 – 이 책은 반드시 정당한 주인에게 돌아가야 하오.";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "우스운 금액이군. 이 책에는 최고의 대장장이 장인들의 비밀이 담겨 있지. 십오만 페소다 – 동의하든지, 아니면 주인에게 돌려보내겠다. 흥정은 없다.";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "부디, 그렇게 급하게 거절하지 마시오. 나는 이 일을 위해 먼 길을 왔소. 그 사내를 처리한 솜씨에 대한 존경의 표시로, 순수하게 십만을 드릴 준비가 되어 있소.";
			link.l1 = "나는 할 말은 다 했어. 이제, 실례하겠소, 가봐야 하오.";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 신뢰해 주셔서 감사하지만, 십오만 페소라니 – 그건 가격이 아니라 말도 안 되는 소리요. 이 거래를 우스꽝스럽게 만들지 맙시다. 십만 페소면 합리적인 금액이니, 그 정도로 합의합시다 – 이 책에 그 이상을 줄 사람은 없소.";
			link.l1 = "우리가 서로 뜻을 맞추지 못한 것 같군. 뭐, 이 대화를 계속할 이유도 없지. 안녕히 가시오, 나리.";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "잠깐! 알겠어, 네가 이겼다. 십오만. 거래하는 거지?";
			link.l1 = "올바른 선택을 해서 다행이야. 책은 네 거다. 이 책만 있으면 카리브 해에서 최고의 장인이 될 수 있을 거라고 생각해.";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 이 책이 없어도 나는 누구에게도 뒤지지 않았지. 하지만 이렇게 희귀한 전리품을 얻으니 솔직히 기분이 좋군. 이제 실례하겠소 – 이 책이 소문만큼 대단한지 어서 직접 확인해 보고 싶으니.";
			link.l1 = "그럼, 더 붙잡지 않겠소. 안녕히 가시오.";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "이봐, 이봐, 이게 무슨 쓰레기야? 우리 보물상자 털고 도망칠 생각이었어? 큰 착각했구나, 이놈아. 이제 우리가 직접 너를 그 상자에 쑤셔 넣고 뚜껑을 못질해버릴 거다!";
			}
			else
			{
				dialog.text = "오, 이거 봐라... 여기 누가 있나? 길이라도 잃었어, 이쁜이? 보물 상자 털고 조용히 빠져나가려 했지? 큰 착각이었군, 귀여운 것. 이제 제대로 뒤져볼 거다 – 네 주머니에 뭐가 들었는지... 그리고 다른 데도 말이지.";
			}
			link.l1 = "너희 같은 한심한 벌레들에게는 말이 너무 많군. 칼이나 뽑아 봐라, 네놈이 얼마나 대단한지 보자고.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "선장님! 자비에르가 당신 덕분에 벌써 저 세상으로 갔다는 소식은 이미 들었소. 내가 너무 일찍 죽이지 말라고 부탁했었는데! 내 돈을 돌려주러 온 거겠지?";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "그래. 내가 그의 은닉처를 찾아냈는데, 거기엔 페소 10만이 들어 있었어. 그게 그가 가진 전부였지.";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "그래, 내가 그를 죽여야 했어. 하지만 먼저 나를 공격했으니 어쩔 수 없이 방어했지. 주머니는 텅 비었더군 – 동전 한 닢도 없었어. 유감스럽게도 빚을 회수하지 못했어.";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "십만... 물론 전부는 아니지만, 하비에르를 아는 내가 보기엔 그 녀석한테서 더 뽑아낼 사람은 없을 거야. 자, 고맙소, 선장. 내가 사람을 잘못 쓴 것 같군. 당신이야말로 진정한 달인이오.";
			link.l1 = "어렵지 않았소. 그럼, 이만 실례하겠소\n"+GetSexPhrase("","")+". 볼일이 기다리고 있군.";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "안녕히 가십시오, 선장님.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "You "+GetSexPhrase("악당","불쌍한 놈")+"! 내 눈을 똑바로 보면서 거짓말을 해?! 이대로 넘어갈 줄 알지 마라!";
			link.l1 = "아르그...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\Russian\Master_02.wav");
			dialog.text = "안녕, "+pchar.name+"! 자재나 상품을 구매하시겠습니까?";
			link.l1 = ""+TimeGreeting()+". 무엇을 가지고 있는지 보자.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "그리고 너에게도 인사하지, "+npchar.name+"! 제안은 고맙지만, 나는 그냥 원했을 뿐이오"+GetSexPhrase("","") +" 인사하러.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 결국 뭔가 사기로 결정했나?";
			link.l1 = "맞아. 오늘 뭐 가지고 있는지 보여 줘.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "미안하지만, 나는 벌써 떠난다.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}