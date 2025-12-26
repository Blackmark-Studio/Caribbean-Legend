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
		
		case "Sailor_1":
			dialog.text = "뭘 원하지, "+GetSexPhrase("동료","아가씨")+"? 럼주를 준다면 마다하지 않겠어. 이 빌어먹을 마을을 얼마나 많이 빙빙 돌았는지, 다리가 꼬일 지경이야. 그런데 네 이름이 뭐지?";
			link.l1 = "Captain "+GetFullName(pchar)+". 너 '이글'에서 온 사람 아니지?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "그리고 나는 - "+GetFullName(npchar)+". 그리고 그래, 나는 '이글'에서 왔어. 우리 배가 마음에 들어, 선장?";
			}
			else
			{
				dialog.text = "선장? 그래, 그래... 흠흠... 나는 안토니오 벨렌타야. 맞아, 나는 '이글'호 출신이지. 우리 배가 눈에 띄었나, 선장?";
			}
			link.l1 = "배는 배다. 마을에서 어슬렁거릴 시간에 얼른 배에 타는 게 좋을 거야—네 선장은 벌써 벼락이라도 칠 기세거든. 조수 빠지기 전에 항구를 떠날 생각이니, 이봐 꼬마야, 널 기다려주진 않을 것 같아.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "젠장... 알아, 알아... 하지만 아직 이 도시에서 끝내지 못한 일이 좀 남아 있어. 두블룬 몇 개 벌고 싶지 않아, 선장?";
			link.l1 = "두블룬은 언제나 환영이지. 하지만 버는 것과 문제에 휘말리는 건 별개야. 일이 뭐지? 어서 말해봐.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "있잖아, 내가 창고에서 짐을 내리다가 편지 한 통을 발견했어. 일부러 숨긴 것 같진 않고, 그냥 오래된 통들 사이에 놓여 있더라고. 우리 플루트는 여러 번 적의 습격을 당했으니, 그 편지가 어디서 온 건지 알 수가 없어.";
			link.l1 = "그래서 편지를 찾았다고? 그래서 뭐 어쩌라고?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "포르토 벨로에서 온 마리사 칼데라라는 사람에게 보내진 거야. 밀랍으로 봉인되어 있고... 내 촉으로 느껴지는데, 이건 평범한 일이 아니야. 선장일 수도, 상인일 수도 있겠지만... 적어도 나 같은 평범한 선원이 받을 편지는 아니지! 하지만 난 수신인을 찾을 시간이 없어 – 우리 선장은 농담을 진지하게 받아들이는 사람이 아니거든. 이 편지, 나한테서 사지 않겠어? 천 페소면 넘기지. 너는 선장이니까, 이 세뇨리타를 찾는 건 어렵지 않을 거야. 그리고 누가 알겠어, 그녀가 너한테 금을 줄지, 아니면 다른 걸 줄지... 무슨 말인지 알겠지?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "그렇다면, 네 마리사를 내가 찾아줄지도 모르지. \n어차피 잃을 건 없어. 천 페소만 빼고 말이야. 편지 내놔.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				Notification_Money(false, 1000, "peso");
			}
			link.l2 = "미안하다, 친구야, 하지만 다른 사람을 찾아봐라. 나는 편지 배달보다 더 중요한 일이 있거든.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "여기 있어. 자, 몸조심해라, "+GetSexPhrase("동료","아가씨")+", 이제 가봐야겠어 – 내 소지품이 '이글'호와 함께 떠나버리면 곤란하니까.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "너 누구야? 뭐 원하는데?";
			link.l1 = "내 이름은 선장이오 "+GetFullName(pchar)+". 마리사 칼데라를 찾고 있어.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "나는 마리사를 모른다. 잘못 찾아왔군. 지금 나가라, 안 그러면 경비병을 부를 거다 – 금방 쫓겨날 테니까.";
			link.l1 = "Father "+sld.name+" 그녀의 친구라고 들었소. 그녀 앞으로 온 편지가 있소. 겉모습을 보아하니, 꽤 오래된 것 같군. 내가 직접 전해주고 싶소.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "아, 신부님... 그분은 모두에게 너무 친절하시지만, 사람을 잘못 판단하는 일은 드물어요. 편지는 저에게 맡기세요. 반드시 그녀에게 전달하겠습니다.";
			link.l1 = "용서해 주시오, 세뇨리타. 하지만 직접 전해 드리는 게 좋겠소. 그분께서 내가 어떻게 이것을 구하게 되었는지, 또 왜 이렇게 오래 걸렸는지 물으실 수도 있으니.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "그런데 내가 네 선의만 곧이곧대로 믿으라고? 선한 얼굴 한 악당들을 나는 수도 없이 봤다네. 편지를 두고 가든지, 아니면 어서 길을 떠나게.";
			link.l1 = "나는 선장으로서 맹세하오, 당신이나 마리사에게 해를 끼치지 않겠소. \n게다가 경비병이나 무기를 다룰 줄 아는 사람 누구든 이 만남에 데려와도 좋소. \n내 목적은 오직 이 편지를 마리사에게 직접 전하는 것뿐이오.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "알겠소. 내일 밤 열한 시 이후에 오시오. 그녀가 만나겠다고 할지는 장담 못하지만, 당신이 한 말은 모두 전해주겠소.";
			link.l1 = "곧 갈게. 금방 보자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "안녕, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". 나를 찾고 있었다고 했지, 여기 있네. 돌로레스가 내게 줄 편지가 있다고 하던데?";
			link.l1 = "안녕하세요, 칼데라 부인. 맞아요, 여기 있습니다. 아쉽게도 당신께 전해지기까지 꽤 오랜 시간이 걸린 것 같네요.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Given: Letter for Marisa Caldera", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "돌로레스... 이건 그의 필체야... 라미로의 글씨체라고!";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "하지만 그게 어떻게 가능하지? 벌써 2년이나 지났는데!";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" 선장님... 어떻게 그걸 손에 넣으셨습니까? 어디서 찾으신 겁니까? 모든 걸 알아야겠소! 제발, 아는 것을 전부 말씀해 주십시오.";
			link.l1 = "이 편지는 한 선원이 내게 가져온 거요. 그는 자기 배의 어두운 창고 구석에서 이걸 발견했고, 직접 당신에게 전해주고 싶어 했지만 급히 배로 돌아가야 했소. 그래서 나에게 당신을 찾아 달라고 부탁했고, 그래서 내가 여기 온 거요. 내가 아는 건 이게 전부요...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "감사합니다, "+GetAddress_Form(NPChar)+"! 정말 고마워요! 제발, 가지 말아요. 당신과 더 이야기하고 싶지만, 먼저... 이 편지를 읽어야 해요.";
			link.l1 = "물론이지요, Caldera 부인. 여기 있겠습니다.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Twenty minutes passed, Marisa read the letter...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "돌로레스... 그는 마지막 항해 전에 이 편지를 썼어. 벨리즈의 상인에게서 흑단 대량 선적을 살 기회가 있다고 내게 말하고 싶었던 거야. 하지만 돈이 부족했지. 그래서 이 대출을 받았어... 이백 두블론이나... 그 때문에 지금 나는 평온을 찾을 수가 없어.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "그렇다면 모든 게 설명되는군... 하지만 안타깝게도 네 짐이 가벼워지진 않을 거야. 힘내, 마리사. 어둠은 영원하지 않고, 이 빚도 너를 영원히 괴롭히진 않을 거야.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "아니, 돌로레스, 그런 일은 없을 거야! 라미로가 우리 아지트에 비상금을 숨겨놨다고 썼어... 아직 손대지 않았다면, 그 돈으로 빚을 갚고 드디어 이 악몽에서 벗어날 수 있을지도 몰라.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "주님께서 자비를 베푸셨소! 우리의 기도를 들으셨구려...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "선장님, 다시 한 번 이 편지를 가져다주셔서 정말 감사합니다. 저에게는 세상 전부와도 같은 일이었어요... 하지만 한 가지 부탁을 더 드려야 할 것 같습니다. 제 남편 라미로는 제 전부였고, 저는 그 누구에게도 보호를 구한 적이 없어요. 이제 그가 떠나고 나니, 의지할 가족도 아무도 남지 않았어요\n남편의 은신처에 가야 해요. 그곳은 도시 밖에 있어요. 하지만 혼자 가기엔 너무 두렵습니다. 남편의 채권자들이 저를 쫓고 있거든요. 편지를 전해주기 위해 저를 찾아와 주신 것만으로도 당신은 고결하게 행동하셨습니다... 제발, 한 번만 더 도와주세요.";
			link.l1 = "물론이지, Marisa. 내가 데려다줄게. 언제 출발하고 싶어?";
			link.l1.go = "Marisa_16";
			link.l2 = "죄송합니다, 세뇨라, 하지만 이 도시에 머문 시간이 이미 너무 길었습니다. 시골 산책은 제 계획에 포함되어 있지 않습니다.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "알겠소... 이미 내 기대 이상으로 도와주셨소. 고맙소, 선장님, 그리고 안녕히 가시오.";
			link.l1 = "안녕히 가십시오.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "감사합니다, 선장님. 내일 새벽, 일곱 시까지 오십시오. 준비해 놓겠습니다.";
			link.l1 = "그럼 다시 만날 때까지, 부인.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "카바예로, 여기 계셨군요... 진정 명예로운 분이십니다! 출발합시다. 우리의 길은 정글을 지나 모스키토스 만에서 멀지 않은 동굴로 이어집니다.";
				}
				else
				{
					dialog.text = "선장님, 여기 계셨군요... 올 줄 알았습니다. 있잖아요, 자기 배를 지휘하는 여성을 만난 건 이번이 처음입니다. 그리고 이미 알겠어요, 선장님은 명예와 고귀함 모두에서 어떤 남자와도 동등하다는 걸!";
				}
				link.l1 = "훌륭하오, 세뇨라. 그럼 시간 낭비하지 맙시다. 가까이 붙어 있고 한순간도 떨어지지 마시오.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "고마워, 마리사. 내 아버지는 선장이자 명예로운 분이셨지. 어릴 때부터 나에게도 똑같은 이상을 심어 주셨어.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "새벽, 일곱 시까지 오시오. 준비해 두겠소.";
				link.l1 = "그럼 그때 보지, 세뇨라.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "그랬나? 내 라미로와 같은 운명을 맞이했나?";
			link.l1 = "그는 분명히 칼을 손에 쥔 채 죽거나 폭풍 한가운데서 최후를 맞이하길 바랐을 거야.\n하지만 운명은 달랐지 – 아무에게도 말하지 않았던 병에 결국 쓰러지고 말았어.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "당신의 상실에 유감을 표합니다, "+pchar.name+" 주님께서는 우리 중 가장 훌륭한 이들을 데려가십니다...\n그리고 우리가 그 이유를 항상 이해하지 못하더라도, 그것이 주님의 뜻이지요. 우리가 할 수 있는 일은 그들의 불멸의 영혼을 위해 기도하는 것뿐입니다.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "가자. 우리의 길은 정글을 지나 모스키토스 만에서 멀지 않은 동굴로 이어진다.";
			link.l1 = "물론이지. 가까이 붙어 있어, 한순간도 멀리 가지 마.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "여기야... 라미로와 나는 젊었을 때, 그가 내 남편이 되기 전 이곳에서 비를 피한 적이 있어. 그때 그가 내게 말했지, 무슨 수를 써서라도 내 마음을 얻겠다고.";
			link.l1 = "남편 없이 혼자 여기 오게 해서 미안하오, 세뇨라. 이런 곳에는 많은 추억이 깃들어 있지. 둘러보세 – 어쩌면 추억 말고도, 라미로가 가장 힘든 때를 위해 남겨둔 무언가를 찾을 수 있을지도 모르니.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Señor "+pchar.lastname+"",""+pchar.name+"")+"... 뭔가 찾았나? 라미로가 남긴 게 맞아? 뭐가 더 무서운지 모르겠어 – 아무것도 없다는 건지, 아니면 이걸로도 빚을 다 못 갚는다는 건지...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(보여주며) 여기, 이게 상자에 있던 전부야. 이걸로 네 운명이 더 나아지길 바란다.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "아직 상자를 살펴보고 있어.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "아, 선장님! 물론이지요! 이 정도면 충분합니다! 하지만 도와주신 대가를 그냥 넘어갈 수는 없지요. 여기 100두블론을 받으십시오. 당신이 아니었다면 이 은닉처에 대해 평생 몰랐을 테고, 아직도 라미로의 채권자가 보낸 놈들한테서 숨어 다니고 있었을 겁니다...\n";
			link.l1 = "정말 후하시군요, 세뇨라, 감사합니다. 우리 일에서는 금이란 절대 헛되이 쓰이지 않지요.";
			link.l1.go = "Marisa_34";
			link.l2 = "아니요, 세뇨라. 이 돈은 나보다 당신에게 훨씬 더 필요해요. 중요한 건 이제 당신이 모든 걱정을 뒤로하고 평화롭게 살 수 있다는 거죠. 그걸로 저는 충분합니다.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Given: Amulet 'Cimaruta'", "None");
			notification("Given: Amulet 'Fisherman'", "None");
			notification("Given: Matchlock Musket", "None");
			notification("Given: Diamond (10)", "None");
			notification("Given: Ruby (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "그렇다면, "+GetSexPhrase("나리",""+pchar.name+"")+", 우리 이제 움직여야 해. 내가 마을에서 눈에 띄었으면 누군가 우리를 따라올 수도 있어. 여기 오래 머무르지 않는 게 좋겠어.";
			link.l1 = "네 말이 맞아, Marisa. 가자.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "선장님, 제발요... 제 남편은 우리 가족을 지키려고 이 무기를 간직했어요. 저는 확신합니다—선장님 손에 있다면 정의로운 일에 쓰일 거라고요. 모든 희망이 사라졌을 때 저를 구해준 분께 이 무기가 전해졌다는 걸 라미로도 기뻐할 거예요.";
			link.l1 = "알겠소, 마리사, 고맙소. 그대는 친절하고 명예로운 여인이오. 운명이 그대에게 이렇게 잔혹했다는 것이 정말 유감이오.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "가끔 주님께서는 우리의 신앙을 시험하시려고 힘든 날이나 심지어 몇 년의 시련을 주시지만, 올바른 길을 걷는 이들을 결코 버리지 않으십니다. 주님께서 당신을 제게 보내주셨고, 이제 제 가장 큰 고난도 곧 끝나리라 희망합니다.\n하지만 지금은 돌아갈 때입니다. 여기서 충분히 머물렀으니, 아직 저를 찾는 자들이 있어 위험할 수 있습니다.";
			link.l1 = "물론이오, 세뇨라, 가시지요.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "하! 여기 있었군, 우리가 찾던 놈이! 네가 정말 이 쥐구멍 같은 데 숨어서 내가 못 찾을 거라 생각했냐? 내가 이 마을을 몇 번이나 샅샅이 뒤졌는데, 결국 여기 있었잖아\n"+GetSexPhrase(", 게다가 어떤 풋내기랑 데이트까지 했다지. 내 돈 어딨어, 이 작은 창녀야? 당장 내놓지 않으면 이 동굴이 네 무덤이 될 거다.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "너...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "그래서 네가 여자들한테 빚 받아내면서 먹고사는 놈이냐? 하는 짓 보니 머리는 원래 안 썼겠구나. 네가 여기까지 혼자 찾아온 게 신기할 지경이다. 그냥 네 신발이나 따라다녔으면 더 나았겠네.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "입 다물어, 영웅 놈아. 네 차례도 곧 오겠지만, 먼저 저 여자부터 처리해야겠다. 저년이 오백이십오 두블룬을 빚졌지 – 이자가 붙은 금액이다. 전액 갚든가, 아니면 여기서 영원히 썩어 벌레 밥이 되든가. 근데 네가 그렇게 정의로운 척하니 네가 대신 갚아도 돼. 그럼 난 떠나겠다.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "네가 그냥 들어와서, 숙녀를 모욕하고, 날 무시하고, 도블론까지 챙겨서 멀쩡히 나갈 수 있을 거라 생각하나? 영 똑똑해 보이지는 않는군. 하지만 여자 앞에서 싸움은 시작하지 않겠다. 그러니 내 제안을 들어라: 마담 칼데라에게 사과하고, 도블론 챙겨서 당장 꺼져라. 아니면 내가 제대로 예의를 가르쳐줘야 할 테니.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			else
			{
				dialog.text = "입 닥치고 네 차례나 기다려. 이 놈부터 끝내고 나서 너를 상대해 주지. 저 여자는 오백이십오 두블룬을 빚졌어—이자가 붙은 금액이지. 그렇게 정의로운 척하니 네가 대신 갚아라. 그러면 난 떠나겠다.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "그래, 네 거친 태도랑 나한테 무례하게 군 것도 봐줄 생각이야. 하지만 네가 두블룬을 받고 무사히 여기서 나가고 싶다면 칼데라 부인께 사과해야 할 거다. 그렇지 않으면 누가 무기를 더 잘 다루는지 보게 될 거야. 내 말 믿어라, 난 허세로 무기를 차고 다니는 게 아니니까.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			link.l2 = "분명히, 내가 차례를 기다릴 거라고 생각했다면 너한테는 별 재치도 없는 거지. 그리고 너랑 네 족속들이 칼데라 나리께 끼친 온갖 골칫거리를 내가 못 본 척할 거라 믿었다면, 그건 더 어리석은 짓이고.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "좋아, 네 뜻대로 해. 쓸데없는 위험 없이 돈을 챙길 수 있다면, 굳이 내 목을 내밀 이유는 없지. 두블룬을 내놔 – 그리고 썩 꺼져.";
			link.l1 = "먼저, 그 숙녀에게 사과해.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "용서해 주시오, 세뇨라. 악마가 나를 잠시 지배했소.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Happy"+GetSexPhrase("","")+"? 금이나 내놔. 난 할 일이 많아서 여기서 너랑 인사나 나눌 시간 없어.";
			link.l1 = "두블룬 챙기고 여기서 꺼져.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "선장님, 정말 이해가 안 됩니다... 이게 무슨 뜻입니까?";
			link.l1 = "이제 빚은 모두 갚았소. 자유요.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "하지만... 지금 당장 전액을 갚을 수는 없어. 조금만 기다려 줄 수 있겠나...";
			link.l1 = "이해하지 못하는구나, 마리사. 너는 나한테 아무 빚도 없어. 이제 그 누구에게도 빚진 게 없어. 네가 찾은 돈도 너한테 아주 쓸모가 있을 거야. 옛 삶으로 돌아가. 교회가 너를 기다리고 있어.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "나... 나는 정말 믿을 수가 없어. 이런 일은 일어나지 않는데, "+GetSexPhrase("기사 나리","아가씨")+"! 나 때문에 그렇게 큰돈을 썼는데... 그냥 이렇게 끝인 거야? 이제 빚도 없고, 쫓기는 일도 없는 거야? 말해 줘, 진짜야?";
			link.l1 = "맞아요, 나리. 이제 다 끝났어요. 더 이상 누구에게도 빚진 게 없어요.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "오, 선장님, 정말 고귀하십니다! 마치 신께서 보내주신 분 같아요! 어떻게 감사를 드려야 할지 상상도 못 하겠어요.\n정말... 제 인생이 완전히 바뀌었어요, 그리고 저는... 도대체 무엇을 해드릴 수 있을까요?";
			link.l1 = "아무것도 할 필요 없어, 마리사. 그냥 살아. 두려움 없이, 과거의 사슬 없이. 예전 삶으로 돌아가서 그 안에서 행복을 찾아. 그게 나에게 가장 큰 감사가 될 거야. 자, 내가 마을까지 데려다줄게.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "무슨 짓을 한 거요, 선장님, 그를 죽였잖소!";
			link.l1 = "맞아요, 세뇨라. 당신과 당신의 명예를 지켜야 했으니까...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "아이고, 선장님, 아무리 그런 자라 해도 생명을 빼앗는 일은 무겁고 끔찍한 죄입니다! 그 죄를 영혼에서 조금이라도 씻으려면 밤낮으로 기도해야 할 것이오. 하느님께 맹세코, 내가 가진 모든 것을 그에게 내주었더라면 그는 그냥 떠났을 것이오... 하지만 이제... 이제 그의 피가 선장님의 손에 묻었으니, 용서받을 수 있을지는 오직 하늘만이 결정할 것이오!\n";
			link.l1 = "어쩌면 주님의 뜻이었을지도 모르지. 하지만 그 일에 너무 집착하지 말자. 대신 이 동굴부터 나가자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "선장님, 다시 한 번 감사의 말씀을 드립니다! 선장님의 건강과 안녕을 위해 기도하겠습니다, "+pchar.name+". 부디 우리 교회로 오십시오 – 주께서 당신의 모든 죄를 용서하시고 축복을 내리시길 바랍니다.";
			link.l1 = "언젠가 한 번 들를지도 모르지. 그리고 명심해, Marisa. 네가 거기서 환하게 웃는 얼굴을 보여주지 않으면, 난 정말 실망할 거야.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "아, "+GetAddress_Form(NPChar)+"... 당신은 저에게 정말 친절하십니다. 우리 마을에서 다시 뵙게 된다면 진심으로 기쁠 것입니다. 하지만 지금은 용서해 주십시오, 제 삶을 정리하고 이 좋은 소식을 돌로레스에게 전하고 싶어서요.";
			link.l1 = "물론이지, Marisa. 잘 가. 몸조심해.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "선장님, 다시 한 번 끝없는 감사의 마음을 전하고 싶습니다! 당신은 제게 불가능한 일을 해내셨습니다! 당신의 친절함과 고귀함에 보답하고자, 지난 2년간 제가 어떻게 용병들을 피해 다녔는지 말씀드리고 싶습니다. 어쩌면 이 지식이 언젠가 선장님께도 도움이 될지 모릅니다.";
			link.l1 = "감사합니다, 부인. 이런 일에서는 지식이 금만큼이나 소중하지요. 말씀해 보십시오.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "이렇게 나는 지난 2년을 보냈지. 힘이 모든 것을 좌우하는 세상에서, 그림자 속에 머무는 법을 알면 남들이 꿈도 꾸지 못할 기회가 열리거든.";
			link.l1 = "이야기해 줘서 고마워, 마리사. 많은 일을 겪었구나, 네 경험은 정말 소중해.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "다시 우리 마을에서 당신을 뵙게 된다면 진심으로 기쁠 것입니다. 부디 우리 교회에 오십시오—주님께서 당신의 모든 죄를 용서하시고 축복을 내려주시길 바랍니다.";
			link.l1 = "언젠가 한번 들를지도 모르지. 그리고 명심해, Marisa. 네가 거기서 환한 얼굴로 반겨주지 않으면, 난 정말 실망할 거야.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "아, 선장님... 저에게 정말 친절하시군요. 하지만 이제 용서해 주십시오, 제 삶을 정리하고 돌로레스와 이 좋은 소식을 나누고 싶어서 더는 기다릴 수가 없습니다.";
			link.l1 = "물론이지, Marisa. 잘 가. 몸조심해.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Did you hear? Captain "+GetFullName(pchar)+" paid off Calder's widow’s debt from his own pocket! Not many would part with that kind of money for a stranger. Seems Spain still has true caballeros left!","It warms the heart to see that Spain is home not only to worthy caballeros, but also to women whose honor and courage rival any man’s.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("They say a certain captain paid his own money to free Calder’s widow from her late husband’s debts! Not everyone would act so nobly. A true person of honor, don’t you think?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "선장님, 다시 뵙게 되어 정말 반갑습니다! 들러 주시길 바라고 있었지요. 오늘은 잠시 머물러 기도할 시간 있으신가요?";
						link.l1 = "Glad"+GetSexPhrase("","")+" 만나서 반갑소, 마리사. 하지만 지금은 오래 머물 여유가 없구려. 주님께 대한 내 의무를 기억하지만, 기도는 잠시 미뤄야겠소.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "선장님, 또 오셨군요! 항상 반갑습니다. 주님께서 교회로 오는 길을 잊지 못하게 하시는 것 같네요... 어쩌면 이번에는 기도할 시간이 생길지도 모르겠군요?";
						link.l1 = "마리사, 이렇게 보니 반갑구나. 하지만 오래 머물 수는 없어 – 내 일은 기다려주지 않거든. 기도하지 않아도 주님께서는 내 마음을 아신다고 믿는다.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "선장님, 다시 뵙게 되어 얼마나 기쁜지 모르겠습니다! 매일 주님께 선장님의 친절에 감사드리고 있지요. 선장님이 저를 도와주셨을 때 세상이 훨씬 밝아졌습니다.";
						link.l1 = "Glad"+GetSexPhrase("","")+"   건강해 보여서 다행이구나, 마리사. 그동안 더 이상 불쾌한 일은 없었기를 바란다. 훨씬 행복해 보이는구나.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "선장님, 이렇게 뵙게 되어 정말 기쁩니다! 선장님께서 우리 교회에 오실 때마다 제 마음이 평온해집니다. 선장님은 언제나 선행의 빛을 함께 가져오시니까요.";
						link.l1 = "그리고 나도 기쁘다"+GetSexPhrase("","")+" 만나서 반갑구나, Marisa. 이제 조용한 생활에 익숙해졌는가, 아니면 가끔씩 지난날을 돌아보기도 하느냐?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+", 모두가 기도를 미루기만 했다면 세상은 진작 어둠에 잠겼을 것이오. 잠시 걱정을 내려놓으시오 – 참회는 계속 나아갈 힘을 주오.";
			link.l1 = "알겠어, Marisa. 하지만 지금은 정말 안 돼. 말이 없어도 주님께서 내 마음을 들으실 거라고 믿어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", 마음이 바뀌었나? 죄는 저절로 사라지지 않으니, 오래 미룰수록 더 무거워질 뿐이오.";
			link.l1 = "아쉽지만, 이제 가봐야겠소. 하지만 다음번에는 꼭 기도하겠다고 약속하오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "하지만 신앙은 아는 것에 그치는 게 아니라, 실천하는 것이오! 구원의 길을 자꾸 미루기만 해서는 안 되오. 죄의 무게를 벗어던지고 안도감을 느끼고 싶지 않소?";
			link.l1 = "아마도, 하지만 지금은 아니오. 기도가 미뤄지더라도 주님께서 내 말을 들어주시길 바라오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "선장님, 회개를 미루는 것 자체가 죄라고 생각하지 않으십니까? 언젠가는 너무 늦을 수도 있습니다.";
			link.l1 = "아마도 그렇겠지만, 오늘은 시간이 없어서 미안하오. 신앙은 내 곁에 있고, 주님께서는 기도 없이도 내 회개를 보고 계시오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "네, 당신 덕분에 다시 숨을 쉴 수 있게 되었소. 주님께서 당신과 당신의 여정을 지켜주시길 바라오. 혹시 나와 함께 기도해 주시겠소?";
			link.l1 = "당신의 기도는 이미 충분히 강하다고 믿습니다. 가장 중요한 것은 이제 당신 곁에 오직 친절함만이 남아 있다는 사실입니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", 결국 마음이 바뀐 건가? 우리 창조주께 기도할까?";
			link.l1 = "유감이지만, Marisa, 이제 가야 해. 할 일이 있거든.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "나는 오직 앞만 보려고 해. 이제 내게는 미래가 있어, 이 모든 게 당신 덕분이야. 우리 함께 주님께 감사드려야 하지 않을까?";
			link.l1 = "내가 하는 것보다 네가 더 잘할 것 같아. 중요한 건 네 기도가 너에게 평안을 가져다주는 거야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", 적어도 한 번은 기도해 달라고 설득할 수 있을까?";
			link.l1 = "용서해 주오, Marisa. 하지만 지금은 시간이 없소. 나를 위해서도 기도해 주시오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "선장님, 여기는 아닙니다. 우리가 가야 할 동굴은 모스키토스 만 근처에 있습니다.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}