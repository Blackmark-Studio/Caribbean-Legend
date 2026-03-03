void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("마을에 경보가 울렸소. 모두가 자네를 찾고 있네! 내가 자네라면 여기 오래 머무르지 않을 것이오.","온 마을 경비대가 너를 찾으려고 마을을 샅샅이 뒤지고 있어. 나도 바보는 아니니 너랑 말할 생각 없어!","도망쳐, 이봐, 군인들이 널 갈기갈기 찢기 전에..."),LinkRandPhrase("뭘 원하지, 이 악당아?! 지금 당장 도시 경비대가 네 뒤를 쫓고 있다. 더 이상 못 도망갈 거다, 더러운 해적놈아!","내 집에서 나가, 살인자야! 경비병들!!","난 너 따위 안 무서워, 이 건달아! 곧 네놈은 교수형을 당할 거다, 도망 못 간다..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("헤, 난 경보 따윈 별로 신경 안 써...","그들이 나를 잡을 가능성은 없어."),RandPhraseSimple("입 다물어, "+GetWorkTypeOfMan(npchar,"")+", 아니면 네 더러운 혀를 뽑아버릴 거야!","헤헷, "+GetWorkTypeOfMan(npchar,"")+", 너도 해적을 사냥하고 싶다고! 이봐, 진정하면 살아남을 수 있어..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! 처음 뵙는군, 나리. 감히 선장이라고 추측해도 되겠소... 내가 맞췄나? 내 이름은 "+GetFullName(npchar)+", 그리고 내 상점은 당신을 위해 열려 있소. 금, 은, 그리고 호기심 많은 이의 흥미를 끌 만한 것들이 더 많이 있지.";
				Link.l1 = "알겠소. 나는 "+GetFullName(pchar)+". 만나서 반갑소, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", 나리! 다시 제 상점에 오셔서 반갑습니다. 금괴를 구입하시겠습니까? 아니면 오늘은 광물에 관심이 있으신가요?";
				link.l1 = "물건 좀 보여주시오, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "아니요, 아무것도 필요하지 않습니다, "+npchar.name+". 그냥 인사나 하려고 들렀소.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "저도 그렇소, 나리. 제 상품 한번 보시겠습니까? 분명히 관심 가질 만한 물건이 있을 것이오.";
			link.l1 = "여기는 처음 와보는 곳이라 이 정착지에 대해 좀 더 알고 싶소.";
			link.l1.go = "info";
			link.l2 = "그럼 판매하는 물건을 보여주시오.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "우리 작은 마을은 금광 덕분에 세워졌소. 그곳에서 금광석, 은, 금덩이를 채굴하지. 가끔은 보석도 나오고. 예전에는 여기 주둔군만 있었는데, 친절한 인디언들과 몇몇 백인 정착민들이 합류했지\n이그나시오 오르테가가 선술집을 지어 우리 삶이 조금 더 밝아졌소. 온갖 모험가들이 우리를 털겠다는 어리석은 생각으로 이곳을 찾아오지. 법정이 없어서, 마을 한가운데서 멍청이 몇 놈을 교수형에 처한 뒤로는 그런 자들이 줄었소\n금광석은 병사들과 친절한 인디언들의 호위 아래 배로 보내지지만, 금덩이는 바로 이 가게에서 살 수 있소\n게다가 가끔 아주 흥미로운 광물도 취급하니, 시간 나면 들르시오. 항상 새로운 물건을 들여놓으니.";
			link.l1 = "흥미로운 이야기 감사합니다! 기억해 두겠습니다.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("대낮에 강도질이라니!!! 여기서 무슨 일이 벌어지는 거지?! 잠깐, 기다려, 친구...","이봐, 거기서 뭐 하는 거야?! 나 털려고 하는 거냐? 이제 큰일 났다...","잠깐, 지금 뭐 하는 거야? 결국 도둑이었군! 여기서 끝이다, 이 자식아...");
			link.l1 = LinkRandPhrase("악마다!!","카라암바!!","아, 젠장!");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
