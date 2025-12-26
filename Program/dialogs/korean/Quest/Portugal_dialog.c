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
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "버그다. 개발자들에게 알려라.";
		link.l1 = "그래.";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "오, 또 다른 용감한 선원이군! 네 같은 놈들 내가 잘 알지, 젠장 맞을 내 눈이 널 딱 보고 있거든, 하! 왜 그런지 물어볼래?";
			link.l1 = "다른 일에 대해 물어보겠소. 그건 자네가 이 지역... 음, 업소의 여주인에게 진 빚에 관한 것이오. 그녀가 내게 자네의 빚을 상기시켜 달라고 부탁했으니, 뭔가 조치를 취하는 게 좋을 거요. 그렇지 않으면 내일 그녀가 경비병들에게도 같은 부탁을 하게 될 것이오.";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "현지인... 아, 젠장! 요한나, 그녀가 나한테 이럴 수 없어! 정말이야? 진짜로 나를 몇 푼 때문에 감방에 쳐넣겠다고 했어?";
			link.l1 = "물론이지. 그녀가 그렇게 말했어. 내 임무는 끝난 것 같군, 잘 있어, Avendell 나리.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "잠깐! 기다려! 제발, 기다려 줘! 당신, 노련한 선장처럼 보이는데. 분명 동전 좀 있겠지, 난 빈털터리야. 우리 오래된 우정 덕분에 그 착한 바텐더만이 외상으로 내 잔을 채워주지. 내... 내 제안을 들어봐! 내 빚을 갚아주면 내가 몫을 떼어주겠어\n사업이 하나 있는데... 아주 이익이 쏠쏠한 사업이지, 젠장 내 엉덩이까지 걸고 맹세한다! 내 피 묻은 닻에 맹세하건대, 그냥 믿어봐, 선장님 - 이름이 뭐든 간에!\n작은 빚 하나만 갚아줘, 만 페소면 돼. 그러면 신세계의 모든 창관을 살 만큼 동전을 벌 기회가 생길 거야! 어때? 네가 나한테 주면, 나도 너한테 주는 거지, 정직한 놈들끼리 하는 것처럼...";
			link.l1 = "보물 약속이나 하는 누더기 녀석이군. 그런 헛소리는 집어치워라, 난 너 같은 놈한테 자선 따윈 안 해. 돈을 구해 오지 않으면 곧 요새 지하 감방에서 살게 될 거다. 잘 가라!";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "한몫 달라고? 그리고 내가 왜 술에 취한 바보 말을 믿어야 하지? 헛된 약속 때문에?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "내 말 좀 들어봐, 선장! 힉, 내가 거짓말하면 그냥 쏴 죽여도 돼! 하지만 진짜야! 생각해 봐, 내가 거짓말하는 거 잡히면, 선장 허리에 찬 멋진 칼로 내 창자를 도려내도 돼! 젠장, 그 칼 자루 값이 내 비참한 빚의 다섯 배는 될 거야! 어때? 선장은 잃을 게 없잖아!\n";
			link.l1 = "네 말은 이제 지긋지긋하다. 잘 가라.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "좋아, 휴고... 네가 하는 그 허튼소리를 믿어보는 위험을 감수하지. 하지만 명심해, 내가 돌아왔을 때 내 돈이 헛되이 쓰이지 않았다는 걸 설득하고 증명해야 할 거다. 그렇지 않으면 네 목이 위험해질 테니.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "협박할 필요 없어, 이해했어. 맹세할게, 선장! 우리 부자 될 거야! 이 빌어먹을 빚만 갚으면 다시 와, 그때 우리가... 얘기하자! 그래, 꼭! 널 따돌리진 않을 거야!";
			link.l1 = "좋아, 네 빚은 없던 일로 해주지. 하지만 기도나 해라, 휴고 아벤델. 네 '제안'이 내 마음에 들어야 할 테니까.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "선장님, 최대한 빨리 돌아오십시오 - 이 일은 금방 사라질 수도 있습니다.";
			link.l1 = "그래, 그래, 곧 네 빚 갚을 거야.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "돌아오셨군요, 선장님! 망할 천둥번개와 폭풍에 맹세코, 정말 반갑습니다! 내 빚은 어떻게 됐습니까?";
			link.l1 = "내가 처리했으니, 이제 네 차례야, 휴고. 네 이야기를 해 봐, 그리고 최소한 조금이라도 믿을 수 있게 말해 봐!";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "걱정 마, 선장! 나 현상금 사냥꾼인 거 알고 있었어? 아니면... 예전엔 그랬지. 운이 별로 없었던 것 같아. 아마 악마조차도, 그 온갖 짓을 하고도, 나만큼 패배자는 아니었을 거야. 마지막 일에서 모든 걸 잃었거든... 선원들은 날 버리고 떠났고, 빚 때문에 배도 팔아야 했어...\n";
			link.l1 = "이미 그대의 영웅적인 과거에 대해 들었네. 본론으로 들어가세, 휴고. 내 인내심을 시험하지 말게.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "그래, 그래, 선장님..."+GetFullName(pchar)+", 맞지? 나도 너에 대해 좀 아는 게 있어. 하지만 그게 중요한지는 모르겠군. 바르톨로메우 포르투갈 사람이라는 이름 들어봤나?";
			link.l1 = "포르투갈 놈 바트 말인가? 당연히 들어봤지. 다들 알거든. 내가 아는 한 그는 해적이고, 도살자에다 천하의 쓰레기야. 그런데 네 이야기에서 그 자가 무슨 역할을 하는 거지?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "그 자가 이 일에 피투성이로 깊이 관여하고 있어! 나는 지난 1년 반 동안 그를 쫓아다녔지. 네덜란드 회사에서 그의 목에 큰 현상금을 걸었어. 하지만 나는 실패했고, 모든 걸 잃었지. 그리고 회사는 최근에 그 자의 현상금을 세 배로 올렸어—살아있는 채로만, 살아있는 채로만 말이야, 젠장!\n";
			link.l1 = "당연하지, 그를 살아서 잡는 건 쉬운 일이 아니거든. 어쨌든, 내가 그걸 왜 신경 써야 하지, 위고? 네가 나를 속이려는 것 같은데!";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "나도 그럴 생각 없었어, 선장! 있잖아, 여기 의사 피터 반 스탈이라는 사람, 정말 좋은 분인데, 내 두통을 낫게 해주는 약을 줬거든! 그래서 말인데, 그 의사가 거의 사흘 동안 집에 없었고...\n";
			link.l1 = "휴고, 내 인내심도 이제 바닥나고 있어! 아가씨한테 칼로는 안 찌르겠다고 약속했으니까, 주먹으로 대신해도 괜찮겠지! 내일 네 머리는 어떤 약으로도 못 고칠 거라고 맹세한다!";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "잠깐만요, 선장님! 제발요! 제 말 좀 들어보세요, 제가 의사 집 근처에서 몇몇 남자들을 봤는데, 그들을 알아봤어요. 그 자들은 저주받은 포르투갈 프리깃 '알바트로스'에서 온 놈들이에요! 그리고 그중 한 명이 자기네 선장 건강에 대해 얘기하고 있었어요! 지금 보세요, "+pchar.name+", 바르톨로메오는 여기, 이 도시에 있어! 우리 코앞에 숨어 있으면서, 다쳤거나 병이 든 게 분명하니 저놈들이 의사를 찾는 거지!\n포르투갈 놈이 전부 선원들을 데려오진 않았을 거라 생각하지만, 나 혼자 이 난장판을 시작할 순 없어! 네가 그 빌어먹을 검을 어떻게 쓰는지 잘 알잖아! 힘 좀 쓰는 놈들 몇 명 데리고 가자. 우리가 그 쥐새끼를 찾아낼 거야! 그리고 놈을 붙잡아서 당국에 넘기자고!\n그러면 금화 두천 더블룬이 우리 주머니에 들어올 거다!";
			link.l1 = "아니, 휴고, 네 말은 이제 지긋지긋하다. 네 말이 맞다 해도 이 난장판에 끼지 않을 거야. 잘 있어라.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "흠, 흥미롭군. 그가 어디에 숨어 있는지 아나? 일이 잘 풀리면 몫에 대해 얘기할 수 있겠지만, 네 말이 사실이라면 지금 당장 서둘러야 해!";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "아니요, 어디 있는지 모릅니다, 선장님. 그 녀석들을 쫓아갈 용기가 없었어요. 외눈박이가 날 봤다면... 휴! 하지만 선장님의 부하들과 함께라면 이 마을 전체를 샅샅이 뒤질 수 있을 겁니다. 사람들 불러 모으시고, 이제 시작합시다! 젠장, 네덜란드 더블룬이 우리를 기다리고 있잖아요! 이런 빌어먹을 기회는 평생 한 번뿐이야, 청어라도 씹어야겠네!";
			link.l1 = "칭찬할 만한 열정이군... '위대한' 현상금 사냥꾼, 식탁에서 일어날 수나 있겠나? 나는 바로 수색을 시작할 테니, 따라오고 싶으면 따라와. 단, 너무 방해만 하지 마라.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "그래, 그래, 선장님, 술만 다 마시면 바로 따라가겠소... 어디서부터 시작할까요?";
			link.l1 = "어디라고?!... 난 간다, 네가 오든 말든.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "집 잘못 찾았어, 이봐. 얼른 꺼져!";
			link.l1 = "흠. 여기가 맞는 집인 것 같은데...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "글쎄, 내가 경고했잖아...";
			link.l1 = "...";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "돛을 바람에 가득 채우고, 높이 날아라, 아들들아... 대포를 준비해라!... 아하하하... 아, 내 아름다움이여...";
			link.l1 = "흠, 저 녀석 살아있는 게 운이 좋군...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "오, 신이시여, 누구시오? 제발 무기를 내려놓으시오! 여기 아픈 사람이 있소!";
			link.l1 = "네가 말하는 이 '병자'는 네가 평생 본 사람보다 더 많은 이들을 죽였어, 의사 양반. 비켜!";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "그는 내 환자고 겨우 서 있을 수 있을 뿐이야! 그걸 못 보겠어? 제발, 칼을 내려놔! 부탁이야!";
			link.l1 = "아니, 저 자식 뭐가 문제야, 젠장!?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "아마도 이 모든 게 그의 상처 때문일 거요, 독이 묻은 카리브 무기에 맞았으니... 그리고 그를 여기 데려온 자들이 말하길, 그가 죽으면 나도 죽는다고 했소! 하지만 나는 할 수 있는 건 다 하고 있으니, 그들에게 그렇게 전해 주시오!";
			link.l1 = "그 자들 걱정하지 마, 의사 양반. 내 부하들이 자네 집을 지킬 거고, 나는 총독을 만나러 가야 해. 아마 기뻐서 오줌을 지릴걸. 내가 돌아올 때까지 여기서 나가지 마, 의사.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "나는 떠나지 않을 거야, 그건 걱정하지 마. 그냥 그를 당국에 넘기고 이 악몽을 끝내자.";
			link.l1 = "물론이지, 지금 가는 중이야.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "해냈어요, 선장님! 우리가 그를 찾았고 곧 부자가 될 거예요, 제가 말한 대로죠! 이제 어떻게 할까요?";
			link.l1 = "그러길 바란다, Hugo. 어쨌든 아직 끝난 건 아니지. 이제 내가 총독에게 가서 보상에 대해 논의해야겠지?";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "아, 안 돼, 선장님! 저 빌어먹을 토마스한테 가지 마세요! 믿으세요, 저 악당이 우리 포로를 빼앗아갈 거고, 운이 좋으면 커피 한 잔이나 얻어마시겠지! 각하란 자는 교활한 놈이라서, 보상을 제대로 받고 싶으면 큐라소로 가야 해요! 안 그러면 포르투갈 놈을 요새로 끌고 가버리고, 우린 거지처럼 쫓겨날 거예요!\n";
			link.l1 = "그래, 정말 그렇게 확신한다면...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "나는 확실하지, 선장. 젠장, 정말이야! 하지만 바르톨로메오의 부하들이 분명히 이 마을 어딘가에 있을 테니, 우리도 주둔군의 눈길을 끌고 싶진 않다는 건 확실해! 이제 포르투갈 놈들을 네 배로 어떻게 데려갈지, 그리고 어떻게 들키지 않고 할지 결정해야 해.";
			link.l1 = "좋아... 윌렘스타드로 가는 길에 그 자의 프리깃과 싸우고 싶진 않아. 뭐 좋은 생각 있어?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "그래, 하나 있지. 먼저 그에게 더 고상한 옷을 찾아 입혀야 해, 그 다음에 취한 장교처럼 뒷문으로 끌고 들어가자고! 아무도 저놈이 빌어먹을 해적이라고는 의심도 안 할 거야, 믿어!";
			link.l1 = "흠, 나도 이게 맞는지 잘 모르겠지만, 어차피 더 나은 계획도 없잖아. 우리 손님을 위해 좋은 천을 구해볼게. 너는 여기 남아서 바트랑 의사를 잘 지켜봐.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "걱정 마시오, 선장님. 그 포르투갈 놈은 내가 든든하게 지키고 있소, 헤헤...";
			link.l1 = "나는 그렇게 믿고 싶군...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "군인들이 안 보여, "+GetAddress_Form(NPChar)+". 어디 있지? 네가 상황을 알리면 바로 그를 체포하겠다고 했잖아. 그런데 왜 병사들이 여기 없는 거야?";
			link.l1 = "병사들은 없을 거요, Van Stal 나리. 내가 직접 일을 처리할 것이고, 당신 환자를 가능한 한 빨리 쿠라사오로 데려가야 하오.";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "선장님, 들어보십시오. 저로서는 그의 상처를 감당할 수 없습니다. 할 수 있는 거라곤 열을 조금 낮추는 것뿐입니다. 그는 거의 의식을 잃고 헛소리를 하고 있으며, 누가 방해하지 않아도 분명히 죽을 겁니다. 게다가 며칠 안에 배의 흔들림이 그를 죽일 것입니다. 도움이 될 만한 약을 좀 드리겠습니다...";
			link.l1 = "아니, 의사 양반, 당신도 우리랑 같이 가야 해. 첫째, 나는 의학엔 영 꽝이고, 둘째, 여기 남아서 포르투갈 놈들에게 선장이 어디 갔는지 설명하고 싶진 않을 거 아냐?";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "...그래, 네 말이 맞을지도 모르지. 하지만 이 해적은 정말 끈질기단 걸 알아둬라. 나는 인디언 무기에 가벼운 상처만 입은 자들도 봤는데, 그들 모두 사흘도 못 가 죽었지. 그런데 그의 '동료'들 말로는, 이 상태로 벌써 일주일이나 버텼다더군! 그래도 나는, 이 자가 망망대해의 배 위에선 오래 못 버틸 거라 본다. 사흘, 그 이상은 못 간다!\n우리에겐 그 정도 시간밖에 없어.";
			link.l1 = "새도 쿠라사오까지 사흘 만에 못 갈 거야. 하지만 내가 뭘 해야 할지 알 것 같아! 내... 친구가 한 명 있는데, 앤티가의 세인트 존스에 살아. 그 친구는 치명상을 입은 사람도 치료할 줄 알아. 지금 우리를 도울 수 있는 사람은 그 녀석뿐이야. 목표는 간단해 — 포르투갈 놈이 죽기 전에 거기 도착하는 거지. 짐 싸, 의사 양반. 곧바로 출항한다. 그리고 네 환자는 다음에 옮길 거야!";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "안타깝군, 선장. 우린 졌고, 그 빌어먹을 금도 못 보겠어. 잘 가라.";
			link.l1 = "잘 가라, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "닥터, 환자 상륙 준비시켜. 장선 준비됐어. 서둘러!";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "가는 중이야, "+GetAddress_Form(NPChar)+".";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придёт через 7 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "이 집은 피비린내 나는 혼합물 냄새로 가득하군! 여기서 포르투갈인이 죽었다면 그게 진짜 놀랄 일이겠지; 이 냄새만 맡아도 어떤 병이든 다 나을 것 같으니!\n그리고 저 남자의 선원들도 이 악취 덕분에 우리를 쉽게 찾을 수 있겠어!";
			link.l1 = "휴고, 농담은 그만해. 내가 집을 지키라고 거리에 몇 명을 남겨뒀지만, 손님을 위해 경비 한 명 더 두는 게 나쁠 건 없지. 그를 잘 지켜보고, 욕은 좀 참아라. 아니면 지노가 자기 약을 먹이려고 할 거다; 분명 그 버릇 고칠 수 있을 거야.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "걱정 마시오, 선장님! 내가 우리 돈을 아주 철저히 지킬 테니, 저 자가 멀쩡하다 해도 절대 못 도망칠 거요! 그리고 제발, 더 이상 약 혼합물은 그만두시길 바라오!";
			link.l1 = "봐, 너도 마음만 먹으면 착할 수 있잖아. \n긴장 늦추지 마, 난 가봐야 해.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "벌써 떠나시나, 선장님? 좋아! 이제 때가 됐소! 거리에서 수상쩍... 수상한 녀석 몇을 봤소. 포르투갈 놈들 같진 않던데, 뭔가를 찾고 있었소. 조심해야 하오, 선장님!";
			link.l1 = "좋아, 경고해 줘서 고맙다, 휴고. 배로 가자.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "선장님, 이 만남을 얼마나 오래 기다렸는지 모릅니다! 그런데 그 옆에 있는 자는 누구요? 포르투갈인 바르톨로메오 본인이군, 하, 용감한 피에르가 맞았네 - 바로 그 사람이오! 물러서시오, 선장님, 우리는 저 자를 데려갈 것이니 아무도 다치지 않을 것이오.";
			link.l1 = "미안한데, 나리, 도대체 누구야? 내 길 막지 마, 안 그럼 너희 모두 내일 못 볼 줄 알아!";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "오, 저 놈 좀 봐라, 얘들아! 으하하하! 이봐, 꼬맹이, 레오 코드와 그의 돈 사이에 끼어들지 마라! 우리가 포르투갈 놈을 거의 반년이나 쫓아다녔고, 이제야 드디어 잡았거든. 그러니 네 그 이쑤시개나 내려놓고 살아 있을 때 꺼져라! 우리 그렇게 욕심쟁이 아니거든; 죽은 놈이면 충분하니까, 하하!\n";
			link.l1 = "그만하지. 춤추자고, 신사 여러분!";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "여기 뭔가 이상하다고 느꼈지! 잘했어, 선장! 하지만 이제 가야 해. 저 빌어먹을 레오 코드가 이 근처에 산적도 많고 훌륭한 배도 가지고 있거든! 이 섬에서 빨리 벗어나야 해!";
				link.l1 = "좋은 지적이야, 휴고. 그리고 네가 숨었던 구멍에 총알이 날아들지 않아서 정말 다행이야.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "안타깝군, 선장. 우린 졌고 그 빌어먹을 금도 못 보게 됐어. 잘 가라.";
				link.l1 = "잘 가라, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "저... 저는 우리 후방을 지키고 있었어요, 선장님! 선장님은 저 없이도 잘하고 계셨지만, 만약 누가 길 반대편에서 우리를 공격했다면 어쩌실 뻔했습니까? 그땐 배로 달려갈 시간도 없었을 거예요.";
			link.l1 = "어쩌면 그래서 네가 그 일에서 성공하지 못한 걸지도 모르지? 뭐, 됐다, 말은 그만하고 이제 배로 가자! 시간이 없어!";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "선장님, 그 포르투갈 놈이 정말 상태가 안 좋아요, 멈춰야겠어요!";
			link.l1 = "그래서 우리가 여기 온 것이오, van Stal 나리, 우리의 여정도 거의 끝나가오. 나는 선술집에서 방을 빌릴 것이고, 우리의 포로는 며칠 동안 그곳에 머물게 될 것이오.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "캡틴 나리, 내가 그 포르투갈인을 돌보겠소, 그는 완전히 쉬어야 하오.";
			link.l1 = "알겠어요, 의사 양반, 괜찮아요. 젠장, 내가 이 해적을 언제까지 돌봐야 하는 거야? 이건 저한테도 안 좋고, 저 친구한테도 필요한 게 아니에요! 내가 보모로 고용된 것 같고... 아, 미안해요, 의사 양반, 너무 벅차서 그래요... 나중에 봐요.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "나리, 당신이 선장인가 "+GetFullName(pchar)+", 오늘 막 우리 항구에 도착한 그의 배 말인가?";
			link.l1 = "맞아요, 무엇을 도와드릴까요?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "우리 식민지의 총독 자크 딜르 뒤 파르케 각하께서 당신을 기다리고 계십니다. 일이 급하오!";
			link.l1 = "좋소, 나리, 오늘 각하를 찾아가겠소.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "마르티니크에 도착했습니다, 선장님! 이제 우리의 돈도 멀지 않았습니다...";
			link.l1 = "포르투갈 놈들이 우리가 빌렘스타드에 도착할 때까지 살아남아야만 하지. 휴고, 나는 배로 가야 하니 네가 의사랑 환자를 지켜봐야겠다.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "배로 가자고? 왜? 나 좀 도와주라고 네 부하 몇 명 빌려줄 거야? 네가 없는 동안 무슨 일이라도 생기면 어쩌려고?";
			link.l1 = "미안하지만, 안 되네. 여기서 그대에게 위협이 될 만한 건 없을 거라 생각하네. 주둔군이 경계 중이고, 거리에는 평소보다 병사들이 더 많으니 무슨 일이 생기면 그들을 부르게. 이 섬에서 멀지 않은 곳에서 큰 배를 봤다고 하더군, 해적선일지도 모른다네. 그리고 총독 각하께서 내게 배로 순찰하며 섬을 강화하라고 명하셨네.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "배? 해적선인가? 혹시 알바트로스일지도 몰라! 아니면 우리 옛 친구 레오 코드의 동료일 수도 있고!";
			link.l1 = "아니면 그냥 평범한 해적선일 수도 있지. 그래도, 휴고, 만약 저 배가 우리 목숨을 노리고 온 거라면, 현지 순찰대와 함께, 그리고 총독의 금을 위해 맞서는 게 낫겠지. 남은 항해 내내 뒤만 살피는 것보단 훨씬 나으니까. 만약 이 경보가 헛소동이라면, 며칠간 선술집에서 엉덩이 붙이고 앉아 있는 일은 피할 수 있겠지.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "생각해 보시오, 선장. 댐... 아니, 포르투갈인을 아무런 보호 없이 두는 게 현명하다고 생각하시오? 그의 프리깃이 근처를 돌아다닐 수도 있는데 말이오. 당신이 총독의 보수를 받겠다고 하면 우리 보상까지 위험해지는 거요!";
			link.l1 = "말은 그만해, Hugo Avendell! 여기서는 내가 선장이니 최종 결정도 내 몫이야! 내 명령대로 해. 선술집에 가서 내가 돌아올 때까지 의사랑 포르투갈 놈을 감시해.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "돌아오셨군요, 선장님, 드디어! 유감스럽게도 나쁜 소식이 있습니다 – 포르투갈 놈이 사라졌고, 의사도 없어졌습니다!";
			link.l1 = "뭐라고?! 그럼 그때 넌 뭐 하고 있었던 거야, 이 멍청아?!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "그 배가 '알바트로스'였다는 데 내 손목을 걸 수 있어. 포르투갈 놈들이 선술집에 들어가는 걸 봤지, 그리고 나는... 나는 도망쳤어. 미안하지만, 외눈박이 개를 만나는 건 아무리 돈이 많아도 나한텐 너무 벅찼어!";
			link.l1 = "젠장! 적어도 선술집에서 무슨 일이 있었는지는 말해 줘야지?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "아무것도 못 봤다고 말했잖아. 프란츠 가르케랑 그 일당을 보자마자 바로 부엌을 뛰어갔어... 너무 아슬아슬했어! 어제 저녁에 일어난 일인데, 너한테 어떻게 알려야 할지 몰랐어...";
			link.l1 = "그래, 너 정말 용감하고 수완 좋은 놈이구나... 좋아, 한 번 더 기회를 주지. 우리가 놈들을 찾아낼 거다. 나는 이 악당을 너무 오래 아껴뒀고, 이제는 내 소유물이라고 생각한다. 아직 놈들을 잡을 시간이 좀 남았으니 선술집부터 시작하자. 아마 네가 도망치는 뒷모습 말고 더 본 사람이 있을지도 모르지. 가서 준비해!";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "들으셨죠, 선장님, 그가 외눈박이 개에 대해 말하고 있었어요. 제가 최근에 그에 대해 말씀드렸잖아요. 그리고 혀짧은 카스티야인은 에르난도 바스케스, 그 피의 돈, 베라크루스의 도살자예요. 저는 그를 못 봤어요!";
			link.l1 = "진정해, 휴고. 바르톨로메오는 아직 섬에 있을 거야. 좀 나아졌을지 몰라도 아직 너무 약하지. 그리고 내가 그를 어디서 찾을 수 있을지 알 것 같아! 우리가 놈들을 잡을 거야, 나는 내 보상을 포기하지 않아. 네가 겁쟁이가 아니라면 따라와. 아직 끝난 게 아니니까.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "질문이 너무 많군, 선장... 잠깐, 너 필립스버그에서 온 그 교활한 녀석 아니냐? 우리한테서 너무 오래 도망쳤지, 그런데 봐라 - 결국 여기 있잖아...";
			link.l1 = "재수 없었군, 이 쓰레기 놈아!";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... 이 썩을 게딱지 같은 놈, 다 불게 될 거다, 내 말 믿어라, 이 피투성이 쥐새끼야! 그러고 나면 돛대 대신 야드암에 매달려 죽게 될 거다... 그런데 넌 또 뭐야? 젠장, 저 원숭이 같은 놈들은 믿을 수가 없어! 맨날 내가 다 해야 한다니까...";
			link.l1 = "내가 방해하고 있나, 신사 여러분?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "네 타이밍이 마음에 드는군... 오늘까지 나를 살려준 것에 대해 고맙다고 해야겠지?";
			link.l1 = "맞아. 내 이름은 "+GetFullName(pchar)+" 그리고 너, 포르투갈 놈, 아직도 내 포로야. 그러니까 질문하지 말고, 가야 한다.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "잠깐만요, 선장님... 마을에 바스케스 놈들이 잔뜩 있어서 그냥은 못 나가요. 저한테 칼을 주시면 훨씬 더 잘 싸울 수 있을 겁니다.";
			link.l1 = "너, 동료들이랑 사이가 안 좋은가 보군, 응? 좋아, 칼 하나 더 있으면 나쁠 건 없지. 시체 무기 챙기고 내 옆에 붙어 있어!";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "내가 등을 돌리는 순간 네가 나를 치라고 무기를 줄 거라 생각도 하지 마! 그냥 내 옆에 붙어 있어.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "걱정 마시오, 선장님. 차라리 죽는 게 바스케스 손에 다시 잡히는 것보다 낫소.";
			link.l1 = "글쎄, 아직 너를 죽이고 싶진 않아. 가자, 시간이 없어!";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "안타깝군, 내가 너를 죽이고 싶었다면 외눈박이 놈을 도왔겠지...";
			link.l1 = "근데 너도 나 안 도와줬잖아, 그러니까 닥치고 움직여!";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "젠장! 저놈들이다! 전부 죽여라!";
			link.l1 = "또 시작이군... 자, 덤벼라 이 잡놈들아!";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "훌륭하군! 너는 외눈박이 개를 죽였으니, 이건 정말 걸작이라 할 만하지! 그의 부하들 중 몇 놈이나 지옥불에 보냈냐?";
				link.l1 = "나는 싸우고 있었지, 세는 게 아니었어. 그리고 너는 어디 있었냐, 휴고?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "안타깝군, 선장. 우린 졌고 그 빌어먹을 금도 못 보겠어. 잘 가.";
				link.l1 = "잘 가라, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "나는... 안전하게 후퇴할 수 있도록... 그러니까, 우리 후방을 지키고 있었지.";
			link.l1 = "그래, 이걸로 끝이군, Hugo Avendell. 네 비겁함은 내 모든 기대를 뛰어넘었어. 우리가 얼마나 힘들게 싸웠는지 알기나 해? 간신히 살아남았다고!";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "진정하시오, 선장님... 내가 숨고 있었던 건 인정하오. 하지만 이번 기회를 당신께 가져왔소! 기억하시오, 포르투갈 놈들에게 당신을 이끈 것도 나였소! 음... 당신의 정당한 분노를 생각해서, 보상은 3분의 1만 받겠소.";
			link.l1 = "이거 참 대단하군! 이제 흥정이라도 하겠다는 거냐? 아니, 친구, 너는 이 일에서 끝났어! 너는 생피에르 선술집에서 돈을 잃었지. 거기다 두고 도망쳤으니, 이제 너한텐 끝난 거야.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "선장님, 분명히 과장하고 계십니다... 좋아요, 4분의 1에 동의하죠... 아니, 5분의 1! 10퍼센트요!";
			link.l1 = "내 인내심을 시험하지 마라! 꺼져! 내 선원 중에 겁쟁이는 필요 없어, 특히 지금처럼 시간이 촉박할 때는 더더욱!";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", 좀 불공평하지 않아?";
			link.l1 = "인과응보야, 휴고... 네가 선택을 했으니, 이만 작별이다. 네가 직접 결과를 받아들이고, 그런 모험에 함부로 뛰어들지 마라. 이런 일은 분명 네게 맞지 않아.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "밸러스트를 버리는 건가요, 선장? 정말 그렇군, 하... 바스케스는 아직 자유롭고 알바트로스에는 사내들과 대포가 잔뜩 있지. 내 멋진 바지를 낡은 손수건과 바꿀 만큼 확신하는데, 에르난도는 우리가 도망치는 걸 절대 두고 보지 않을 거야.";
			link.l1 = "흠, 우리가 직접 가서 그를 맞이해야 할 것 같군. 가라, 포르투갈 나리, 그리고 입 좀 다물고 있어라. 최대한 빨리 닻을 올릴 거다.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "뭘 기다리고 있어, 젠장?!";
			link.l1 = "에르난도 바스케스는 어디 있지? 말하면 목숨은 살려주겠다.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "네 빌어먹을 질문이나 들고 지옥이나 꺼져라!";
			link.l1 = "먼저 가시지...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "그리고 여기 있군, 내 용감한 친구. 이제야 제대로 대화를 할 수 있겠어! 축하하네, 선장. 외눈박이 개를 죽이고 '알바트로스'를 박살낸 건 결코 쉬운 일이 아니었지! 정말로, 내 목숨을 구하기 위해 많은 일을 해줬군... 어쩌면 내가 고맙다고 해야 할지도 모르겠네?";
				link.l1 = "네가 교수대 위에서 춤추게 될 때, 아니면 빌렘스타트에서 너를 위해 준비해둔 게 뭐든 간에, 그때 가서 나한테 고마워하게 될 거다.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "그리고 여기 있구나, 용감한 친구여, 드디어 우리도 제대로 대화를 나눌 수 있게 되었군! 축하하네, 선장 – 외눈박이 개를 죽인 건 명예로운 노래로도 남을 만한 일이야! 정말 내 목숨을 구하기 위해 많은 일을 해줬지... 어쩌면 내가 자네에게 감사해야 할지도 모르겠군?";
				link.l1 = "네가 교수대에서 춤추게 될 때, 아니면 빌렘스타트에서 너를 위해 준비해둔 게 무엇이든 간에, 그때 나한테 고마워하게 될 거다.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "믿을 수가 없군! 지난 2주 동안 내 목숨을 구해주고, 네 집으로 데려가서 싸움에서도 날 지켜줬지... 그런데 이제 날 죽으러 보내겠다고? 정말 믿기 힘들다... 사실, 이제 널 거의 내 친구라고 생각할 정도야, 하하.";
			link.l1 = "명예를 운운하는 해적이라니? 포르투갈 놈, 농담하는 거냐? 내가 널 살려둔 이유는 딱 하나였어 - 살인자이자 악당인 네놈을 법정에 세우려고!";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "내 친구라니... 조롱처럼 들리는군. 그래도 네 말이 맞아. 내가 그렇게 한다면 이상하겠지, 포르투갈 놈아...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "아, 그만하면 됐소, 선장. 자네, 내가 살아 있는 걸 보고 싶어서가 아니라 회사에서 약속한 돈을 받으려고 그 모든 짓을 한 거겠지! 자신이 정말로 정직한 척하지 마시오, 나리, 그건 자네한테 어울리지 않으니.";
			link.l1 = "나만이 나 자신을 판단할 수 있지. 그러니 이 대화는 여기서 끝내자. 이제 윌렘스타드로 항해할 시간이야.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "요즘 사람들 사이에도 아직 정직함이 남아 있는 것 같군... 하지만 돈이 항상 걸림돌이 되지, 그치, 선장?";
			link.l1 = "교수대에 오를 해적 주제에 그런 말을 듣다니, 포르투갈 놈. 널 풀어주겠다... 이유는 묻지 마라, 첫 항구에 닿자마자 당장 꺼져라. 그리고 명심해라, 다음에 또 만나면 이렇게 봐주지 않을 거다.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "정말요? 그러면 좋겠어요, 선장님! 여기 럼주 좀 시켜주실래요? 알잖아요, 선장님의 기사도와 우리 사이, 그리고 제 형 집행 연기를 축하하는 의미로요?";
			link.l1 = "못된 농담은 하지 마라, 첫 번째 해안에 도착할 때까지 넌 아직 내 포로다. 잘 가라.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "그래... 결국 교수대구만. 예상했던 일이야. 이제 내 말 좀 들어봐, 선장. 나를 제대로 처형하려고 그렇게까지 살려둔 거, 고맙게 생각해. 지금 와서 마음을 바꿔달라고 하면 바보 같겠지? 그런데 내가 뭔가를 내놓는다면 어때? 거래를 하자는 거지, 응?\n";
			link.l1 = "나는 아무 말도 하지 않겠다, 포르투갈 놈. 너는 해적이자 개자식이지. 네 죄값은 빌렘스타트에서 치르게 될 거다.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "거래라고? 뭘 내놓을 수 있는데?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "네 거래 따위 필요 없어, 그냥 제일 처음 만나는 항구에서 꺼져. 오늘은 운이 좋은 날이니까.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "있지, 내 목숨을 이렇게 집요하게 구해준 건, 그 배경이 썩 유쾌하진 않아도 고마움을 표할 만하지. 그리고 포르투갈인 바르톨로메오는 은혜에 대해 좀 아는 놈이지. 자, 들어봐. 너랑 내가 만나기 한 달 전에, 우리는 컴퍼니 소속 배 한 척을 나포했어. 놈들은 마지막 한 명까지 악마처럼 싸웠지. 하지만 창고엔 포탄이랑 쥐밖에 없더라고\n내 선원들은 불만이었지만, 난 선장 선실에서 아주 흥미로운 상자 하나와 서류 몇 장을 발견했어. 그 배는 아마존 어딘가 광산에서 샘플을 운반하던 특사선이었지. 순수한 다이아몬드와 루비, 진짜 보물이었어!";
			link.l1 = "흥미로운 전리품이군... 이제야 왜 회사가 너한테 그렇게 관심을 가지는지 알겠어, 그런데 네 이야기는 도대체 무슨 의미가 있지?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "내 일등항해사 바스케스와 프란츠 가르케가 선원들을 잘 다스리고 있었기에, 나는 내 운에 맡기기로 했다. 나는 그들에게서 돌을 숨기고 서류는 불태웠다. 네덜란드 놈들이 승선전투 때 우리 돛대와 장비를 심하게 망가뜨려서, 우리는 '알바트로스'를 북쪽의 작은 섬, 작은 만으로 끌고 들어가야만 했다. 선원 전원이 프리깃을 수리하는 동안, 나는 혼자 정글 깊숙이 들어갔다\n나는 돌을 묻었다. 이런 상황에서 배에 두는 건 너무 위험했으니까. 내 계획은 첫 항구에서 사랑하는 선원들을 따돌리고, 작은 배를 사거나 훔쳐서 그 섬으로 가 상금을 챙긴 뒤... 내 지난 삶과 작별하는 거였지! 유럽, 근사한 저택, 아름다운 아내, 그 다음은 다 알잖아...";
			link.l1 = "짐작컨대, 뭔가 잘못된 거지.";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "모든 게 엉망이 됐어! 젠장할 섬이 알고 보니 현지 식인종 무리의 소굴이었지. 내가 해안으로 돌아오자마자 놈들이 우리를 공격했어. 우리는 최대한 빨리 배를 띄워 도망쳐야 했고, 그때 내가 한 방 맞았지. 그냥 긁힌 줄 알았어.\n며칠 뒤 나는 열에 시달리며 반쯤 죽은 채로 누워 있었고, 아마 돌에 대해 뭔가를 중얼거렸던 모양이야. 프란츠와 바스케스는 내가 섬 어딘가에 뭔가를 숨겼다는 걸 눈치챘지만, 정확한 위치는 몰랐지. 놈들은 인디언들에게 계속 총질당하면서 그 섬을 헤매는 게 마음에 들지 않았던 거야. 그래서 그 자식들은 나를 가장 가까운 항구로 질질 끌고 갔지. 네덜란드 놈들과 싸우다 우리 의사가 죽었으니, 새 의사가 필요했던 거야.\n그렇게 해서 내가 그 의사 집에 끌려가게 된 거지. 놈들은 나를 잠깐 정신 차리게 해서 고문하고 돌의 위치를 알아내려고 했어. 그 후에는 날 토막 내서 내 살코기를 게밥으로 줄 생각이었을 거다.";
			link.l1 = "그들을 탓한다고는 못 하겠군 – 당신이 부하들을 속이려고 했으니까. 그러니 다시 묻지, 왜 그 이야기를 나한테 하는 거지?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "이 놈들은 사람이 아니었어, 믿어라. 이제 다 제자리, 즉 지옥에 갔지, 하하! 내 자유와 목숨값으로 네게 네덜란드 보물의 정확한 위치를 알려줄 수 있지.";
			link.l1 = "아니, Bart, 네 배신으로 네가 얼마나 사악한 놈인지 완전히 확신하게 됐다. Willemstad와 정당한 심판이 널 기다린다. 협상은 없어.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "정말로 그런 보석들이 존재한다고 내가 믿어야 하냐? 뭐, 어차피 잃을 것도 없으니... 거래로 이 이야기가 시작됐고, 거래로 끝나겠지. 네 조건을 받아들이겠다, 포르투갈 놈.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "이건 내 소박한 감사의 표시야. 에이, 바르톨로메오 포르투갈 놈의 목숨값이 반짝이는 페소로 얼마나 될지 알았으면 좋겠군, 하! 네 목적이 순전히 실리적이었다는 건 알지만, 그래도 모든 일에 고마워, 선장. 하하\n터크스야, 해안에서 멀지 않은 정글이지. 마른 채로 비뚤어진 나무를 찾아. 거기엔 그런 나무가 딱 하나뿐이야. 난 그 근처에 상자를 묻었어. 그러니 삽 챙기는 거 잊지 마라. 행운을 빈다...";
			link.l1 = "좋아, 그건 기억하마. 지금 당장 너는 장선 타고 내 배에서 내려라. 잘 가라.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "마지막으로 한 가지 더, 선장. 아직 야만인들이 많을 거라 생각하지만, 그놈들만 조심할 게 아니오. 바스케스는 '알바트로스'에 없었지? 피투성이 돈은 너무 영악한 놈이야... 그 자식이 교수대에 매달리거나 머리에 총알이 박힐 때까지 등 조심하시오.";
			link.l1 = "경고해 줘서 고맙군, 포르투갈 놈. 이제 내 배에서 얼른 나가주겠나... 내 인내심 시험하지 말라고.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "오, 이게 누구야! 선장 "+pchar.name+" 자기야! 한잔 할래?";
			link.l1 = "있지, 다시 만나서 사실 기쁘다. 하지만 마르티니크에서 내가 너한테 너무 심하게 굴었을지도 모르겠군.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "뭐, 선장! 이미 일어난 일은 어쩔 수 없지... 사실 내가 쫓겨나도 할 말 없는 짓을 하긴 했지... 그런데 말이야, 오늘 필립스버그에 누가 손님으로 왔는지 믿기나 하겠어?";
			link.l1 = "설마 그게...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "아니요, 아니요, 선장님, 포르투갈 놈들이 아닙니다. 또 다친 놈도 아니고요. 훨씬 더 좋은 소식입니다! 에르난도 바스케스... 바로 그 피의 돈입니다! 며칠째 이 지역 총독의 손님으로 와 있었습니다.";
			link.l1 = "바스케스? 총독의 손님 말인가? 이제 알겠군. 휴고, 이게 대체 어떻게 된 일이야, 자세히 말해 봐.";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "음, 나도 아는 게 많지... 하지만 이번 항해 덕분에 또다시 빈털터리가 됐어. 이 정보가 그렇게 필요하다면 페소 몇 푼쯤은 줘야 하지 않겠어?";
			link.l1 = "휴고, 넌 여전히 협잡꾼이자 악당이군! 할 말 있으면 해라, 그리고 옛 우정 생각해서 5000페소 가져가라.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "어쩐지, 전혀 놀랍지 않군. 자, 1만 페소 가져가라. 네 정보가 그만한 값어치를 하길 바라는 게 좋을 거다!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "내가 더 좋은 제안을 하지. 내 선원으로 들어오는 건 어때? 자네가 이익이 되는 거래를 만들고 찾아내는 재주가 있다는 건 알고 있지. 용감한 전사인 척하는 게 지겹다면, 내 배의 경리 자리를 기꺼이 맡아도 좋아.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "아니, 선장, 그렇게는 안 되지! 그 빌어먹을 포르투갈 놈이랑 한탕 크게 챙겼잖아, 분명히. 그러니 그게 내 몫이라고 생각해, 그렇게 욕심부리지 마. 15,000코인, 한 푼도 깎아줄 수 없어!";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "아, 젠장, 가져가라!";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "그래, 탐욕이 좋다던데... 너한테는 좀 과한 거 아니냐, 응?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "이게 바로 내 노림수지! ... 들어봐, 바스케스는 나랑 같은 배를 탔는데, 나는 선실값 갚으려고 갑판 청소나 하고 있었고, 그놈은 선실에서 쉬고 있었거든. 덕분에 서로 얼굴 볼 일도 거의 없었고, 그가 날 알아보지도 못했지. 하지만 나는 그 악마를 바로 쫓기 시작했어... 그놈한테 재미있는 일이 벌어졌거든.";
			link.l1 = "계속 말해! 그 자가 총독 관저에서 뭘 하고 있는 거야?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "나는 잘 모르지만, 그가 도착한 이후로 며칠째 주둔군이 경계 태세를 유지하고 있었고, 거대한 전함이 갑자기 닻을 올리고 급히 떠났어. 북서쪽으로 항해한 것 같아. 마을 전체가 온통 추측과 소문으로 떠들썩했지...\n";
			link.l1 = "그래서 그게 내가 마주쳤던 배였군! 흥미로운데... 주제에서 벗어나지 말게, 휴고, 계속 이야기해 보게.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "음, 내가 말했듯이, 배는 사라졌고 바스케스는 우리 총독 마르틴 토마스의 일종의 손님이 되었지. 가끔 마을에서 그를 보는데, 항상 몇몇 군인들과 함께 다녀. 그게 호위인지 아니면 호송대인지 나도 잘 모르겠어, 하하. 하지만 돈에 대해 더 자세히 알려줄 수 있는 사람들은 관저에 있는 사람들뿐일 거야.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "어쩌면 네 말이 맞을지도 모르지. 하지만 우리 약속했잖아, 기억 안 나? 영웅인 척하지 말고 내 배로 가서 내가 돌아올 때까지 기다려. 나는 우리를 환대하는 총독과 이야기해 볼게.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "흥미로운 일이었군. 정말 도움이 됐어, Hugo. 럼이나 마셔, 나머지는 네가 신경 쓸 일이 아니야.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "진심이오, 선장? 도대체 무슨 생각이오? 내 얼굴에 총을 들이대며 쫓아냈으면서, 이제 와서 이런 제안을 하러 온 거요?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "그건 잊어버려, 내가 요즘 정신이 없었어. 미안하다, 욕심이 날 집어삼킨 것 같군. 자, 여기 1만 페소다. 바스케스에 대해 아는 걸 말해 줘, 난 지금 급하거든.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "그 일에 대해 사과해야 할지도 모르겠군. 넌 싸움은 형편없지만, 돈에는 꽤 능하더군. 내 제안을 다시 한 번 하겠다, 어때?";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "뭐라고 해야 할까... 알겠어, 하지만 내 몫을 받고 나서야 동의하지, 선장. 10퍼센트, 기억하지? 그 악당 때문에 이천을 받았으니, 나를 선원으로 들이려면 먼저 빚부터 갚는 게 순서야. 10퍼센트, 딴소리 말고!";
			link.l1 = "너 정말 사기꾼이구나, 휴고. 지금 당장 그 정도 돈은 없어, 하지만 곧 다시 올 거야. 여기서 기다려.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "네 사업 수완으로 내 기대에 부응하길 바라네, 하! 몫을 가져가게!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "결정은 선장님이 하십시오. 나는 여기서 잠시 머물겠소. 마음이 바뀌면 다시 오시오.";
			link.l1 = "좋아, Hugo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "마음이 바뀌었나, 선장? 그럼 돈은 기다리겠네.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "동전이나 가져가라, 이 악당아, 하하!";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "아직 그런 돈은 없어.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "좋은 하루요, 선장님. 무슨 일로 오셨소?";
			link.l1 = "아니, 아니오, 나는 그냥 기다리고 있을 뿐이오. 토마스 나리께서는 언제 시간이 나시지? 나는 접견을 기다리고 있소... 그래. 그런데, 각하께서는 정말로 그 유명한 해적 에르난도 바스케스를 친구로 여기시나?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "걱정 마시오, 마인헤르, 이제 곧 그가 풀려날 것이오. 그리고 물론 아니오, 마인헤르! 이 악당은 당국에 항복했지만, 어찌된 일인지 교수형을 면했소. 아마도 예전 범죄 동료들을 밀고해서 목숨을 부지한 것 같소... 확실하진 않소. 그는 며칠째 여기 감옥에 갇혀 있었소... 정말 악몽이었소, 마인헤르! 인간의 탈을 쓴 그 짐승이 우리 저택에서 살고 있었다니!";
			link.l1 = "악몽이 따로 없군! 도대체 그 괴물이 토마스 나리에게 교수대를 피하라고 무슨 말을 했다는 거지? 상상도 못 하겠어!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "나도 잘 모르겠어, 하지만 몰래 말해주자면, 각하께서 그런 손님을 내쫓으셨을 때 하인들 모두가 기뻐했지...";
			link.l1 = "그 자를 처리했어? 결국 자기 죗값을 치른 거야?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "아직은 그렇지 않아. 며칠 전에 그자는 군함 감옥에 실려 윌렘스타드로 끌려갔지. 있잖아, 토마스 나리께서 그 악당에게 흥미를 잃으셨다더군. 속이려 했던 모양이야.\n그리고 그자의 전 선장도 잡혔다더라 - 포르투갈인 바르톨로메오 말이야! 생각해 봐라! 회사에서 둘을 같이 교수형에 처하려는 것 같아. 재판이 한 달 뒤라는데, 왜 그렇게 오래 기다리는지 모르겠군.";
			link.l1 = "포르투갈 놈들?! 흠... 같이 있어줘서 고맙다, 친구... 이제 토마스 나리가 한가해진 것 같으니, 나는 이만 물러가겠다.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
		
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "이제 너희 둘 다 죽었어!";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "이런, 이럴 줄은 몰랐는데, 선장! 하지만 이 피와 소음, 총성까지... 이게 우정 어린 방문 같진 않군. 아니면 불꽃놀이로 축하라도 하는 건가, 응?";
				link.l1 = "그만 좀 해, 포르투갈 놈. 네가 내게서 산 자유를 어떻게 써먹는지 마음에 안 들어. 내가 네 한심한 엉덩이 구하려고 얼마나 애썼는데, 우리 헤어진 직후에 이렇게 멍청하게 잡히게 둘 순 없지!";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "음, 심심해서 왔지! 그래서 너 보러 온 거야. 여기서 편하냐, 친구!";
				link.l2.go = "Portugal_free_1a";
				// <-- legendary edition
			}
			else
			{
				dialog.text = "조심해, 친구! 아, 내가 도와줄 수 없어서 정말 아쉽군!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "그래, 귀족들이 때로는 돈에 흔들리지 않기도 하지, 그치? 하하... 조심해라, 바로 뒤에 있다!";
			link.l1 = "아, 또 이런 빌어먹을 난장판이냐!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
			dialog.text = "그래, 귀족들은 가끔 돈에 흔들리지 않기도 하지, 그치? 하... 조심해, 바로 뒤에 있어!";
			link.l1 = "아, 또 이 피투성이 난장판이냐!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "그리고 내가 이 녀석이 문제라고 경고했잖아!";
			link.l1 = "거의 내 등을 쏠 뻔했어! 어떻게 뚫고 들어온 거지?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "그가 자물쇠 따개를 가지고 있는 걸 봤어, 누가 준 것 같더라고... 항상 하층민들과 연줄이 있었지. 자, 선장님, 이제 이곳을 떠나야 한다고 생각하는데, 동의하십니까?";
			link.l1 = "그렇다고? 좋아, 주둔군 전부가 오기 전에 서두르자. 네 자물쇠는 금방 따줄게...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "있잖아, 선장. 이 신선한 공기... 감옥에서 몇 주 보내고, 네 배의 보트가 현지 순찰대에 발견된 뒤에야 진짜 소중함을 알게 되더라고. 아직도 네가 날 구해준 빚을 갚아야 할 것 같아.";
			link.l1 = "필요 없어, 포르투갈 놈. 나는 명예로운 기사도 아니야, 그냥... 옳다고 생각하는 일, 해야 할 일을 할 뿐이야.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "하, 그거야말로 완벽한 품질이지! 하지만 난 꼭 주고 싶어, 자 받아... 감옥에서 내가 유일하게 숨길 수 있었던 거야... 그래, 맞아. 이건 내 부적이야. 바다에서 항상 행운을 가져다줬지. 너는 훌륭한 선원이니, 너나 네 항해사가 분명 잘 쓸 수 있을 거라 확신해.";
			link.l1 = "그래, 그리고 그 부적으로 네가 바로 네덜란드 놈들 손아귀에 떨어진 건 운이 좋았지.";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "이봐! 나 아직 살아 있잖아? 그리고 참고로, 이제 더 이상 감옥에 있지도 않아. 받아, 선장. 이제 이 부적이 네게 힘이 될 때야. 그리고 다시 한 번 고맙다!";
			link.l1 = "그럼 이만, 포르투갈 놈. 그리고 제발, 교수대는 좀 피해서 살아라! 내 고생을 생각해서라도 말이지, 하하!";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("You have received the talisman");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
