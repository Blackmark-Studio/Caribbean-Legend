void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	if (findsubstr(sAttr, "tonzag_jail_" , 0) != -1) {
	 	pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
 	    Dialog.CurrentNode = "exit";
 	}
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "이 줄을 보고 있다면, 코드에 버그가 있는 거야";
			Link.l1 = "Exit";
			Link.l1.go = "exit";
			
			//--> Вступительный туториал на палубе корабля за Шарля
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
			{
				dialog.text = "짜릿하군, 젠장! 진짜 해전이야!\n여기서는 싸움을 직접 볼 수 없다는 게 아쉽네... 뭐, 괜찮아. 이제 항해에 대해 충분히 배웠으니 어떻게 돌아가는지 상상할 수 있지.\n아마 해적 다섯 명쯤... 큰 배 하나, 중간 배 몇 척, 그리고 잔챙이들. 우리 피나스에는 딱 맞는 상대야. 멋진 이야기가 되겠어 — 루루가 정말 좋아하겠지!";
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
				pchar.wind.speed = 18.0;
				fWeatherSpeed = stf(18.0);
				//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
				AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
			}
			//<-- Вступительный туториал на палубе корабля за Шарля

			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "그래, 우리가 지도에서 이 장소를 찾았어. 표시해 두고, 이제 탐색하러 가면 되겠군.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "좋아, 도착했군. 내 배는 남쪽 만에 숨겨 두고, 정글을 걸어서 돌아와서 플리트우드에게 제대로 된 함정을 준비해야겠어.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "흠... 저 녀석을 믿는 건 위험하지. 그래도 하는 말이 진짜 같긴 해. 이번엔 거짓말이 아닐지도 모르지. 하지만, 어쨌든 그 아내와 얘기해 봐야겠군... 보선! 저 포로 여자를 데려와라!";
    			link.l1 = "예, 알겠습니다, 선장님!";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//<-- Ложный след
			
			//--> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "여기가 그곳인 것 같아. 이 근처에 잎이 없는 나무는 이것뿐이야. 여기서 파봐야겠어.";
    			link.l1 = "(보물을 파내라)";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//<-- Португалец
			// Сага
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "무슨 일이야? 내가 어디에 있는 거지?! 여기가 대체 어떤 곳이야?";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> приколы со стуком в дверь Диффиндура, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "이 문은 배의 내실로 통하는 문이다. 잠겨 있군... 호크가 여기 있을 거야. 올레가 뭐라고 했더라? 비밀 노크를 써야겠어.";
    			link.l1 = "두 번 두드려.";
    			link.l1.go = "knock_2";
				link.l2 = "세 번 두드려.";
    			link.l2.go = "knock_3";
				link.l3 = "한 번 두드리고, 잠시 멈췄다가, 세 번 두드려라.";
    			link.l3.go = "knock_1_3";
				link.l4 = "두 번 두드리고, 잠깐 멈췄다가, 다시 두 번 두드려.";
    			link.l4.go = "knock_2_2";
				link.l5 = "세 번 두드리고, 잠시 멈췄다가, 한 번 더 두드려.";
    			link.l5.go = "knock_3_1";
    		}
			//<-- приколы со стуком в дверь Диффиндура, LSC
			
			//--> напялили водолазный скафандр, для перехода в режим шага
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "이런 젠장! 저건 진짜 무겁잖아!";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//<-- водолазный скафандр
			// отказ от телепортации
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "아니, 아니, 아니! 절대 안 돼! 세 번이면 진절머리가 나!";
    			link.l1 = "...";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "끝났다. 르바쇠르는 죽었다. 생각했던 것보다 훨씬 쉬웠군... 하지만 뭔가 이상하다. 티보가 마르텐에게 한마디도 하지 않았어! 그 말은 로베르가 나를 배신했거나, 무슨 사고가 있었다는 뜻이지\n그런데 그 망할 놈 티보는 어디로 도망친 거지? 분명 카트린을 쫓고 있을 거다. 내가 그 녀석 코앞에서 그 여자애를 살아서 데려가려면 빨리 움직여야 해...";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "보물, 보물... 인디언 도시... 이런 우연을 믿지 않아... 내 형이 Dichoso의 프리깃선 실종에 뭔가 관련이 있었던 게 틀림없어. 아마 Dichoso가 다시는 입을 열지 못하게 했겠지\n아니면 둘이 한패였을 수도 있지; 스페인 놈들이 Dichoso가 이 근처에 있다고 생각한 데는 이유가 있었을 거야. 도무지 말이 안 돼. 하지만 Michel이 de Poincy에게 전달하던 인디언 금과 Miguel Dichoso의 금, 결국 같은 금이라고 확신해. 죄수의 이야기가 장교가 내 형의 모험에 대해 말해준 것과 일치하거든\n웃기지, Michel도 금을 전달하지 못했고 Miguel도 마찬가지야! 그럼 지금 그 보물들은 어디에 있는 거지? 아마 그게 내 형이 그렇게 서두르는 이유일 거야\n즉, 금을 찾으면 일석이조라는 거지: 내 형의 뻔뻔한 눈을 다시 마주하게 될 테고... 그래, 금은 언제나 좋은 거니까. 그런데 도대체 어떻게 찾아야 하지? 이제 스페인 놈들한테 아주 가까이 다가가야 할 때인 것 같아\nDon Ramona Mendoza는 제외야; 그와는 상대할 수 없을 것 같으니, 하지만 성직자 Vincento, 남작의 최악의 적... 그 자라면 괜찮겠지. 그런 부류는 양심은 없지만 돈과 더러운 수단을 좋아하니까\nDichoso, Dichoso... 이 성을 예전에 들어본 것 같기도 하고... 아니면 아닌가? 뭐, 알 바 아니지. 장교에게 가서 스페인 죄수를 넘겨달라고 해야겠다. 그러면 언제든 Santiago로 갈 수 있을 거야.";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "바닐라가 브리건틴에 실렸고, 그 배의 돛은 이미 수평선 너머로 사라진 지 오래다. 그런데 이 빌어먹을 갈레온은 바다로 나가지 않고 항구로 돌아와 버렸군. 내 배를 끌고 항구에 나타나선 안 되겠어. 내가 과달루프를 떠난 줄로만 생각하게 두는 게 상책이지... 정글을 통해 마을까지 걸어가서, 내 소중한 마르셰 소식이나 알아봐야겠다...\n";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "상갑판에는 경비병이 몇 명밖에 없고, 모두 꽤 졸린 상태야. 내가 조용히 뒤에서 접근해서 너클더스터로 뒤통수를 치면 한 명씩 처리할 수 있을 것 같은데... ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "잠기지 않은 빈 집, 2층에는 아늑한 방이 있고, 칼훈의 방 근처라니... 이건 정말 처녀의 기도에 대한 응답이군... 창문으로 나가서 지붕의 처마를 따라가면 아치의 방으로 쉽게 몰래 들어갈 수 있겠어. 하지만 들키지 않으려면 밤에 해야 해...";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// Поиски Ксочитэма
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "드디어! 나는 '현현'이 가리킨 장소를 찾았어. 그곳엔 인디언 우상이 있군. 내가 가까이 가면 '길잡이 화살'이 흔들림을 멈추고 한 방향을 가리켜. 뭐, 인디언 마법에 인디언 우상이라면 당연하지. 이제 '길잡이 화살'이 가리킨 위치를 지도에 표시해야겠어, 그리고 도미니카로 갈 거야.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "드디어! '현시'가 가리킨 장소를 찾았다. 인디언 우상이다. 내가 가까이 다가가면 '길의 화살표'가 흔들림을 멈추고 한 방향을 가리킨다. 뭐, 당연하지. 인디언의 마법과 인디언 우상이니까. 이제 '길의 화살표'가 가리키는 위치를 지도에 표시하고, 그 다음 메인으로 가야겠다.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "두 징후 모두 발견했어! 이제 두 번째 방향을 지도에 표시해야지. 이 두 방향이 교차하는 지점이 바로 크소체아템 섬의 위치를 알려줄 거야.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// рассуждения по Тайясалю
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "알론소 데 말도나도는 유카탄 북쪽에서 시작하는 타야살로 가는 길이 있다고 말했다. 즉, 그 지역의 셀바 깊숙이 들어가야 한다는 뜻이지. 하지만 지노는 원래 순간이동 석상이 사람들을 타야살로 이동시키기 위해 만들어졌다고 했어\n그리고 미스키토 샤먼 스네이크 아이는 그 우상들이 '먹힌 자'를 그곳으로 보내도록 설계되었다고 내게 말했다. 그런데 그렇다면 왜 그 포탈들은 망가진 걸까? 흠. 게다가 투 매니페스테이션 지도에는 미스키토 석상 근처에 이상한 원이 그려져 있어\n대체 이게 무슨 뜻이지? 또 다른 마법의 장소란 말인가? 아니면 그 석상에 뭔가 추가적인 기능이 있다는 걸 보여주는 건가? 샤먼을 한번 찾아가 봐야겠군. 아니면 메인 섬 북서쪽으로 가서, 현지 만 중 한 곳에서 길을 찾아볼 수도 있겠지.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "알론소 데 말도나도는 유카탄 반도의 북쪽에서 타야살로 가는 또 다른 길이 있다고 말했다. \n즉, 나는 셀바 깊숙한 곳으로 들어가는 길을 찾아야 한다는 뜻이지. \n내가 찾아야 할 길은 북서쪽 메인에 있는 만 중 하나에서 시작될 가능성이 높다.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// решаем - титры или фриплей 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "끝났다. 내 오랜 여정의 끝이구나. 감옥에 갇힌 내 형제를 구하는 일이 결국 그와의 마지막 싸움을 준비하는 것일 줄은 상상도 못 했지! 내가 우리의 세계를 거의 멸망시킬 뻔했다니. 신께 감사드린다, 이제 모두 끝났어\n이제 더 이상 카리브에 나를 붙잡아 둘 것은 없다. 집, 프랑스로 돌아갈 시간이다. 하지만... 정말로 내가 그걸 원하는 걸까?";
				link.l1 = "그래, 나는 유럽으로 돌아갈 거야.";
				link.l1.go = "final_1";
				link.l2 = "아니, 나는 여기 카리브에 머물 거야.";
				link.l2.go = "final_2";
    		}
			// фэйловый финал 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("Voice\English\military02.wav");
				dialog.text = "대령님 말씀 들었지? 반란군이 저기 숨어 있대! 전부 뒤져, 집을 샅샅이 뒤집고 보이는 놈들 전부 잡아! 어서 움직여!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
			/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "여기가 매복하기에 가장 좋은 곳이군. 여기서 피네트가 오기를 기다려야겠다.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}*/
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "흠. 이 이야기는 뭔가 수상하군. 내 생각엔 세인트 존스에서 온 그 러거선은 애초에 존재하지 않았던 것 같아. 그 중위가 자기 군사 작전에 나를 끌어들이고 있어. 내가 그럴 이유가 뭐지? 난 네덜란드랑 전쟁 중도 아닌데... 어떻게 해야 하지? 이곳에서 일이 엉망이 되기 전에 그냥 떠나서 저놈들을 악마에게나 던져버릴까, 아니면 남아 있을까?";
				link.l1 = "나가.";
				link.l1.go = "FMQN_1";
				link.l2 = "가만히 있어.";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "그래, 상자는 준비됐어. 필요한 재료를 전부 내가 직접 찾아볼 수도 있겠지만, 차라리 파데이를 만나러 가는 게 낫겠어. 그 사람이라면 뭐든 구해올 수 있을 것 같으니까.";
    			link.l1 = "*생각을 소리내기 옵션을 사용해서 탄약 수집을 마무리하시오*";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "그러니까, 우리는 롱보트 여섯 척을 만들어야 해. 그러려면 목수 한 명, 판자 20개, 가죽 꾸러미 10개가 필요해.";
    			link.l1 = "*생각을 말하기 옵션을 사용해 롱보트 제작을 시작하십시오*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "그래서 이 낡은 목재 더미를 그냥 산산이 날려버릴 생각이야. 확실하게 하려면 화약 300단위만 있으면 돼.";
    			link.l1 = "*Thinking Out Loud 옵션을 사용해 화약 배치를 지시하시오*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+" 출구가 막혔어! 뭔가 무거운 걸로 문을 막아버린 것 같아! "+RandSwear()+"\n쉿... 뭐야, 이게?";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "여기가 끝이군... 이제 더 이상 갈 곳이 없어\n 돈 엔리코가 진심이었다는 게 분명해졌어: 이 지하 감옥에서 나갈 방법이 없어. 수면 근처에서 두 번째 문을 찾았을 때 잠깐 희망이 있었지만, 이제는... 시간이 얼마나 흘렀는지도 모르겠어 - 이 어두운 터널에서 얼마나 숨어 있었던 거지? 반나절, 아니면 하루 종일? 이곳은 관처럼 조용하고 무섭기만 해\n 예전에 여기, 바로 이곳에 교회가 있었지. 기도하기에 이보다 더 완벽한 곳은 없겠군. 나는 너무 많은 죄를 지었어, 너무나도 많이... 여기서 기도하고 잠들겠어, 상처와 피로가 나를 죽이고 있으니. 운이 좋다면, 다시는 일어나지 않겠지...";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
			{
				dialog.text = "";
    			link.l1 = "나, 샤를 드 모르, 프랑스 선장이자 귀족은 내 자신과 양심에게 맹세한다. 이제 해적이었던 과거와는 영원히 결별하겠노라고!";
    			link.l1.go = "Good_Choice";
				link.l2 = "그래! 그래! 아하하!! 내가 해냈어, 살아남았어! 잘 봐라, 조로! 지옥에나 가라, 마커스! 이제 나 혼자다! 찰리 프린스는 죽었을지 몰라도, 샤를 드 모르는 누구도 절대 못 죽인다!";
    			link.l2.go = "Bad_Choice";
			}
			// <-- legendary edition
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog")) {
				dialog.text = "우리가 뭘 해야 하지?";
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime")) {
					DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
					dialog.text = "... 물론이지, 르바쇠르는 바보가 아니야. 아니었으면, 왜 바로 지금 우리를 체포하려고 하겠어?\n그리고 한마디도 안 했잖아!\n"+dialog.text;
				}
				
				DeleteAttribute(link, "l1");
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena")) {
					link.l1 = "헬렌, 왜 이렇게 조용해?";
					link.l1.go = "tonzag_jail_helena";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary")) {
					link.l2 = "메리, 왜 그렇게 기뻐 보여?!";
					link.l2.go = "tonzag_jail_mary";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu")) {
					link.l3 = "티칭이투? 상황에 맞는 말을 해 봐.";
					link.l3.go = "tonzag_jail_tichingitu";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag")) {
					link.l4 = "에르퀼, 들리나? 우리 이제 어떻게 할 거야?";
					link.l4.go = "tonzag_jail_tonzag";
				}
				
				link.l5 = "어쩔 수 없군. 당분간 미셸의 신발을 신어야겠어.";
				link.l5.go = "tonzag_exit";
			}
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic")) {
				dialog.text = "";
				link.l1 = "이런 맙소사, 헤르퀼을 죽였어!";
				link.l1.go = "exit";
				link.l2 = "이 자식들아!";
				link.l2.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
				AddDialogExitQuestFunction("Tonzag_GFAfterShot");
			}
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame")) {
				dialog.text = "이런 밤이 다 있나! 내가 왜 그녀 말을 들었지? 형 말이 맞았어 – 여기 여자들은 완전히 달라. 혹시 럼주에 뭔가 넣은 건가?";
				link.l1 = "잘 시간이다, 그리고 나서 카르타헤나로 간다!";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

				AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk")) {
				dialog.text = "단 하나도 도둑맞은 게 없는데, 모든 게 여기저기 흩어져 있군. 귀중품조차 손도 안 댔어. ";
				link.l1 = "그 자들은 나를 털려고 한 게 아니었어 - 뭔가 특정한 걸 찾고 있었지. 그런데 그게 뭘까? 그리고 더 중요한 건, 누구를...?
