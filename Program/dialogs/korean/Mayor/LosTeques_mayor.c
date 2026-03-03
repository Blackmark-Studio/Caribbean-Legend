void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("감히 여기에 오다니?! 대담하군...","어떻게 저런 바보들이 적의 침입을 허락할 수 있단 말인가?! 도무지 이해할 수 없군...","흠, 내 경비병들이 아무 쓸모가 없구려. 어떤 바보가 내 관저를 돌아다니고 있다니..."),LinkRandPhrase("뭘 원하지, 이 자식아?! 내 병사들이 이미 너를 추적했으니 도망칠 수 없을 거다."+GetSexPhrase(", 더러운 해적놈"," 더러운 해적")+"!","더러운 살인자, 내 저택에서 당장 꺼져라! 경비병들아!!!","나는 너 따위가 두렵지 않아, 이 자식아! 넌 교수형을 당할 거야, 절대 도망치지 못해..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("병사들은 비용이 들지 않소...","그들이 나를 절대 잡지 못할 것이오."),RandPhraseSimple("입 다물라, "+GetWorkTypeOfMan(npchar,"")+", 아니면 네 혀를 잘라서 네 목구멍에 쑤셔 넣어 주겠다...","내가 충고하지, 친구야: 조용히 앉아 있으면 하루 더 살 수도 있을 거야..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "내 관저에 적이 들이닥쳤다! 경보!!!";
				link.l1 = "제기랄!";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+" 나리. 저는 "+GetFullName(npchar)+", 로스트-테케스 광산의 사령관이며, 그 광산은 소유주가 "+NationKingsName(npchar)+". 이제, 방문 목적을 말씀해 주시겠소, "+GetAddress_Form(NPChar)+".";
				link.l1 = "여기는 처음이라 이 정착지와 그 법에 대해 더 알고 싶소...";
				link.l1.go = "info";
				link.l2 = "그저 인사만 드리려 했습니다, 저는 이제 떠나겠습니다.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "또 오셨습니까, 나리? 또 무엇을 원하십니까?";
			link.l1 = "별일 아니오. 나는 떠나겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "나는 그런 규율을 존중하오. 흥미가 그리 많으시니, 그럼 자세히 알려드리겠소.\nLos-Teques 광산은 스페인 왕실의 소유요. 우리는 여기서 은과 금 광석, 그리고 은과 금 덩어리를 채굴하오. 모든 금과 은은 스페인에 속하며, 구세계로 운송되오.\n광산은 잘 경비되고 있소. 항상 정예 스페인 병사 부대가 주둔하고 있지. 해적들이 여러 차례 우리 광산을 약탈하려 했으나, 결과는 언제나... 그들만 나빴소.\n보시다시피, 여기는 작은 마을이오. 선술집과 상점이 있소. 그곳에서 금과 은 주괴를 좋은 값에 살 수 있소. 또한, 우리 병참장교이자 상점 상인이 흥미로운 금속과 광석도 팔 수 있소.\n우리 일꾼 대부분은 죄수들이지만, 흑인 노예도 소수 있소. 보시다시피, 우리는 항상 새로운 인력이 필요하오. 이 저주받은 죄수들 중 매일 최소 한 명은 죽어나가니 말이오.\n그러니 노예를 데려오면, 우리는 그 대가로 금덩이를 교환해 주겠소. 이런 일은 수석 기술자에게 문의하시오. 그는 갱도 안에 있소.\n여기서는 얌전히 행동하시오. 결투나 싸움을 벌이거나, 무언가를 훔치려 하지 마시오. 특히 금이나 은은 절대 안 되오. 우리는 감옥은 없지만, 군사재판은 있소.\n이상 설명은 이 정도요. 이 간단한 규칙만 따르면 아무 문제 없을 것이오. 광산 내에서는 자유롭게 다닐 수 있소. 선술집도 꼭 들러보시오. 내 허락 하에... 특별한 서비스를 제공하오. 환영하오!";
			link.l1 = "감사하오!";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "강도라니!!! 그건 용납할 수 없소! 각오하시오, "+GetSexPhrase("친구","소녀")+"...";
			link.l1 = LinkRandPhrase("제기랄!","카라암바!!","제기랄!");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
