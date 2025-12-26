// шаман команчей Змеиный Глаз
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
			if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
			{
				dialog.text = "안녕하시오, 내 창백한 친구.";
				link.l2 = "나도 너를 다시 보게 되어 기쁘다, 내 붉은 피부 형제여. 또다시 너에게 중요한 일이 있네.";
				link.l2.go = "calendar";
				break;
			}
			dialog.text = "안녕하시오, 내 창백한 친구.";
			link.l1 = "나도 반갑다, 스네이크 아이.";
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
			{
				link.l2 = "당신이 부탁한 부적들을 가져왔어. 거래하자.";
				link.l2.go = "SnakeEye_potion";
			}
			if (CheckAttribute(pchar, "questTemp.LSC")) // был в LSC
			{
				if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
				{
					link.l2 = "네 탬버린을 찾았어, 스네이크 아이. 한 번 봐봐.";
					link.l2.go = "LSC_buben";
				}
				if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
				{
					link.l2 = "재미있는 인디언 파이프를 찾았어, 스네이크 아이. 한번 봐.";
					link.l2.go = "LSC_tube";
				}
				if (!CheckAttribute(npchar, "quest.LSC_hello"))
				{
					link.l2 = "안녕, 주술사. 내가 그 조각상을 사용해서 정말 놀라운 여정을 겪었어. 네 말이 전부 맞았어. 난 배들의 묘지와 하얀 선장, 심지어 보급품이 있는 화물창까지 찾았어!";
					link.l2.go = "LSC_hello";
				}
				if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
				{
					link.l3 = "스네이크 아이, 네 도움이 필요해.";
					link.l3.go = "Saga_nathaniel";
				}
			}		
			NextDiag.TempNode = "First time";
		break;
		
	//---------------------------------------- первая встреча------------------------------------------------
		case "SnakeEye":
			dialog.text = "안녕하시오, 내 창백한 친구.";
			link.l1 = "안녕, 주술사. 내가 네 친구라고 왜 생각하지?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "나는 많은 것을 알고 있지만, 항상 무엇을 아는지는 정확히 모르지. 너는 목적을 가지고 여기 왔어. 운명이 너를 이끌었고, 나는 너를 도우려고 여기 있지.";
			link.l1 = "알아두면 좋겠군! 사실 나는 네 도움이 필요해서 여기 온 거야, 붉은 피부 친구. 바로 묻지. 왜 호크의 아내에게 쿠쿨칸에 대해 말한 거지?";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "죽은 물고기도 떠내려가지. 살아 있는 인간은 운명에 이끌려 목표에서 목표로 옮겨 다니는 법. 사슬에 묶인 선장이 셀바에서 악한 자들에게 쫓기며 품었던 목표는 쿠쿨칸 상상이었지.\n그가 자신을 희생한다면, 이곳에서 아주 멀리 떨어질 수도 있었을 거야.";
			link.l1 = "나는 아무것도 이해하지 못했어. 너희 신의 조각상은 대체 무엇에 쓰는 거고, 호크는 어떻게 그 먼 길을 걸어서 지금까지 아무도 못 찾게 된 거야?";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "만약 쿠쿨칸이 호크를 삼켰다면, 어디든 그를 뱉어낼 수 있지. 어쩌면 다른 세계일 수도 있어. 쿠쿨칸은 나를 세 번이나 삼켰다네. 그리고 매번 다른 곳에 떨어졌지. 오래전에 나는 여기 도착해서 더 이상 위험을 감수하지 않기로 했네. 나는 쿠쿨칸의 입으로 들어가지 않았고, 그가 희생자들을 어디로 뱉어내는지 알지 못하네.";
			link.l1 = "이런, 이건 내 이해를 완전히 벗어나는군! 돌 우상이 사람을 멀리 순간이동시킬 수 있다는 말이오?";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "그뿐만이 아니야. 쿠쿨칸은 공간뿐 아니라 시간까지도 지배하지. 아니, 어쩌면 그 이상일지도 몰라. 나는 사슬에 묶인 선장에게 사람을 집어삼키는 황금상에 대해 이야기했지. 어쩌면 그는 추격자들이 가까워지는 걸 보고 위험을 감수하기로 한 걸지도 몰라...";
			link.l1 = "잠깐, 저 조각상은 돌로 만들어졌잖아. 그런데 너는 금으로 된 걸 말하는 거지...";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "자정이 되면 우상이 생명을 얻어 황금으로 변한다네. 이 순간, 쿠쿨칸의 영혼이 그 안에 깃들지. 가까이 다가가면 조심하게, 자네는 다른 곳에서 해돋이를 보게 될지도 모르니. 심지어 하늘의 별들조차 자리를 옮길 수 있다네. 아직 태어나지 않은 이들을 만나거나, 오래전에 죽은 자들의 탄생을 목격하거나, 아예 태어나지 않은 자들의 탄생을 보게 될 수도 있지.";
			link.l1 = "뭐야... 또 수수께끼야... 넌 참 흥미로운 녀석이군, 스네이크 아이. 네가 믿는 신 쿠쿨칸과 세 번이나 마주치고 살아남았다고 했지. 그렇다면 내가 믿지도 않는 신의 우상에 운을 걸어보지 않을 이유가 뭐가 있겠어?\n";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "안타깝군. 네가 믿지 않는다니 유감이야. 어쩌면 쿠쿨칸께서 직접 너를 부르시고 조상들의 땅을 떠나게 하셨을지도 몰라. 하지만 넌 아직 그분의 목소리를 듣지 못하는구나. 모든 일에는 다 이유가 있는 법이지. 만약 네가 위험을 감수하기로 마음먹었다면, 내가 매번 살아남을 수 있었던 건 훌륭한 코만치 약 덕분이었다는 걸 알아둬.";
			link.l1 = "코만치? 또 다른 부족이냐?";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "그건 적들이 내 민족을 부르는 말이오. 나는 다시는 그들을 볼 수 없겠지. 이 약은 기력과 인내를 회복시켜주고, 상처를 치유하며 강한 독에서도 구해주오. 몇 병이 필요하겠지만, 내게는 세 병만 남았소.\n원래는 네 병이었으나, 이상한 곳에서 하나를 잃었소. 마치 백인들의 배가 묻힌 묘지 같았지. 내가 이 세상에서 여정을 시작한 곳이기도 하오. 어쩌면 쿠쿨칸이 선장을 거기에 내던졌는지도 모르지. 그렇다면, 나는 그가 부럽지 않소.";
			link.l1 = "여기가 어디지? 배들의 무덤인가?";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "이상한 곳이야... 존재해서는 안 되는데, 실제로 존재하지. 그곳에는 피부색 때문에 사람을 죽이는 자들이 살아. 그들은 쿠쿨칸이 나를 뱉어낸 큰 배 안에 물자를 보관하지. 나는 도둑들을 막으려고 지키는 그 배의 창고 안에는 들어가지 않았어; 그들은 믿음직한 이웃이 아니거든. 네가 그곳에 가게 된다면, 다른 출구를 찾아. 창고 안에 들어가면 문제가 생길 거야.\n백인 소년이 아직 살아 있다면 다른 조각상을 찾는 걸 도와줄 거야. 이 흰 구슬을 그에게 줘. 그는 이런 걸 좋아하거든.";
			link.l1 = "흠. 머리가 벌써 어지러운데 점점 더 흥미로워지는군. 계속해, 내 붉은 피부 형제여.";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			Log_Info("You have received a white pearl");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "jewelry52");
			dialog.text = "만약 선장이 살아 있다면, 아마도 많이 아플 거야. 내가 약을 줄 시간이 없었거든. 거기서 내 탬버린을 찾아 줘. 그건 할아버지께 받은 거야. 내가 잃어버린 가방에는 이것저것 많이 들어 있지만, 난 탬버린만 필요해. 그게 없으면 영혼들과 대화하기가 힘들거든.";
			link.l1 = "음, 이곳이 꽤 흥미로운 곳처럼 들리는군! 호크가 거기로 순간이동됐기를 바라자고... 네 물약을 줄 수 있겠어?";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "내가 그것을 주겠소. 하지만 그 대가로 이곳 부적 세 개를 나에게 주어야 하오: "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian)+", "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet)+" 그리고 "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg)+". 부적 하나당 플라스크 하나씩이오. 그러니 공평하오. 모든 부적을 모으면 다시 오시오. 그때 서로 교환하겠소. 내가 욕심쟁이라고 생각하지 마시오. 아니면 부적을 찾으면서 생각이 바뀔지도 모르지.";
			link.l1 = "나는 그렇게 생각하지 않을 거야. 기다려, 스네이크 아이. 곧 돌아올게.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			npchar.quest.amulet = "true";
			AddQuestRecord("BaronReturn", "3");
			AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
			AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
			AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
			sld = characterFromId("Danielle");
			sld.quest.talk = "SnakeEye";
			pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
			pchar.questTemp.HelenDrinking.GiveAmulets = true;
			
			//if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap4_Start"))
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))	// Временно так
			{
				// Квест "Путеводная звезда", начало 4 этапа
				PChar.quest.PZ_Etap4_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap4_Start.win_condition.l1.location = "Shore9";
				PChar.quest.PZ_Etap4_Start.win_condition = "PZ_Etap4_Start";
				locations[FindLocation("Shore9")].DisableEncounters = true;
			}
		break;
		
		// даёт зелья - идем на телепортацию
		case "SnakeEye_potion":
			dialog.text = "좋아, 친구. 쿠쿨칸에게 가려면 내게 부적을 가져왔나?";
			link.l1 = "그래. 나는 한때 사슬에 묶인 선장이었던 네이선리얼이 떠났던 그 여정을 똑같이 떠날 준비가 되어 있다.";
			link.l1.go = "SnakeEye_potion_1";
		break;
		
		case "SnakeEye_potion_1":
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
			TakeNItems(pchar, "Ultimate_potion", 3);
			Log_Info("You have given amulets");
			Log_Info("You have received three versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "이 물약들을 가져가라. 기억해라, 쿠쿨칸이 너를 토해내자마자 반드시 하나를 마셔야 한다. 그렇지 않으면 죽거나 중병에 걸릴 것이다. 그리고 창백한 자들이 물자를 보관하는 화물칸에는 가지 마라. 배를 떠나는 다른 길이 있다. 사실 두 가지 길이 있다. 첫날 밤에 붉은 여자를 찾아라, 매우 중요하다. 내가 해줄 수 있는 말은 여기까지다.";
			link.l1 = "그것은 기억하겠소, 형제여.";
			link.l1.go = "SnakeEye_potion_2";
		break;
		
		case "SnakeEye_potion_2":
			dialog.text = "그럼 가라. 자정에 쿠쿨칸을 건드리면 네놈을 삼켜 버릴 것이다. 내가 영혼들을 불러 길을 안내하게 하마.";
			link.l1 = "고맙소, Snake Eye. 내 걱정은 하지 마시오, 다 잘 될 것이오. 우리는 다시 만날 것이오!";
			link.l1.go = "SnakeEye_potion_3";
		break;
		
		case "SnakeEye_potion_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Saga.BaronReturn = "first_teleport";
			pchar.questTemp.Dolly = true; // телепорты работают!
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // не пускать офицеров в локу телепорта
			DeleteAttribute(npchar, "quest.amulet");
			AddQuestRecord("BaronReturn", "4");
			sld = characterFromId("Danielle");
			sld.quest.talk = "teleport";
			pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
			QuestPointerToLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		// пришёл из LSC
		case "LSC_hello":
			dialog.text = "그대를 다시 보게 되어 기쁘오, 친구여. 어떻게 배 무덤에서 돌아왔소?";
			link.l1 = "네가 말해준 대로 거기서 쿠쿨칸의 조각상을 찾았어. 화이트 보이, 올레 크리스티안센이 도와줬지. 조각상은 바다에 가라앉아 있었지만 내가 겨우 도달했어. 그 조각상이 나를 도미니카의 인디언 마을로 순간이동시켰어.";
			link.l1.go = "LSC_hello_1";
			npchar.quest.LSC_hello = "true";
		break;
		
		case "LSC_hello_1":
			dialog.text = "Monkitekuvri가 거기서 너를 만났나?";
			link.l1 = "흠. 몽키테쿠브리? 그게 누구지?";
			link.l1.go = "LSC_hello_2";
		break;
		
		case "LSC_hello_2":
			dialog.text = "그는 마을 촌장이오.";
			link.l1 = "나는 그의 이름을 묻지 않았어. 어쩌면 그가 몽키테쿠브리였을 수도 있고, 아닐 수도 있지.";
			link.l1.go = "LSC_hello_3";
		break;
		
		case "LSC_hello_3":
			dialog.text = "그 자 머리 위에 새 깃털로 만든 거창한 머리장식을 쓰고 있었나?";
			link.l1 = "그래, 그랬지. 깃털이 아주 많았어... 정글에 있는 앵무새를 죄다 털 뽑은 것 같더라고.";
			link.l1.go = "LSC_hello_4";
		break;
		
		case "LSC_hello_4":
			dialog.text = "그의 이름은 몽키테쿠브리야. 저건 앵무새 깃털이 아니라 독수리 깃털이지. 이 머리장식은 내 거야. 쿠쿨칸이 날 다시 뱉어냈을 때 내가 몽키테쿠브리에게 줬지. 그러고 나서 그들이 날 또 다른 조각상으로 데려갔어...\n";
			link.l1 = "이거 참 대단하군! 나도 쿠쿨칸에게 '제물로 바쳐졌'다네! 그리고 정신을 차려보니 여기, 첫 번째 동상 근처에 와 있었지.";
			link.l1.go = "LSC_hello_5";
		break;
		
		case "LSC_hello_5":
			dialog.text = "그래, 내 창백한 친구. 나 역시 여기서 여정이 끝났지.";
			link.l1 = "우상들이 원을 그리며 순간이동을 하네... 그런데 그게 무슨 의미가 있지? 스네이크 아이, 너는 무슨 생각이 있나?";
			link.l1.go = "LSC_hello_6";
		break;
		
		case "LSC_hello_6":
			dialog.text = "조각상들이 제대로 작동하지 않는 것 같군. 지금은 사람들을 여기저기로 옮기고 있지만, 원래는 한 곳으로 옮겨야 하거늘. 뭔가 잘못된 게 분명해.";
			link.l1 = "왜 그렇게 생각하시오?";
			link.l1.go = "LSC_hello_7";
		break;
		
		case "LSC_hello_7":
			dialog.text = "원 안에서 순간이동하는 건 아무 의미가 없으니까. 쿠쿨칸은 희생자들을 이리저리 옮기는 게 아니라 한 곳에 모두 모아야 해.";
			link.l1 = "그 한 곳이 어디란 말이오?";
			link.l1.go = "LSC_hello_8";
		break;
		
		case "LSC_hello_8":
			dialog.text = "이건 나에게도 아주 큰 비밀이야, 백인 형제여.";
			link.l1 = "알겠소. 좋아, 우상 따위 다 집어치우지. 다시는 그 근처에도 가지 않겠소. 나는 이미 사슬에 묶인 선장을 찾았으니, 더 이상 포탈을 돌아다닐 필요 없소.";
			link.l1.go = "LSC_hello_9";
			AddQuestRecord("BaronReturn", "12");
		break;
		
		case "LSC_hello_9":
			dialog.text = "네가 배 무덤에 갔을 때 말이야. 거기서 내 탬버린을 찾았니?";
			if (CheckCharacterItem(pchar, "buben"))
			{
				link.l1 = "그런 것 같소. 한번 보시오.";
				link.l1.go = "LSC_buben";
			}
			else
			{
				link.l1 = "아니오. 유감스럽게도 아직 찾지 못했소. 하지만 섬이 어디 있는지는 알고 있고, 그곳에 갈 수 있소. 당신의 탬버린을 찾아보겠소.";
				link.l1.go = "LSC_hello_10";
			}
		break;
		
		case "LSC_hello_10":
			dialog.text = "찾아줘, 내 창백한 친구야. 제발 부탁이야. 탬버린이 없으면 영혼들의 소리가 잘 안 들려.";
			link.l1 = "알겠어, 스네이크 아이. 또 보자!";
			link.l1.go = "exit";
		break;
		
		case "LSC_buben":
			RemoveItems(pchar, "buben", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "저건 내 탬버린이야. 고맙다, 창백한 친구야. 내가 보답할 수 있지. 이 무기를 너에게 주마. 너희 사람들이 아직 오래도록 갖지 못할 무기다. 이 무기는 내 시대의 창백한 자들이 쓰는 무기다.";
			link.l1 = "흥미롭군! 나한테 보여 줘, 내 붉은 피부 친구야...";
			link.l1.go = "LSC_buben_1";
		break;
		
		case "LSC_buben_1":
			GiveItem2Character(pchar, "pistol7");
			Log_Info("You have received a Colt revolver");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 3);
			dialog.text = "가져가. 남은 탄약은 세 개뿐이야, 나머지는 내가 다 썼지. 하지만 네가 직접 탄약 만드는 법을 배울 수도 있을 거야. 내가 배 묘지에서 탄약 부품 몇십 개를 잃어버렸으니, 거기서 찾아볼 수 있을 거야.";
			link.l1 = "오호! 이건 권총이잖아! 이런 건 처음 본다... 참 이상한 기계구나. 뭔가 돌아가는 장치가 있고... 다섯 발이나 들어가네! 멋진데!";
			link.l1.go = "LSC_buben_2";
		break;
		
		case "LSC_buben_2":
			dialog.text = "이건 콜트 리볼버라고 불린다. 자네 시대에는 이런 권총이 없어. 사용하기도 쉽지. 해머를 젖히고 방아쇠만 당기면 돼. 명중률도 좋아.";
			link.l1 = "고마워! 고마워, 스네이크 아이! 이걸로 내 적들에게 기분 좋은 깜짝 선물을 줄 수 있겠군... 아쉽게도 세 발밖에 없다는 게 문제지만...";
			link.l1.go = "LSC_buben_3";
		break;
		
		case "LSC_buben_3":
			dialog.text = "콜트 리볼버용 탄약 만드는 법을 스스로 익혀 보게. 그러면 자네는 시대의 위대한 전사가 될 것이야. 아, 창백한 내 형제여, 배 묘지에서 내 파이프를 찾아달라고 부탁하는 걸 깜빡했군. 아주 예쁜 파이프였지.";
			if (CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l1 = "하! 이게 누구의 색칠된 파이프인가 궁금했는데. 한번 봐봐.";
				link.l1.go = "LSC_tube";
			}
			else
			{
				link.l1 = "좋아. 네 파이프도 찾아볼게. 또 보자!";
				link.l1.go = "exit";
			}
			npchar.quest.LSC_tube = "true";
		break;
		
		case "LSC_tube":
			RemoveItems(pchar, "smoking_tube", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "이건 내 파이프야, 형제. 네가 찾아줘서 기쁘다. 그리고 그 대가로 또 다른 선물을 줄 수 있지. 이건 내가 예전에 얻은 백인들의 영리한 책이야. 나는 이걸 이해할 수 없어. 이 책을 읽고 이해할 수 있는 똑똑한 사람을 한번 찾아봐.";
			link.l1 = "고맙소, 스네이크 아이. 이 일에 관심 가질 만한 사람을 내가 아는 것 같소.";
			link.l1.go = "LSC_tube_1";
		break;
		
		case "LSC_tube_1":
			GiveItem2Character(pchar, "chemistry");
			Log_Info("You have received a Lavoisier's chemistry textbook");
			PlaySound("interface\important_item.wav");
			dialog.text = "그에게 줘, 하얀 형제. 이 책에는 백인들의 지혜가 담긴 큰 비밀이 들어 있어.";
			link.l1 = "좋아. 또 보자, 스네이크 아이!";
			link.l1.go = "exit";
		break;
		
		// лечение Натаниэля
		case "Saga_nathaniel":
			dialog.text = "듣고 있네, 창백한 얼굴의 형제여.";
			link.l1 = "나는 내가 배 무덤에서 찾고 있던 사슬에 묶인 선장을 데려왔소. 그는 매우 위독하오. 그를 고칠 수 있는 사람은 오직 당신뿐임을 알고 있소...";
			link.l1.go = "Saga_nathaniel_1";
		break;
		
		case "Saga_nathaniel_1":
			dialog.text = "쿠쿨칸이 그의 건강을 갉아먹었어. 내가 치유를 도울 수 있을 것 같아. 하지만 온전한 보름달이 지나야 할 거야.\n쿠쿨칸은 오래전에 선장을 삼켰고, 그 병이 그의 깊은 곳까지 퍼졌지.";
			link.l1 = "그를 치료해 주시오, 주술사! 필요한 건 뭐든 가져다주겠소!";
			link.l1.go = "Saga_nathaniel_2";
		break;
		
		case "Saga_nathaniel_2":
			dialog.text = "노력해 보겠다, 하얀 형제여. 나에게 아무것도 가져올 필요 없어. 나는 모든 걸 가지고 있지. 시간이 병을 키우지만, 사슬에 묶인 선장도 한 달이면 다시 건강해질 거야.";
			link.l1 = "고맙네, 내 붉은 피부 형제여. 또 한 번 내 목숨을 구해줬군.";
			link.l1.go = "Saga_nathaniel_3";
		break;
		
		case "Saga_nathaniel_3":
			dialog.text = "사슬에 묶인 선장은 내 오두막에 두고 가, 하얀 형제여, 그리고 걱정 말고 걸어가. 그의 아내도 데려와라, 내 의식을 보는 이는 없으니.";
			link.l1 = "좋아, 스네이크 아이. 다니엘을 데리고 가마. 또 보자!";
			link.l1.go = "Saga_nathaniel_4";
		break;
		
		case "Saga_nathaniel_4":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "treatment";
			sld = characterFromId("Nathaniel");
			RemovePassenger(Pchar, sld);
			LAi_SetStayType(sld);
			sld.location = "none";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
			pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;
		
		case "calendar":
			dialog.text = "듣고 있어, 친구.";
			link.l1 = "쿠쿨칸 조각상에 대해 나눈 이야기 기억나? 네가 '그것들이 사람들을 어떤 특별한 곳으로 이끌어야 한다'고 했잖아.";
			link.l1.go = "calendar_1";
		break;
		
		case "calendar_1":
			dialog.text = "기억하지, 백인 선장.";
			link.l1 = "나는 쿠쿨칸에게 잡아먹힌 사람들이 그 조각상들에게 어디로 끌려갔는지 알고 있어.";
			link.l1.go = "calendar_2";
		break;
		
		case "calendar_2":
			dialog.text = "어디?";
			link.l1 = "마야의 옛 도시 타야살로. 그곳은 마인 정글 깊숙한 곳에 위치해 있다.";
			link.l1.go = "calendar_3";
		break;
		
		case "calendar_3":
			dialog.text = "매우 흥미롭군. 이것을 어떻게 알았지?";
			link.l1 = "긴 얘기지, 스네이크 아이. 네가 어떻게 여기 오게 됐는지도 이해해. 아직 태어나지도 않았잖아, 안 그래?";
			link.l1.go = "calendar_4";
		break;
		
		case "calendar_4":
			dialog.text = "내 아버지조차도 그대 시대에 태어난 분이 아니오. 하지만 나는 그대 시대에 살고 있으니, 그것이야말로 큰 신비로다.";
			link.l1 = "사실 설명이 가능하네. 타야살에 사는 이차 사제 카넥이라는 자가 쿠쿨칸에게 이 세상에 인간으로 태어나 백인의 지혜를 흡수해 달라고 청했지. 그리고 시간의 구멍도 만들어서 미래에서 몇몇 사람들을 우리 시대로 순간이동시켰다네...\n";
			link.l1.go = "calendar_5";
		break;
		
		case "calendar_5":
			dialog.text = "쿠쿨칸이 미래 사람들의 지혜를 흡수하게 하라고?";
			link.l1 = "그래. 그리고 쿠쿨칸은 오래전에 죽은 마야인들에게 그 지식을 전해주기 위해 과거로 갈 계획이야.\n역사가 바뀔 것이고, 마야가 아메리카를 지배하게 될 거야, 어쩌면 그 이상도...";
			link.l1.go = "calendar_6";
		break;
		
		case "calendar_6":
			dialog.text = "";
			link.l1 = "하지만 차원문에 뭔가 문제가 생겨서 사람들이 테야살로 가는 대신 계속 제자리로만 순간이동하게 되었소. 그래서 내가 여기 온 것이오, 스네이크 아이. 당신의 조언이 필요하오.";
			link.l1.go = "calendar_7";
		break;
		
		case "calendar_7":
			dialog.text = "왜 나야, 백인 선장?";
			link.l1 = "쿠쿨칸에게 잡아먹혔기 때문이지. 그리고 네 마을 근처에 있는 쿠쿨칸 상이 이 지도에 이상한 표시로 나타나 있는데, 그게 카넥의 의식과 깊이 연관되어 있기 때문이야.";
			link.l1.go = "calendar_8";
		break;
		
		case "calendar_8":
			dialog.text = "이 지도를 보여줄래?";
			link.l1 = "여기, 한번 봐...";
			link.l1.go = "calendar_9";
		break;
		
		case "calendar_9":
			RemoveItems(pchar, "skinmap", 1);
			dialog.text = "(보면서) 이 둥근 표식, 맞지? 그리고 이게 무슨 뜻이야?";
			link.l1 = "모르겠소, 주술사. 내가 아는 건 쿠쿨칸 조각상 셋 중 하나에만 이 표식이 있다는 것뿐이오. 그리고 그 표식이 있는 조각상은 당신 거요. 그러니 당신 조각상이 특별하다고 결론내렸소. 무슨 생각이라도 있소?";
			link.l1.go = "calendar_10";
		break;
		
		case "calendar_10":
			dialog.text = "내일 아침까지 시간을 주게, 하얀 형제여. 이 가죽 지도를 나에게 두고 가게. 영혼들에게 물어봐야 하네. 내일 다시 오게.";
			link.l1 = "좋아, 붉은 피부 형제여. 나는 내일 여기 있을게. 도와줘서 고맙다.";
			link.l1.go = "calendar_11";
		break;
		
		case "calendar_11":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
			pchar.questTemp.Tieyasal = "calendar_think";
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_wait":
			dialog.text = "나중에 다시 와, 백인 형제. 지금은 귀찮게 하지 마.";
			link.l1 = "그래, 주술사...";
			link.l1.go = "exit";
			NextDiag.TempNode = "calendar_wait";
		break;
		
		case "calendar_12":
			dialog.text = "너에게 할 말이 있어, 백인 형제.";
			link.l1 = "뭔가 찾았나? 아니면 짐작가는 게 있나?";
			link.l1.go = "calendar_13";
		break;
		
		case "calendar_13":
			dialog.text = "조상 영혼들이 내게 계시를 주었고, 나는 지도를 들고 쿠쿨칸에게 갔어. 찾아서 발견했지. 네가 찾는 것이 틀림없어, 백인 형제.";
			link.l1 = "뭘 찾았어?";
			link.l1.go = "calendar_14";
		break;
		
		case "calendar_14":
			dialog.text = "쿠쿨칸 동상에는 쇠 클램프 두 개와 오목한 홈이 있다. 그 홈은 둥글고 매끄럽다.\n그 방향은 가죽 지도에 있던 둥글고 납작한 물건을 향하고 있다.";
			link.l1 = "무슨 일이야?";
			link.l1.go = "calendar_15";
		break;
		
		case "calendar_15":
			dialog.text = "모르겠소. 내가 아는 건 그것이 둥글고, 평평하며, 작은 호박만 한 크기에 손가락만큼 두껍다는 것뿐이오. 직접 움푹 파인 곳과 고정쇠를 가서 보면 되오. 고정쇠가 그것을 잡아줘야 하오.";
			link.l1 = "무슨 생각이라도 있나? 아니면 그게 뭔지 짐작가는 게 있나?";
			link.l1.go = "calendar_16";
		break;
		
		case "calendar_16":
			dialog.text = "돌에는 불의 흔적이 남아 있지. 무슨 일이 있었는지 나는 알고 있네. 하늘에서 내린 불이 그것을 쳤지.";
			link.l1 = "번개? 번개에 맞은 거야?";
			link.l1.go = "calendar_17";
		break;
		
		case "calendar_17":
			dialog.text = "나는 그 점에 확신이 있네. 나는 미스키토들에게 이 우상에 대해 물어봤지. 한 전사가 오래전에 그 동상 근처에서 예쁘게 칠해진 물건 몇 개를 봤다고 했네. 바위와 아주 비슷했다더군. 그는 그것들이 아주 예쁜 붉은 돌들이었다고 말했어. 백인 마을에서 온 백인 한 명이 그것들을 샀다고 하더군.";
			link.l1 = "흠. 내가 이해한 바로는, 번개가 이 둥근 '무언가'를 쳐서 산산조각 내고, 그 조각들이 어떤 백인에게 팔린 것 같다는 말이지?";
			link.l1.go = "calendar_18";
		break;
		
		case "calendar_18":
			dialog.text = "그런 것 같군.";
			link.l1 = "그 백인은 누구였지? 네 전사가 말해줬나?";
			link.l1.go = "calendar_19";
		break;
		
		case "calendar_19":
			dialog.text = "그가 내게 말했어. 그는 미스키토의 훌륭한 친구였고 블루웰드 마을에 살아. 이름은 포레스트 데빌이야. 나도 아는 사람이니, 너도 분명히 알 거야.";
			link.l1 = "얀 스벤손? 잠깐만... 빨간색으로 칠해진 바위라고? 운이 아주 좋았던 모양이군. 이리 와봐, 주술사야, 내가 가진 이 빨간 바위들을 봐! 숲의 악마가 내게 준 거야.";
			link.l1.go = "calendar_20";
		break;
		
		case "calendar_20":
			Log_Info("You have given ornamental pattern fragments");
			RemoveItems(pchar, "splinter_js", 1);
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			dialog.text = "분명 저놈들이야. 바위 다섯 개. 봐봐, 하얀 형제. 이렇게 놓으면... (함께 맞추며)";
			link.l1 = "...";
			link.l1.go = "calendar_21";
		break;
		
		case "calendar_21":
			dialog.text = "... 그러면 둥근 물건이 있지. 봐! 서로 맞아. 원래는 하나였던 거야.";
			link.l1 = "젠장! 이 조각들이 내 주머니에 그렇게 오래 있었단 말이지... 이봐, 주술사, 내가 이 파편들을 그 홈에 넣으면...";
			link.l1.go = "calendar_22";
		break;
		
		case "calendar_22":
			dialog.text = "쿠쿨칸이 네 말대로 옛 인디언 도시에서 희생자를 토해낼 거야.";
			link.l1 = "그거 정말 좋겠어! 꼭 거기에 가야 해! 장식품이 조각나도 효과가 있을까?";
			link.l1.go = "calendar_23";
		break;
		
		case "calendar_23":
			dialog.text = "나는 우리가 그것들을 모은 다음, 장식을 홈에 넣어야 한다고 생각해.";
			link.l1 = "함께 모으라고? 하지만 우리가 어떻게 다시 합칠 수 있지?";
			link.l1.go = "calendar_24";
		break;
		
		case "calendar_24":
			dialog.text = "나와 조상 영혼들에게 맡기게, 하얀 형제여. 저것들은 단순한 돌이 아니네. 기적의 물건이지. 사흘 밤 뒤에 다시 오게나, 하얀 형제여. 내가 영혼들과 살아있는 이들의 지혜와 솜씨를 불러내어, 파편들을 하나로 합쳐 보겠네.";
			link.l1 = "믿을 수가 없군... 내가 어떻게 보답해야 하지, 스네이크 아이?";
			link.l1.go = "calendar_25";
		break;
		
		case "calendar_25":
			dialog.text = "나중에 고마워해라, 하얀 형제. 이제 가라. 사흘 밤 뒤에 돌아와라.";
			link.l1 = "좋소. 성공하길 바라오...";
			link.l1.go = "calendar_26";
		break;
		
		case "calendar_26":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_28":
			dialog.text = "내가 널 행복하게 해줄 수 있어, 하얀 형제야.";
			link.l1 = "조각들을 하나로 모을 수 있었나?";
			link.l1.go = "calendar_29";
		break;
		
		case "calendar_29":
			dialog.text = "그래. 쉽지 않았고 달력에 상처도 남았지만, 이제 완성되었어.";
			link.l1 = "달력? 왜 그렇게 부르지?";
			link.l1.go = "calendar_30";
		break;
		
		case "calendar_30":
			dialog.text = "이 둥근 물건은 달력이기 때문이야. 내가 자세히 살펴봤지. 여기에 시간 계산이 있어. 고대 도시의 인디언들은 밤, 달, 해, 그리고 시대를 세지.";
			link.l1 = "믿기지 않는군... 하지만 마야 사제들이 할 수 있는 일을 생각하면, 이 달력이 만들어진 것도 그리 대단한 일은 아닌 것 같아.";
			link.l1.go = "calendar_31";
		break;
		
		case "calendar_31":
			GiveItem2Character(pchar, "calendar_maya");
			sld = ItemsFromID("calendar_maya");
			sld.shown = "0";
			Log_Info("You have received a Maya calendar");
			dialog.text = "가져가라, 하얀 선장. 그걸 조각상에 있는 홈에 넣어라. 그러면 어쩌면 인디언 도시에서 널 토해낼지도 모른다.";
			link.l1 = "어떻게 보답해야 하지, 스네이크 아이?";
			link.l1.go = "calendar_32";
		break;
		
		case "calendar_32":
			dialog.text = ""고맙다고 말해라." 신들이 네 길을 인도하고 있다, 네가 보지 못하더라도. 백인들은 운명이라 하더군. 쿠쿨칸이 널 불렀고, 신들이 널 이끌고 있다. 이제 가라. 네 할 일을 하고, 좋은 영들이 널 인도하게 두어라.";
			link.l1 = "고마워, 스네이크 아이! 너를 절대 잊지 않을게.";
			link.l1.go = "calendar_33";
		break;
		
		case "calendar_33":
			TakeNItems(pchar, "Ultimate_potion", 4);
			Log_Info("You have received four versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "잠깐. 우리가 가장 중요한 걸 거의 잊을 뻔했군. 쿠쿨칸은 사람을 잡아먹고 그들의 생명을 흡수하지. 내가 너를 위해 물약을 만들었어. 코만치 물약이야. 이것들을 너에게 주겠다. 내가 플라스크 네 개를 만들었으니, 충직하고 용감한 동료 셋을 데려갈 수 있을 거야.";
			link.l1 = "나에게 이렇게 많은 걸 해줬구나, 내 고향 형제여...";
			link.l1.go = "calendar_34";
		break;
		
		case "calendar_34":
			dialog.text = "코만치 부족 인디언들에게 '형제'란 단순한 말이 아니오. 쿠쿨칸 도시에서 돌아오면 우리 마을에 들르시오. 우리가 사라이아카를 푸짐하게 준비하겠소. 다시 만나게 되어 기쁠 것이오.";
			link.l1 = "물론이지, 내 붉은 피부 형제! 꼭 찾아가겠어!";
			link.l1.go = "calendar_35";
		break;
		
		case "calendar_35":
			DialogExit();
			pchar.questTemp.Tieyasal = "calendar_place";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Tieyasal", "17");
			sld = ItemsFromID("skinmap");
			sld.price = 100; // кожаную карту можно выкладывать 270912 
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