\n";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

				AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_4");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki")) {
				dialog.text = "밤이 될 때까지 기다렸다가 공격하자!";
				link.l1 = "그동안 우리가 장주를 준비하기 시작하겠소.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

				AddDialogExitQuest("PZ_ShturmZvezdy");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu")) {
				dialog.text = "오, 맙소사... 안 돼, 안 돼, 안 돼... ";
				link.l1 = "";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");
				
				LAi_SetActorType(pchar);
				LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva")) {
				dialog.text = "오, 신이시여, 오, 신이시여, 오, 신이시여... 왜 이러십니까? 오, 신이시여, 왜... 하지만 나는 할 수 있는 건 다 했는데...";
				link.l1 = "이 모든 게 내 잘못이야, 전적으로 내 탓이야. 내가 제때 도착하지 못했어. 정말 미안해... 제발, 제발 용서해 줘.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
			}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("정말 지옥 같은 싸움이었지... 이제 도망친 겁쟁이들을 불러낼 수 있겠군...","하! 정말 쉬웠군. 그리고 저 육지 촌놈들은 그냥 뿔뿔이 흩어졌지!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("흠... 이제 뭘 해야 하지?","이제 어떻게 해야 하지?");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "동료를 부르시오.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "아침까지 쉬시오.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "밤이 될 때까지 쉬시오.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "다음 아침까지 쉬십시오.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "노예들을 선원으로 들여라.";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "가장 가까운 도시를 점령하기 시작해.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait")) 
	        {
	        	Link.l7 = "쉬어야겠군...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l8 = "화기의 탄약을 바꾸고 싶어.";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "머스킷의 탄약을 바꾸고 싶어.";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "전투에 사용할 주무기를 고르고 싶어.";
					Link.l10.go = "SetPriorityMode";
			}
			
			Link.l19 = "나는 정기적으로 사용할 물약을 고르고 싶어.";
			Link.l19.go = "ChoosePotion";
			
			//--> Голландский гамбит
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "지도에 표시된 좌표를 이용해서 섬을 찾아봐.";
	    		Link.l11.go = "Seek_AbyIsland";
	    	}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "아담 레이너를 불러와라.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "아담 레이너를 체포하라.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			//<-- Ложный след
			// Addon 2016-1 Jason Пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
	        {
	        	Link.l17 = "상자 안의 물품을 모두 세어 보고, 피카르를 위해 탄약을 계속 모을지 결정해.";
	    		Link.l17.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l17 = "마라카이보 농장을 공격하라고 명령을 내려라.";
	    		Link.l17.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l17 = "장주를 만들라고 명령을 내려라.";
	    		Link.l17.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l17 = "쓰러진 방벽으로 화약을 운반하라는 명령을 내려라.";
	    		Link.l17.go = "mtraxx_powder";
	    	}
			// Jason Долго и счастливо
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter") 
	        {
	        	Link.l18 = "결혼식을 생각해 봐.";
	    		Link.l18.go = "LH_marry";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
	        {
	        	Link.l18 = "청혼을 하시오.";
	    		Link.l18.go = "LH_marry_3";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town") 
	        {
	        	Link.l18 = "축하 준비를 해라.";
	    		Link.l18.go = "LH_marry_4";
	    	}
			//--> завершение игры
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l15 = "카리브 해에서 할 일을 마치고 유럽으로 항해하시오.";
	    		Link.l15.go = "final_1";
	    	}
			//<-- завершение игры
			Link.l20 = RandPhraseSimple("지금은 안 돼. 시간이 없어.","그럴 시간 없어, 할 일이 너무 많아.");
			Link.l20.go = "exit";
		break;
		
		case "tonzag_exit":
			DialogExit_Self();
			AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;
		

		
		case "SetGunBullets":
			Dialog.Text = "탄약 종류를 선택하십시오:";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;
		
		case "SetGunBullets2":
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "탄약 종류를 선택하십시오:";
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "싸움이 시작되면 나는 다음을 사용할 거야:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.PriorityMode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.PriorityMode = 2;
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "물약을 선택하십시오:";
	    	Link.l1 = "치유 물약.";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "엘릭서.";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "혼합물.";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "생강 뿌리.";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "럼.";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "와인.";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "포션을 자동으로 선택하고 싶어.";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "잠깐, 마음이 바뀌었어.";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("A healing essence will be used by default.");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("An elixir will be used by default.");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("A mixture will be used by default.");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("A ginger root will be used by default.");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("Rum will be used by default.");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("Wine will be used by default.");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("Potions will be selected automatically.");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            int needCrew = 500;
			if(CheckOfficersPerk(pchar, "Troopers")) needCrew = 300;
            bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "우리가 지금 바로 마을을 점령하려 들 수도 있겠지만, 우리 배는 요새의 대포 사격을 오래 버티지 못할 거야, 그리고 상륙조를 보낼 수도 없지.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
					if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
					{
						Dialog.Text = "아니, 아직 그렇게 미치진 않았어...";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "LosTeques_ExitTown")
						{
							Dialog.Text = "정보도 모른 채 이 광산을 공격하는 건 아무 의미가 없어. 금과 은이 얼마나 캐지는지 먼저 알아봐야 해. 그렇지 않으면 내 부하들을 헛되이 죽게 만드는 셈이니까.";
							Link.l1 = "...";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "Attack "+GetCityName(chr.City)+".";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
							{
								Link.l1 = "장난 그만쳐! 멈춰!";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "장난 그만 쳐! 멈춰!";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "무기를 들어라!";
							Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "멈춰라!";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "헤헤! 선원 수가 부족해; 최소한 필요해 "+needCrew+" 남자들.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "흩어지지 마! 계속 공격해!";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "노예들 중 누구도 선원으로 합류하려 하지 않는다.";
	            Link.l1 = "그놈들 다 지옥에나 가라!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "배에 새 선원을 태울 자리가 없어.";
	                Link.l1 = "헤헤! 선원 일부를 다른 배로 옮겨야겠군.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "당신의 선원은 다음으로 보충할 수 있습니다 "+pchar.GenQuest.SlavesToCrew+" 당신 밑에서 일하고 싶어하는 노예들입니다. 받아들이시겠습니까?";
	                Link.l1 = "Yes";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "No";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			bOk = ShipBonus2Artefact(pchar, SHIP_MEMENTO) && CheckAttribute(&RealShips[sti(pchar.Ship.Type)], "DeadSailors.RecruitSlaveBonus");
			if(!bOk)
			{
				// belamour legendary edition перк получил время работы, старый метод не подходит
				if (GetOfficersPerkUsing(pchar, "IronWill"))
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
				}
				else
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
				}
			}
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "이 멋진 배는 이제 내 거고, 여기서 내가 선장이야! 하지만 선원 전부를 죽여야 했던 건 아쉽군.";
			Link.l1 = "상륙할 시간이군...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "어느 동료를 부를까?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "다음에 하자.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> Голландский гамбит
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "위도와 경도를 확인할 항해 도구가 없는 게 아쉽군. 섬은 다음에 다시 찾아봐야겠어. ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//<-- Голландский гамбит
		
		//--> Ложный след
		case "FalseTrace_Cabin":
			dialog.text = "보선! 아담 레이너를 당장 내게 데려와라!";
			link.l1 = "알겠어요, 선장님!";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//<-- Ложный след
		
		//--> LSC, приколы со стуком в дверь
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "자, 두드렸으니 이제 대답을 기다려 보자...";
			link.l1 = "(기다려)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "그래, 문을 두드렸으니 이제 대답을 기다려 보자...";
			link.l1 = "(기다려)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "자, 두드렸으니 이제 대답을 기다려 보자...";
			link.l1 = "(기다려)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "자, 두드렸으니 이제 대답을 기다려 보자...";
			link.l1 = "(기다려)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "자, 두드렸으니 이제 대답을 기다려 보자...";
			link.l1 = "(기다린다)";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "그가 문을 열지 않네... 내가 비밀 노크를 잘못한 것 같아. 좋아, 내일 다시 와서 시도해 보지. 오늘은 절대 문을 열지 않을 거야.";
			link.l1 = "(떠난다)";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("Voice\English\YouFace.wav");
			dialog.text = "이런 젠장! 그가 대답하고 문을 열었어! 이제 들어갈 수 있겠군...";
			link.l1 = "(입장)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//<-- LSC, приколы со стуком в дверь
		
		// суп из черепахи
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("Voice\English\EvilPirates02.wav");
			dialog.text = "카람바! 저게 바로 르바쇠르를 위한 늦은 지원군이군... 이 문으로는 절대 나갈 수 없겠어... 좋아, 티보처럼 해야지 - 창문으로! 어차피 그 녀석도 어떻게든 빠져나갔으니까!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// защита Сен-Пьера
		case "SP_defend":
			PlaySound("Voice\English\military02.wav");
			dialog.text = "그러니까, 우리의 임무는 저 빌어먹을 스페인 놈들의 공격을 막아내고 생피에르를 구하는 거다. 요새는 이미 점령당했고, 거리에서는 전투가 벌어지고 있어. 생피에르 만에는 강력한 함대가 있고, 그놈들은 전열함을 기함으로 삼고 있지. 지금 공격하는 건 의미 없어; 요새와 도시는 적의 통제 아래라서 우리가 항구에 상륙하도록 두지 않을 거야\n그래서 나는 정글을 통해 이동해서 도시 성문을 통해 뒤에서 그놈들을 치기로 결정했다. 요새와 도시에서 스페인 놈들을 몰아내면, 그다음에 함대를 상대할 거다. 요새의 화력 지원이 없으면 훨씬 더 취약해질 테니까\n이건 쉽지 않을 거다. 그래서 나는 평소 급여에 더해 선원들에게 추가로 십만 페소를 분배하라고 명령했다. 움직이자!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// финал игры
		case "final_1": // Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
			{
				dialog.text = "잠깐만, 내가 어디로 가는 거지? 파리의 허락 없이 총독 자리를 떠날 수는 없어! 그렇지 않으면 프랑스로 돌아갔을 때 위임받은 식민지를 무단으로 버린 죄로 분명히 체포될 거야. 파리여, 그리울 거다 ...\n";
				link.l1 = "";
				link.l1.go = "exit";
				EndQuestMovie();
			}
			else
			{
				dialog.text = "그럼 더 이상 시간을 낭비하지 맙시다! 내 사랑스러운 가스코뉴의 들판이 너무 그립군요! 출항하라!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "이게 옳은 결정이라고 생각해! 여기까지 와서 이제 와서 좋은 옛 유럽에 내가 남아 있을 이유가 뭐가 있겠어? 게다가, 언제든 내가 원하면 프랑스로 돌아갈 수도 있으니까!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN_1":
			dialog.text = "그게 제일 좋은 방법이야. 내가 배에 올라타서 여기서 떠나야겠어.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "아니, 절대 못 가. 난 여기 남을 거야. 하지만, 젠장, 여기서 뭘 기다리며 멍하니 있을 순 없지. 필립스버그 항구로 가서 상황을 조사해야겠어. 그놈들 손아귀에서 눈먼 꼭두각시가 될 생각은 없어.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // анализируем содержимое сундука
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
			{
				dialog.text = "상자에 차가운 강철 서른 자루가 들어 있지! 이제 멈춰야 할까, 아니면 총기, 화약, 약초를 더 모아야 할까?";
				link.l1 = "이 정도면 충분해!";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "아니, 이 상자를 계속 채워야겠어.";
				link.l2.go = "exit";
				// belamour legendary edition
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
				{
					link.l3 = "파데이의 상자에 내용물을 채우고, 남는 것은 가져가라."; 
					link.l3.go = "mtraxx_ammo_1";
				}
			}
			else
			{
				dialog.text = "차가운 강철 서른 자루는 아직 모으지 못했어! 더 가져와야겠군.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "상자를 잠그고 그것을 플랜테이션으로 밀반입할 계획을 세운다.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "가라, 돌격해! 만세!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
			{
				if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
				{
					dialog.text = "필요한 자재는 모두 준비됐으니, 지금 바로 장주선을 만들기 시작해야겠어.";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "나는 이 일을 해낼 만한 경험 많은 목수가 없어. 장교 한 명을 이 자리에 배치해야겠어.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "자재가 부족해. 최소한 널빤지 20묶음과 가죽 10타래가 더 필요해.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
			{
				if (GetCrewQuantity(pchar) >= 20) // наличие команды
				{
					dialog.text = "모든 준비가 끝났으니 한바탕 터뜨려 보자!";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "화약을 운반하려면 최소한 20명은 필요해.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "화약이 부족해, 최소 300개는 필요하다.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "문이었나?";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "맞아! 손님이 왔어... 얀?.. ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
		// belamour legendary edition -->
		case "Good_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "good";
			DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5); 
			DialogExit_Self();
		break;
		
		case "Bad_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
			Achievment_Set("ach_CL_97");
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "18");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
			DialogExit_Self();
		break;
		// <-- legendary edition
		
		// Jason Долго и счастливо
		case "LH_marry":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			string sTemp = sld.name;
			dialog.text = "너와\n "+sTemp+" 오랜 시간 함께했고, 우리의 인연은 어떤 교회의 서약보다도 굳건하지만, 이 순간을 우리 둘 다 기억하길 바라네. 그러니 내가 그녀에게 청혼할 장소를 정해야겠어:";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "이슬라 테소로 - 이 섬은 우리 이야기에서 아주 중요한 의미를 가지지. 내 생각엔 이보다 더 좋은 곳은 없을 거야 - 사부 마틸라 만은 해질 무렵 정말 매혹적이거든!";
				link.l1.go = "LH_marry_1_1";
			}
			link.l2 = "토르투가는 우리 시대의 자유의 상징이지. 그리고 등대에서 바라보는 토르투 해협의 풍경은 어느 화가의 붓에도 어울릴 만큼 아름답다!";
			link.l2.go = "LH_marry_1_2";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l3 = "자메이카에는 정말 많은 것이 있지! 그리고 포틀랜드 코브에서 맞이하는 새벽은 내가 상상하는 지상낙원이야.";
				link.l3.go = "LH_marry_1_3";
			}
		break;
		
		case "LH_marry_1_1":
			pchar.questTemp.LongHappy.Shore = "Shore_ship1";
			AddQuestRecord("LongHappy", "2_1");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "하지만 교회의 엄숙한 의식 없이는 이 일을 할 수 없어 – 모든 것은 교회법에 따라 이루어져야만 아버지께서 내 선택을 받아들이실 거야. 그래서 신부가 필요하고, 이 역할에 가장 어울리는 사람은 베누아 아빠트라고 생각해. 그는 아버지의 오랜 친구이기도 하고, 내가 신세계에서 모험을 시작하게 된 것도 그분 덕분이야. 내 생각에 그분께서 이 영광을 허락해 주실 거라고 믿어.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_2":
			pchar.questTemp.LongHappy.Shore = "Mayak6";
			AddQuestRecord("LongHappy", "2_2");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "하지만 교회의 엄숙한 의식 없이 이 일을 할 수는 없어. 모든 것은 교례에 따라 이루어져야만 아버지께서 내 선택을 받아들이실 수 있지. 그래서 신부가 필요해, 그리고 이 역할에 가장 어울리는 분은 베누아 아빠트뿐이라고 생각해. 그는 아버지의 오랜 친구이시고, 내가 신세계에서 모험을 시작하게 된 것도 그분 덕분이야. 분명히 내 부탁을 들어주실 거라고 생각해.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_3":
			pchar.questTemp.LongHappy.Shore = "Shore36";
			AddQuestRecord("LongHappy", "2_3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "하지만 교회의 엄숙한 의식 없이는 이 일을 할 수 없어. 모든 것은 교례에 따라 진행되어야만 내 아버지도 내 선택을 받아들일 수 있을 거야. 그래서 신부가 필요하고, 이 역할에 가장 어울리는 사람은 베누아 아빠트라고 생각해. 그는 우리 아버지의 오랜 친구이자, 내 신세계 모험이 그의 손에서 시작됐지. 분명 나를 위해 이 영광을 허락해 주실 거라고 믿어.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_2":
			AddQuestRecord("LongHappy", "3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "글쎄, 이런 일은 인간의 엄숙함 없이도 일어날 수 있지. 그래도 나는 이것을 함께 논의하고 싶군 "+sTemp+" 잠시 후에.";
			link.l1 = "";
			link.l1.go = "exit";
			pchar.questTemp.LongHappy = "choose";
		break;
		
		case "LH_marry_3":
			dialog.text = "좋아, 난 준비됐어!";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_MarryOffer();
		break;
		
		case "LH_marry_4":
			if (LongHappy_CheckGoods())
			{
				dialog.text = "모든 준비가 끝났어!";
				link.l1 = "";
				link.l1.go = "exit";
				LongHappy_OnIslaTesoro();
			}
			else
			{
				dialog.text = "필요한 물품과 돈이 아직 모이지 않았어!";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
	}
}

void DialogExit_Self()
{
    SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
    DialogExit();
	locCameraSleep(false); //boal
}
