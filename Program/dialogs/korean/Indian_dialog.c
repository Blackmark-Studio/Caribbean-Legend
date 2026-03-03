// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "우리 사이에 더 이상 할 말 없어!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","백인 여자 인디언")+" 이야기하고 싶은가?","또 너냐, "+GetSexPhrase("Paleface","백인 여자 인디언")+".",""+GetSexPhrase("창백한 얼굴 녀석은 말이 많군. 여자처럼 보이네.","하얀 여자놈은 말이 많군.")+"","술이 내 창백한 얼굴을 데려왔지 "+GetSexPhrase("형제","누이")+" 나에게.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그래.","그래, 또 나야.","참 시적이군.","나도 당신을 다시 보게 되어 기쁩니다.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "이봐, 창백한 얼굴, 왜 온 거지?";
			link.l1 = "아, 별건 아니고, 그냥 네가 무슨 말을 하나 듣고 싶어서 그랬지...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("백인이 말 걸고 싶어?","또 왔군, 창백한 얼굴?","창백한 얼굴 녀석은 말이 많지.","정령들이 내 창백한 얼굴의 형제를 내게 데려왔지.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그래.","그래, 또 나야.","참 시적이군.","나도 다시 만나서 반갑네.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" 네 말을 듣지, 바다의 아들아.","무엇을 원하지 "+npchar.name+", 창백한 얼굴이?","낯선 이여, 네 말에 귀 기울이고 있네.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("너한테 줄 게 있어. 한번 볼래?","정말 흥미로운 걸 보고 싶어? 분명히 마음에 들 거야...","정글의 아이야, 네가 좋아할 만한 것이 있지. 한번 볼래?");
				link.l1.go = "gift";
			}
			link.l9 = "아, 별건 아니고, 그냥 네가 무슨 말을 하나 듣고 싶었을 뿐이야...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" 보고 싶어 해. 보여 줘.",""+npchar.name+" 관심 있군. 보여 줘.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "거울을 줘.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "오! 이제 "+npchar.name+" 이제 강물에 비친 모습만 볼 필요가 없겠네요! 고마워요, 친절한 나그네!";
			link.l1 = "그래, 이제 네 얼굴을 실컷 감상해도 되겠군...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "오! 정말 아름답군! 이 팔찌는 "+npchar.name+"? 고맙소, 친절한 이방인!";
			link.l1 = "그 까무잡잡한 손에 껴 봐, 미인아, 정말 멋져 보일 거야...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "오! 정말 아름다운 반지네! 이건 누구를 위한 거야 "+npchar.name+", 그렇지? 고마워요, 친절한 이방인!";
			link.l1 = "손가락에 끼워 봐, 친구들이 다 부러워할 거야...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "오! 저 멋진 초록 구슬들은 누구를 위한 거지 "+npchar.name+"? 정말 아름답군요! 고마워요, 친절한 이방인!";
			link.l1 = "그걸 목에 걸어라, 셀바의 딸아. 모두가 너를 부러워할 것이다...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "오, 정말 아름다운 초록 반지네! 이거 누구에게 주는 선물이야? "+npchar.name+"? 고마워요, 친절한 이방인!";
			link.l1 = "네 손에 참 잘 어울릴 거야, 예쁜이...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "물어보고 싶었어 "+npchar.name+" 뭐 필요한 거라도 있나, 바다의 아들?";
				link.l1 = "맞아, 예쁜이. 내 용감한 전사들과 나는 셀바, 그러니까 산속에 있는 스페인 정착지로 갈 거야. 그래서 안내자를 찾고 있지. 나는 그 남자뿐만 아니라 그의 아내에게도 후하게 대할 거야. 내게는 아름다운 총, 신기한 망원경, 거울, 목걸이, 팔찌, 반지 등 많은 보물이 있거든. 혹시 네 남편이 우리가 찾는 그 안내자가 될 수 있을까?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "바다의 아들이여, 반갑소. 나는 로코노족 거북이 씨족의 족장 쿠므와나요. 무슨 일로 내 마을을 찾았소?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "선장님께 선물을 가져왔소. 한번 보시지, 마음에 드실 거요.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "족장님, 도움을 청하러 왔습니다. 저는 메리다라는 스페인 정착지에 가고 싶습니다. 그곳은 당신네 셀바의 산속에 있는데, 문제는 제가 어떻게 가야 할지 모른다는 것입니다.";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "그거 참 다행이구나, 바다의 아들아. 그 길을 모른다니. 그 길은 숲을 지나가야 하고, 두려움을 모르는 카퐁 부족의 땅으로 이어지지. 진짜 재규어 같은 자들이야, 오-에이! 나는 그 스페인 놈들 땅엔 절대 안 가. 내 부족은 평화로운 사람들이라 카퐁 땅엔 가지 않아. 쿰와나는 너에게 조언을 해줄 수 없어. 그 길은 너무 위험하거든.";
			link.l1 = "하지만 스페인 놈들도 거길 찾아냈어! 그리고 난 그 카폰 놈들이 두렵지 않아...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "하지만 그래야 해. 그 자들은 잔인한 놈들이야. 숲에서 내 사람들을 많이 죽였지. 쿠므와나가 다 말했다.";
			link.l1 = "젠장...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "오-이! 또 왔군, 바다의 자식아. 쿠므와나에게 무슨 할 말이라도 있나?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "선장님, 선물 가져왔소. 한번 보시지, 분명 마음에 드실 거요.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "메리다를 찾을 희망이 아직 내 안에 남아 있어...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "로코노는 좋은 친구를 언제나 반갑게 맞이하지.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "권총을 선물한다."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "나침반을 선물로 줘.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "값싼 망원경을 선물로 줘.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "평범한 망원경을 선물로 준다."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "괜찮은 망원경 하나 줘."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("You have given a pistol");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "오-에이! 참 멋진 백인의 무기구나! 쿠므와나가 네 선물을 받겠다! 바다의 자식인 너도 쿠므와나와 로코노족의 선물을 받아라.";
			link.l1 = "고맙소, 족장님!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("You have given a compass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "오-에이! 창백한 자들의 마법 부적이로구나! 쿠므와나가 네 선물을 받겠다! 너도, 바다의 자식아, 쿠므와나와 로코노족의 선물을 받아라.";
			link.l1 = "고마워, 우두머리!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("You have given a cheap spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "오-이! 창백한 얼굴들의 마법 관이로구나! 쿠므와나가 그대의 선물을 받겠소! 그대도, 바다의 자식이여, 쿠므와나와 로코노 부족의 선물을 받으시오.";
			link.l1 = "고맙습니다, 족장님!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("You have given a common spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "오-에이! 창백한 얼굴들의 마법 관이로구나! 쿠므와나가 네 선물을 받겠소! 바다의 자식인 그대도 쿠므와나와 로코노족의 선물을 받으시오.";
			link.l1 = "고맙소, 족장님!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("You have given a decent spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "오-이! 창백한 얼굴들의 마법 관이구나! 쿠므와나가 네 선물을 받겠다! 바다의 자식인 너도 쿠므와나와 로코노족의 선물을 받아라.";
			link.l1 = "고맙소, 족장님!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "무슨 일로 우리 마을에 왔나, 바다의 아들아?";
			link.l1 = "족장님, 도움을 청하러 왔습니다. 저는 메리다라는 스페인 정착지에 가고 싶습니다. 그곳은 당신네 셀바의 산속에 있다고 들었습니다. 문제는, 제가 그곳으로 가는 길을 모른다는 점입니다. 혹시 우리에게 길을 안내해 줄 용감한 전사를 보내주실 수 있겠습니까?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "오-이! 위험한 길이야, 위험하지. 그쪽으로 가려면 숲을 지나야 해, 두려움 모르는 카퐁 부족의 땅이지. 진짜 재규어들이라니까, 오-이! 나는 그 스페인 놈들 있는 데 절대 안 가. 우리 사람들, 평화로운 사람들이야, 카퐁 땅엔 절대 안 가.";
			link.l1 = "나는 정말 메리다로 가야 해. 쿠므와나, 네 부하들에게 물어봐 줘. 혹시 내 부대에 합류할 사람이 있을지도 모르잖아? 내 전사들은 경험이 많고, 무장도 잘했으며, 악마조차 두려워하지 않아. 우리는 안내인을 지켜줄 것이고, 일이 끝나면 후하게 보상할 거야.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "좋다, 바다의 아들아. 전사들을 모아 네 소망을 전하겠다. 내일 새벽이 지난 뒤에 나를 찾아오너라.";
			link.l1 = "감사합니다, 추장님!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("The next day...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "오-이! 또 왔구나, 바다의 자식아. 쿠므와나에게 무슨 할 말이라도 있나?";
			link.l1 = "아직 아무 소식도 없습니다, 우두머리.";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = " 들어봐, 쿠므와나. 나와 내 사람들은 정말로 저 강을 건너서 저 빌어먹을 작은 마을에 도착해야 해. 왜 이게 우리에게 그렇게 중요한지 설명해 줄게.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "내 사냥꾼들이 이미 너에게 알렸지...";
			link.l1 = "다시 말할 필요 없어, 쿠므와나. 하지만 밖을 봐라 – 그리고 네 능력을 과대평가하지 마라. 스페인 금화를 찾아 여기 온 내 용사들이 네 마을 곳곳에 흩어져 있다. 그리고 그들의 인내심도 한계에 다다르고 있지. 만약 그 인내심이 완전히 바닥나면 무슨 일이 벌어질지, 너는 모르는 게 좋을 거다 – 내 말을 믿어라.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "입 닥치고 잘 들어, 붉은 피부 원숭이 놈아. 내 동족들은 저 빌어먹을 카퐁족보다 훨씬 더 무시무시할 수 있다. 지금 우리가 친절하게 대한다고 방심하지 마라. 선택은 간단하다. 스물네 시간 안에 길잡이를 구해오든지, 아니면 전부 묶어서 우리 부대 앞에서 정글로 밀어넣겠다. 잘못된 길로 안내하면 네놈이 직접 늪에서 죽거나, 묶인 채로 카퐁족과 싸우게 될 거다. 알겠어?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "쿠므와나, 이 안내자가 꼭 필요해. 우리는 먼 길을 왔고, 내 부하들에게 이 모든 게 헛수고였다고 말하고 싶지 않아.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "쿠므와나가 이미 말했듯이, 로코노 중 누구도 창백이와 함께 가고 싶어하지 않아.";
			link.l1 = "그런데도 아무것도 못 해? 직접 누구한테 물어보든가. 명령이라도 내려봐. 대장 맞아, 아니야?";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "족장은 인디언을 강요하지 않는다. 족장은 다스리며, 자기 백성을 위해 평화를 원한다. 인디언들은 알고 있다 - 카퐁이 로코노가 백인들을 데려오는 걸 볼 것이다. 그들의 머리는 카나이마에게 잘릴 것이다. 그들은 로코노에게 복수하러 온 것이다. 카퐁 - 죽이기 위해. 로코노를 사로잡아 노예로 만든다.";
			link.l1 = "그리고 누가 너희 목을 가져갔지? 어떤 영혼이나 악마가 인디언들을 이렇게 비겁한 구더기로 만든 거냐? 뭐, 어쩌면 정말로 메리다 원정은 포기해야 할지도 모르겠군. 하지만 한 가지는 기억해둬라, 추장. 누가 나에게 로코노에 대해 묻는다면, 나는 언제나 이렇게 대답할 거다 - 그들은 쓸모없는 겁쟁이 족속이라고. 그들과 똑같이 비겁하고 앞을 못 보는 족장이 이끄는 부족, 카퐁족을 떠올리기만 해도 공포에 일그러진 얼굴을 가진 자 말이다. 너희는 인디언들 사이에서 명예를 얻지 못할 것이고, 우리 백인들 사이에서도 존경받지 못할 것이다.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "창백한 얼굴은 인디언들의 풍습을 모르는구나...";
			link.l1 = "나는 인디언들이 누구를 겁쟁이라 부르고 누구를 용감한 전사라 부르는지 알 만큼은 안다네. 잘 가게, 쿠므와나. 그리고 내 말을 명심하게. 자네는 비겁하고 근시안적인 통치자일세.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "왜 이렇게 협박하는 거야? 우리는 네가 좋은 사람이라고 생각했는데...";
			link.l1 = "좋아, 네가 협조만 하면 문제 없어, 알겠어? 하루 줄게. 그리고 명심해, 내 부하들은 내가 시키는 대로 뭐든지 할 거야. 우리는 더 강해. 혹시라도 의심한다면... 네 아내도 봤고, 네 딸들도 봤어. 이제 무슨 말인지 알겠지?";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "왜 이렇게 협박하는 거야? 우리는 네가 좋은 사람이라고 생각했는데...";
			link.l1 = "네가 협조만 하면 난 괜찮아, 알겠어? 하루 줄게. 그리고 명심해, 내 부하들은 내가 시키는 대로 뭐든지 할 거야. 우린 더 강해. 의심된다면... 네 아내도 봤고, 네 딸들도 봤어. 이제 무슨 말인지 알겠지?";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "쿠므와나는 이해했어, 창백한 얼굴이여. 마을에 타고파라는 사냥꾼이 있어. 아마 그가 너를 정착지까지 안내해 줄 수 있을 거야...";
			link.l1 = "24시간 후에 돌아오겠다. 찰리 프린스는 더 할 말 없어, 야만인아.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "바다의 아들, 너였구나. 쿠므와나가 로코노 전사들과 이야기를 나눴다.";
			link.l1 = "그래서? 자원할 사람 있나?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "그곳에 다녀온 사냥꾼들이 몇 명 있지. 하지만 그들은 카퐁과 재규어들이 전쟁 중이라 두려워하고 있어. 가지 않겠다고 하더군, 카퐁이 네 일행을 죽일 거라고. 그들은 백인들을 두려워하지 않아.";
			link.l1 = "내 전사들은 그 놈들보다 훨씬 뛰어나지! 내 부대 일부는 평생을 정글에서 보냈어! 우리는 그냥 풋내기가 아니야!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "미안하네, 바다의 아들아. 내 사냥꾼들이 두려워하고 있어. 카퐁족은 정말, 정말 위험하거든.";
			link.l1 = "좋아, 그렇다면 그들이 어떻게 거기로 가는지 자세히 설명해 줄 수 있겠군?";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "거기로 가려면 강을 따라 항해하다가 특정 지점에서 상륙해야 해. 잘못된 곳을 선택하면 늪에 빠져 죽게 될 거야. 우리 셀바는 위험으로 가득 차 있지. 혼자서는 그곳을 찾지 못할 거다, 바다의 자식아.";
			link.l1 = RandSwear()+"그럼 나는 어떻게 해야 하지? 네 사냥꾼들을 어떻게 설득할 수 있겠어?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "쿠므와나, 더 이상 말하지 마라, 바다의 아들아.";
			link.l1 = "좋아...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "내 남편 타고파는 우리 부족에서 최고의 사냥꾼이야. 오에이! "+npchar.name+" 남편을 자랑스러워한다. "+npchar.name+" 셀바에서 자주 타고파랑 같이 다녀. 멀리까지 가. 스페인 정착지가 어디 있는지 타고파가 알아.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "타고파는 백인들이 메리다라고 부르는 스페인 도시로 가는 길을 아는가?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "그래, 그래... 타고파가 스페인 도시로 가는 길을 아나?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("내 남편은 셀바에 가지 않아, 바다의 아들아. 그는 물고기를 잡지. 좋은 어부야, 오-에이! ","내 남편은 사냥을 잘해, 오-이, 하지만 정글 깊숙이 들어가진 않아."),RandPhraseSimple("사냥하다가 재규어가 내 남편을 다치게 했어. 이제 그는 마을에 앉아서 화살이나 만들고 있지, 아이고!","여섯 달 전, 카퐁 세 놈이 내 남편을 공격했어. 이제 그는 마을에서 멀리 사냥하러 가지 않아. 절대 안 가! 오에이!"));
				link.l1 = LinkRandPhrase("안됐군...","안타깝군...","정말 안타깝군..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "타고파는 이 정글에서 자랐어. 이 근처의 나무와 돌 하나까지 전부 알고 있지!";
			link.l1 = "그가 우리를 그곳으로 데려가 준다면 너와 타고파에게 많은 선물을 주겠어. 보석, 무기, 뭐든지. 네가 원하는 건 뭐든지. 물론 상식적인 선에서 말이지, 허허. 네 남편과 어떻게 이야기할 수 있지?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "타고파는 창백한 얼굴과 함께 가지 않을 거다. 타고파는 마을에 남을 거다. 사냥하러 가라. 카퐁과 싸우지 마라.";
			link.l1 = "그는 카퐁과 싸울 필요 없어. 그들을 보자마자 숨으면 돼. 내 사람들만 싸울 거야.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "아니, 야라나우이. 창백한 얼굴의 자는 절대 약속을 지키지 않는다. 그 자가 말을 해도, 그 말은 곧바로 허공으로 날아가 버린다. 카퐁이 타고파를 죽이고 나면 우리 마을로 와서 로코노를 죽일 것이다.";
			link.l1 = "이 카퐁 놈들만 걱정하면 된다고 생각하나? 아주 큰 착각이야...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("The Indians don't respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "야하후가 백인의 땅에 들어간다! 하야미는 이제 야라나우이와 더 이상 말하지 않을 것이다.";
			link.l1 = "그래, 그래...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "타고파는 하루 전에 사냥을 나갔어. 해가 잠들 때 내일 돌아오겠다고 약속했지. 내일 와라, 바다의 아들아, 나는 타고파와 저 오두막에 있을 거다; 마을로 들어오면 오른쪽으로 가라. 내가 그에게 너와 함께 갈 건지 아닌지 물어볼게.";
			link.l1 = "타고파에게 내가 가장 예쁜 권총을 선물할 거라고 전해라. 그리고 너한테는 보석을 잔뜩 선물해 주마.";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "로코노는 얄라나우이를 믿지 않는다. 얄라나우이는 인디언을 속이고, 인디언을 노예로 만든다. 하지만 로코노는 네 이름을 들었지, 창백한 얼굴이여. 내 신뢰를 주겠다. 내일 해진 뒤에 오너라, 바다의 자식아. 저 오두막에서 타고파와 함께 있을 것이다. 그에게 너와 함께 갈 것인지 물어보겠다.";
			link.l1 = "타고파에게 내 최고의 권총을 주겠다고 전해라. 그리고 너에겐 내가 보석을 많이 가지고 있지.";
			link.l1.go = "hayamee_2";
			notification("The Indians respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			Notification_Perk(true, "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "오-이!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" 바다의 아들이 와서 반갑다네. 타고파가 돌아왔지. 하지만 카셰리를 너무 마셔서 지금 자고 있어. 깨우지 마라, 타고파는 쉬는 중이야. 내가 이야기하겠네.";
			link.l1 = "좋소, "+npchar.name+". 당신 남편이 우리를 메리다까지 안내해 줄 수 있습니까?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "타고파가 당신의 전사들을 셀바를 지나 스페인 마을까지 안내해 주기로 했소. 하지만 조건이 있소...";
			link.l1 = "어떤 놈들?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "너는 타고파를 카퐁 전사들로부터 지켜준다. 타고파는 에스파냐인이나 카퐁과 싸우지 않는다. 위험이 닥치면 그는 도망칠 것이고, 아무도 그를 찾지 못할 거다. 그는 최고의 로코노 사냥꾼이다.";
			link.l1 = "알겠소. 그대가 자기 부하를 걱정하는 건 당연하지. 우리가 저 카퐁 놈들은 전부 직접 처리하겠다고 약속하오.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "오-이! 타고파는 바다의 아들한테 선물을 원한다네: 작은 건 여러 돌을 쏠 수 있는 것, 큰 건 예쁜 돌 하나를 쏠 수 있는 것. 그리고 각 총에 쓸 탄환도 원한다네: 양손의 손가락 수만큼, 그걸 세 번.";
			link.l1 = "오! 네 놈 부하가 총에 대해 좀 아는구만, 응? 좋아. 또 뭐 있지?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "그리고 타고파는 창백한 얼굴들의 아름다운 마법의 눈을 원하지.";
			link.l1 = "망원경? 좋아. 또 필요한 거 있나?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "타고파에게는 더 이상 없어. "+npchar.name+" 예쁜 걸 갖고 싶어 해. 커다란 빨간 보석이 박힌 금반지랑, 아주아주 많은 초록색 돌로 만든 구슬도. "+npchar.name+"마라카이보에서 화이트 메리에서 그걸 봤어.";
			link.l1 = "루비와 비취 구슬이 달린 금반지?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "비취가 아니야. 반짝이고, 백인들이 귀하게 여기는 거지.";
			link.l1 = "에메랄드? 에메랄드 구슬?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "오-이!";
			link.l1 = "헤헷, "+npchar.name+" 보석에 대해 뭔가 아는군! 좋아, 네가 가져가라.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "모든 것을 가져와 "+npchar.name+" 함께하자, 바다의 아들아. 그러면 타고파가 너와 네 전사들을 인도할 것이다. 시간을 낭비하지 마라, 반달이 지나면 타고파와 나는 이웃 마을로 갈 것이다. 위대한 날을 위해서지. 이제 가라, "+npchar.name+" 잠자고 싶어 한다.";
			link.l1 = "너무 오래 기다리게 하진 않을게. 또 보자.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "뭘 가져왔어 "+npchar.name+" 그리고 타고파가 물었나?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "예. 모든 것이 나리의 목록대로입니다.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "아니, 아직 작업 중이야.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" 바다의 아들아, 기쁘구나. 이제 너를 남편이라 부르마. 그는 너와 함께 갈 것이다. 하지만 네가 누구에게 약속했는지 기억하라. "+npchar.name+"!";
			link.l1 = "그래, 그래, 다 기억하고 있어. 내가 그를 안전하게 지킬 테니 걱정하지 마.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "무기 집어넣어, 창백한 놈아, 아니면 우리가 억지로 집어넣게 해주지!";
			link.l1 = LinkRandPhrase("좋아.","좋아.","걱정 마, 내가 치우고 있으니까...");
			link.l1.go = "exit";
		break;  

	}
}
