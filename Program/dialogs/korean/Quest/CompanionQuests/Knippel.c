void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "뭐야, 무슨 일이야?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "아, 오늘은 정말 덥구만. 이 답답함을 날려버리려면 다리에 체인 샷을 묶고 바다에 뛰어드는 게 낫겠어!";
			link.l1 = "하하, 찰리!.. 네 말대로라면 꽤 과격한 수단이군. 하지만 목 좀 축이는 건 나쁘지 않지 - 오늘 정말 너무 덥거든. 너도 한잔 할래?";
			link.l1.go = "DTSG_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "선장님이랑 한잔, 두잔 하자고? 언제든지지!";
			link.l1 = "그 말 참 듣기 좋군. 가자!";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_1");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "이봐, 선원, 너 세상 다 본 놈처럼 보이네! 한잔하면서 얘기 좀 나눌까? 내가 쏠게!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "어, 고맙지만 됐어, 친구. 난 내 선장이랑 같이 왔거든. 딴 사람 찾아봐.";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "하, 너 같은 누더기 녀석이 대단한 척하네, 선장들이랑만 술 마신다고?";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "거창한 자부심이라고?! 나는 왕립 해군에서 수십 년을 복무했어! 그리고 귀족들을 위해 싸운 게 아니라, 너나 나 같은 평범한 사람들을 위해, 어디서든 법과 질서를 지키려고 싸웠지!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "입만 살았군, 선장들이랑 귀족들이랑만 술 마시잖아! 해군에서 대포 닦는 법은 제대로 배웠나 보지, 하!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "네 목구멍에 체인 샷을 쑤셔 넣어줄 테다, 이 새끼야!";
			link.l1 = "찰리, 그렇게 흥분하지 마, 그럴 가치 없어.";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "이건 내가 처리하겠소, 선장. 해군의 명예가 걸려 있으니, 내가 직접 지켜야지 누구 뒤에 숨을 수는 없소...";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_1");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "기다려줘서 고맙소, 선장님. 너무 오래 걸리진 않았길 바라오.";
			link.l1 = "신경 쓰지 마. 다친 데 없지? 그 놈, 제법이더라.";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "신경 쓰지 마, 선장. 중요한 건 그 자가 마땅한 대가를 치렀다는 거야. 그의 시체에서 뭔가 열쇠 같은 걸 주웠어...";
			link.l1 = "...";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "그 자의 시체에서 뭔가 열쇠 같은 걸 주웠어... 어디에 쓰는 건지 궁금하군?";
			link.l1 = "기본이지, 찰리... 문이나 상자 따위에나 쓰는 거야, 하하. 이 악당에 대해 주점 주인에게 얘기해 보자, 쓸모가 있을지도 몰라.";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Charlie gave you the key.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_2");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "믿을 수가 없군...";
			link.l1 = "너도 나랑 같은 생각하고 있냐, 찰리?";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "나는 모르겠소, 나리, 하지만 여기 이렇게 돈이 많은 건 정말 놀랍군. 저자는 상인이나 귀족이 아니라 그냥 평범한 사람처럼 보였는데.";
			link.l1 = "정말 그렇게 대단한 건 아니지만, 네 말이 맞아. 놀라운 건 이 이상하게 그을린 편지야.";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "그래, 그건 참 멍청한 짓이었지 - 튼튼한 선체에 연쇄탄을 쏘는 거랑 다를 바 없잖아. 편지는 아예 흔적도 없이 없애버렸어야 했어.";
			link.l1 = "맞아. 하지만 그게 우리한테 도움이 되진 않아 – 그가 누구였는지, 누구와 연락했는지 아무것도 모르잖아. 가자, 찰리, 여기서 더 할 일은 없어.";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_2_1");
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "네가 그토록 자랑하던 왕립 해군도 별거 아니군, 푸흣!";
			link.l1 = "찰리는 좋은 사람이었고, 괜찮은 놈이었지. 그리고 그는 해병이 아니라 포수였어.";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "대포수라고?! 그러니까 내가 한 말이 딱 맞았지, 하하하! 그리고 그렇게 노려보지 마라 - 네가 누구를 선원으로 데려가는지 알았어야지.";
			link.l1 = "누구한테 덤비는지 알았어야지.";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "네가 아직 살아 있는 건 정정당당하게 이겼기 때문이야. 그러니까 그 썩은 입 다물고 여기서 꺼져.";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "음, 난 다음엔 너랑 싸워야 할 줄 알았지. 그래도 명예가 너한테 의미 있다는 말을 들으니 기쁘군.";
			link.l1 = "찰리에게도 그건 빈말이 아니었지. 하지만 너에 대해서는 의심이 들어. 뭐, 이제 와서 상관없지만.";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_2");
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "내가 건드린 게 누구냐고, 응? 응석받이 약골 아니었냐?! 너 그 얇은 콧수염이나 제대로 봤냐?..";
			link.l1 = "넌 정말 사람 열 받게 하는 재주가 있군... 네놈한테 화풀이하면 더 속이 시원하겠어.";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_3");
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "잠깐만요, 선장님. 보아하니 당신은 훌륭하고 고귀한 분이군요, 제 부탁 하나 들어주실 수 있겠습니까? 이건 명예가 걸린 일입니다.";
			link.l1 = "어쩌면 내가 할 수 있을지도 모르지. 그런데 무슨 일이지? 그리고 왜 나한테 온 거야? 이 근처엔 귀한 분들이 많은데. 그런데 누구랑 이야기하게 된 영광을 누리고 있는 거지?";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "피터. 피터 아담스. 너는 흔한 귀족 집안의 응석받이 후손이 아니라, 믿음직하고 침착한 사내라는 게 한눈에 보이는군.";
			link.l1 = "이봐, 내가 처음 카리브에 왔을 때를 봤어야 했어, 나리. \n그래, 말해 봐. 뭐 도와줄 일이라도 있나?";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "내 대신 결투해 줄 수 있겠소, 나리? 이 동네 말썽꾼 랄프 패글이 내 아내를 모욕했소. 게다가 사람들 앞에서 대놓고 괴롭혔지. 내 눈앞에서 말이오. 그게 상상이 가시오?";
			link.l1 = "결투를 신청해 놓고 남 뒤에 숨는 건 명예롭지 않지. 특히 네 개인 명예만이 아니라, 네 아내인 여인의 명예까지 걸린 일이라면 더더욱 그렇고. 그렇지 않나, 아담스? 네 여자를 위해 직접 싸울 수는 없는 거냐?";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "그리고 네 말이 맞아, 정말 맞지. 하지만 나 요즘 심한 열병을 앓아서 겨우 버티고 있는 중이야\n솔직히 이런 부탁을 하게 되어 쉽지 않구나. 나를 모욕했다면 참았을 거야. 하지만 내 아내의 명예가 걸린 일이라면 얘기가 다르지! 난 겁쟁이가 아니야, 나리. 한때는 왕립 해군에서 복무했고, 로버트 블레이크와 같은 배에서 항해한 적도 있다네!";
			link.l1 = "나...";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "우리가 도와줄게.";
			link.l1 = "찰리?..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "그는 훌륭한 사람입니다, 선장님. 이게 거짓말이면 대포알에 맞아 영원히 저주받아도 좋습니다! 블레이크 제독과 함께한 이들은 모두 대단한 인물들이었죠. 그들은 평민들이 억압받지 않도록 함께 싸웠습니다\n그리고 그 덕분에 자메이카가 스페인 놈들의 폭정에서 해방된 겁니다!";
			link.l1 = "설령 그렇다 해도, 내 부하들이 내 말을 끊거나 내 대신 결정하게 두진 않을 거야. 알겠지?";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "알겠어, 정말로. 하지만 아직 대답할 기회조차 없었잖아. 앞으로는 그렇게 성급하게 굴면서 내 말을 끊지 마, 알겠지?";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "이렇게 말하겠소, 선장. 만약 이 사람을 도와주지 않는다면, 늙은 찰리 내가 모든 걸 내팽개치고 직접 저 사람을 위해 결투할 거요, 이 자리에서 천벌을 받아도 좋아!";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "조용히 해, 내가 돕지 않겠다고 한 건 아니잖아. 그렇지, Adams 나리?";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "솔직히 말해서, Charlie, 너 때문에 내가 겁쟁이처럼 보이잖아. 난 한 번도 그런 적 없었어. 너도 그건 알잖아.";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "어, 미안합니다, 선장님. 제가 좀 흥분했네요.";
			link.l1 = "괜찮아. 하지만 네 자신 좀 잘 챙겨, 알겠지?";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "널 위해 결투해주지, Adams 나리.";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "감사합니다, 나리! 신의 가호가 있기를!";
			link.l1 = "그리고 주군이신 로드 프로텍터께도 축복을 빌어야지, 그렇지, 아담스 씨? 걱정 마, 샤를 드 모르는 정직한 사람을 곤경에 빠뜨리고 떠나는 법이 없어.";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "고맙습니다, 드 모르 나리! 제인하고 저랑 저녁 식사 같이 하실래요?";
			link.l1 = "음, 나는...";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "내가 꼭 해야겠어!";
			link.l1 = "그래, 네가 그렇게 원한다면야. 고맙다, Peter. 앞장서라.";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "물론이지, 나리! 제인과 함께 이리 와서 여행 끝에 좀 쉬고 싶으신가?";
			link.l1 = "고맙소, 하지만 당신의 환대를 이용하는 게 옳은 일인가?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "오히려 그 반대요, 선장님. 안 오시면 우리가 섭섭하지 않겠소.";
			link.l1 = "그때 내가 어떻게 거절할 수 있었겠어? 먼저 가, Peter!";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_3");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "우리야! 어서 들어와.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "고맙소. 제인과 이야기해도 되겠소? 어떻게 된 일인지 그녀에게 물어보시오 - 모든 세부사항이 필요하오.";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "정말 미안하지만, 다시 생각해보니 거절해야겠어. 곧 결투 준비를 해야 하거든. 그런데, 어디서 언제 열리는 거지?";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "물론이지요, 나리. 저희 둘 다 기꺼이 말씀 나누고 모든 질문에 답해드리겠습니다. 저를 따라오시지요.";
			link.l1 = "고맙다, Peter.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "안타깝군! 하지만 네 말이 맞아, 당연히 철저히 준비해야지. 두 시간. 바로 성문 밖에서.";
			link.l1 = "알겠소, 고맙소. 끝나면 기꺼이 가겠소. 그때 보자!";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_4");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "어서 오시오! 이봐, 손님을 데려올 거라고 말하지 그랬어 - 제대로 준비했을 텐데.";
			link.l1 = "감사합니다, 부인, 오래 걸리지 않을 겁니다. 샤를 드 모르, 당신을 위해 왔소. 남편분과 함께 사연을 듣기로 했지. 어떻게 된 일인지 말씀해 주시오.";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "아, 정말 끔찍했어! 랄프는 완전히 취해 있었지. 이웃들 앞에서, 심지어 피터 앞에서도 나를 괴롭히기 시작했어, 음란한 말까지 하면서...";
			link.l1 = "그 자가 너한테 정확히 뭐라고 했지?";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "그 일은 너무 창피해서 말 못 하겠어. 그러고 나서 그가 술이 깨더니, 그리고...";
			link.l1 = "사과하고 결투를 취소해 달라고 부탁했겠지, 아마?";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "단 한 번도.";
			link.l1 = "안됐군요. 한 가지 더 묻고 싶은데, 허락해 주시겠습니까, 부인.";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "그게 뭡니까, 나리?";
			link.l1 = "어떤 삶의 사정과 시련이 너와 네 남편을 여기서 살게 만든 거지? 네 남편의 공로라면, 영국 어느 도시에서든 이미 랄프를 제자리로 돌려보냈을 텐데.";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "실례합니다, 나리, 감히 어떻게 이런 말을 하십니까?! 당신이 내 선장이 아니었으면, 체인 샷을 들고 제대로 혼쭐을 내줬을 겁니다!\n아담스 나리처럼 훌륭한 분을 못 믿을 뿐만 아니라, 곤경에 처한 숙녀까지 조롱하다니...";
			link.l1 = "내가 숙녀를 조롱하는 걸 들었어? 아니지? 그럼 나를 헐뜯지 마. 우리 사람들이 그들을 도울 수도 있었으니까, 그래서 내가 물어본 거야.";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "진정해, 찰리! 어떻게 그럴 수가... 난 그냥 제인과 피터가 겪은 고생을 더 알고 싶었고, 그들에게 공감하고 싶었을 뿐이야. 영국 식민지였다면 지금쯤 분명히 도움을 받았을 거야.";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "인생이란 어떻게 흘러갈지 모르는 법이지... 난파를 당할 수도 있고, 아니면 누군가의 중상모략에 휘말려서, 아무리 정직한 사람이라도 수치스럽게 숨어 지내야 할 때도 있지\n그렇게 못 믿고 의심스럽다면 이웃들에게 직접 물어봐. 분명 내가 한 말이 다 사실이라고 확인해줄 거야. 하지만 늙은 찰리는 남의 불행을 등 뒤에서 떠들 만큼 비열하진 않아!";
			link.l1 = "내 말 못 들었어? 내가 이 사람들을 돕겠다고 했잖아.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "인생이란 어떻게 흘러갈지 모르는 법이지... 난파를 당할 수도 있고, 아니면 누군가의 중상모략에 휘말려서, 아무리 정직한 사람이라도 수치스럽게 숨어 살아야 할 때도 있지\n그렇게 의심이 많고 믿음이 없다면, 이웃들에게 직접 물어보라고. 분명 내가 한 말 모두 사실이라고 확인해줄 거야. 하지만 늙은 찰리는 남의 불행을 등 뒤에서 떠들 만큼 비열하진 않아!";
			link.l1 = "내 말 못 들었어? 내가 이 사람들을 도와주겠다고 했잖아.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "진심으로 감사드립니다. 기도할 때마다 당신을 기억하겠습니다.";
			link.l1 = "좋아. 그런데 우리 일 말인데. 결투는 어디서, 언제 잡았지, 아담스 나리?";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "도시 성문 밖에서요, 나리. 두 시간 후입니다.";
			link.l1 = "내가 해낼 거야. 좋은 소식 들고 올 테니 기대해. 그리고 미리 내 명복을 빌려고 촛불 켤 생각은 하지 마!";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "무슨 걱정이라도 있으신가요, 선장님? 무척 심각해 보이십니다.";
			link.l1 = "있지, 그래. Adams 얘기에는 뭔가 앞뒤가 안 맞아, 그리고...";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "이게 언제까지 계속될 건가요, 나리?! 누가 도움을 필요로 할 때마다 이렇게 반응하십니까?";
			link.l1 = "제발 좀 조용히 말해라. 거리 전체에 다 들리게 소리칠 셈이냐. 내가 결투에 나가겠다고 했잖아. 그걸로 부족해? 이제 내 말 똑똑히 들어.";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "흠, 알겠소, 선장. 방금 내버린 말에 미안하오 - 나는 왕립 해군에서 복무한 이들의 운명을 정말 신경 쓰오. 우리 중 많은 이들이 괜찮은 놈들이었고, 대부분이 받은 것보다 더 나은 운명을 받을 자격이 있었지.";
			link.l1 = "알겠네, Charlie. 이제 해야 할 일을 기억하게. 선원 몇 명을 도시 성문으로 보내게. 결투 시간이 다가오면, 조용히 모여 내 신호를 기다리도록 하게.";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "정정당당한 결투를 살인으로 만들 생각이야?";
			link.l1 = "완전히 정직하진 않을 것 같아. 꼭 필요할 때만 신호를 보낼 거야. 정말로 모든 게 떳떳하다면, 내가 틀렸어도 기쁘게 받아들이지. 이제 이해했어? 한 달 전에 무슨 일이 있었는지 기억나?";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "알겠소, 나리. 솔직히 마음에 들진 않지만, 필요한 일은 하겠소. 걱정 마시오.";
			link.l1 = "그 말 듣고 싶었어.";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_5");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "그래, 드 모어. 일찍 왔군. 아직 도시에 있잖아. 뭐, 상관없지. 그 늙은 바보를 같이 데려오지 않은 건 아쉽지만. 걱정 마, 결국엔 그 놈도 손봐줄 테니까.";
			link.l1 = "언제든지 네 말만 해라. 용병들이냐? 내가 누구 심기를 건드린 거지?";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "그게 바로 문제야, 아무도 아니지. 우리는 그 늙은이, 찰리 녀석을 쫓고 있어. 그런데 그 자가 지금 네 배에 있다는 걸 알게 돼서, 너를 통해 찾는 게 더 쉽지. 여긴 정글이 아니니까, 괜히 사람들 몰리기 전에 빨리 움직여야 해. 하지만 여기선, 적어도 너는 도망 못 간다.";
			link.l1 = "이 결투도 결국 함정이었던 거냐?";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "그걸 이제야 깨달았나, 친구. 어차피 싸웠을 거야 - 나는 랄프 패글이야, 잘 부탁하지.";
			link.l1 = "사실, 나도 그럴 줄 알고 이웃들에게 말을 걸어봤지. 그런데, 혹시 아담스도 이 일에 연관된 건가? 그리고 제인은? 혹시 그녀도...";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "호기심이 고양이를 죽인다는 말 못 들었어? 결투에 나오라고 했지, 여기저기 기웃거리라고 한 적 없어. 이 난장판에서 살아남을 기회가 있었을 텐데\n그래, 물론이지. 늙은 군인 놈을 자극해서 그 상관까지 결투에 끌어들이라니, 피터, 우리가 생각해낸 완벽한 계획이었지. 제인도 자기 역할을 제대로 해냈고.";
			link.l1 = "말해 봐, 누가 찰리를 없애고 싶어 했지?";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "하, 내가 너한테 말할 것 같아? 스스로 지켜.";
			link.l1 = "안됐군. 그럼 나중에 피터에게 물어보지.";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "오, 내 이야기를 마음에 새기고 벌써 랄프를 벌줬군, 선장.";
			link.l1 = "물론이지, 네가 말한 대로 나는 훌륭하고 고귀한 사나이니까. 그리고 이제 이 비열한 함정에 대한 벌을 내려야겠군.";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "시도해 보시지, 선장. 분명 벌써 지치고 상처투성이일 텐데.";
			link.l1 = "그럼 잠깐 쉬자. 그동안 네가 누구를 위해 일하는지 말해 봐.";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "미안하지만, 내 후원자는 그걸 좋아하지 않을 거야. 내가 너를 처리하더라도 말이지. 그리고, 참고로 지금 바로 그 일이 일어날 거다.";
			link.l1 = "젠장!..";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "이런... 이런 악당들이 우리를 속인 것도 모자라서 왕립 해군에 대해 거짓말까지 했다고? 감히 어떻게 그럴 수가 있지! 놈들이 아직 살아 있었다면, 저런 배신에 쇄탄 몇 발은 삼키게 해줬을 거다!..";
			link.l1 = "사람들은 온갖 일에 대해 거짓말을 하지, 찰리. 너도 그건 잘 알 줄 알았는데. 하지만 네가 확실히 아는 건 누가 그놈들을 보냈는지겠지. 최근에 너한테 놓인 함정이 이게 처음이 아니잖아. 그놈들은 네 신상까지 자세히 적힌 편지를 갖고 있었어. 도대체 누구를 그렇게 화나게 한 거야?";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "음, 나는... 아담스 집에서 다른 걸 찾을 수도 있지 않을까요, 나리?";
			link.l1 = "질문을 피하는 건가? 하지만 네 말이 맞아, 어차피 철저히 뒤져볼 생각이었으니까. 가자.";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "이런 대포알 같은 일이! 금이 이렇게 많다니!";
			link.l1 = "여기 더 이상 아무것도 없어서 아쉽군. '제인'도 어디에도 안 보여. 아직 살아 있다고 생각해?";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "모르겠소, 나리, 저런 악당들은 무슨 짓이든 할 수 있는 놈들이니까...";
			link.l1 = "그건 맞아. 하지만 네가 말하는 것보다 더 많이 알고 있는 것 같군. 이번이 처음으로 너를 쫓는 것도 아니고. 그리고 매번 놈들한테서 돈뭉치를 찾아내잖아.";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "잘 모르겠소, 선장님, 하지만 아마도 세인트 존스에서 온 고리대금업자였던 것 같소.";
			link.l1 = "어떻게 그를 배신했지?";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "음... 얼마 전에 내가 다른 빚을 다 갚으려고 그 사람에게 돈을 빌렸지. 리처드가 대신 갚아주겠다고 약속했는데, 그런데...";
			link.l1 = "그가 안 했다고 생각해?";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "예전엔 믿지 않았겠지만, 그 자가 너한테 그런 짓을 하고 아비랑 서둘러 카리브를 떠난 걸 보고 나니까... 아마 빚진 것도 잊었을 거야. 아니면 잊지 않았어도 그냥 떠난 거고... 리처드는 진짜 개자식처럼 굴었어, 나리. 또 그런 일이 사실로 드러나도 놀라진 않겠지만, 그래도 실망스럽긴 할 거야.";
			link.l1 = "너무 성급하게 단정짓지 마, 찰리. 그러니까, 세인트 존스로 가는 거군.";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "아, 여기 계셨군요, 나리 - 모두가 일찍 오기로 한 모양입니다. 겉모습을 보니 꽤나 여유로워 보이는데, 자신의 실력을 그만큼 믿는 겁니까?";
				link.l1 = "당연히, 이게 내 첫 결투는 아니지.";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "안 올까 봐 걱정했소, 나리. 다른 사람들은 이미 와 있소.";
				link.l1 = "진정한 신사는 죽음에만 늦을 수 있지.";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "멋진 말씀이오, 나리! 우리 상대 랄프 패글을 소개하지. 그리고 이쪽은 우리 세컨드, 프레더릭 스톡스요.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "만나...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "우리 상대는 랄프 패글이야.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "그리고 이쪽은 우리 부선장, 프레더릭 스톡스다.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "...";
			link.l1 = "그래서 이 사람이 랄프야? 전형적인 술주정뱅이 이웃처럼은 안 보이는데.";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "네 이웃이 누군지 절대 알 수 없는 법이지, 그런 생각 해본 적 있나, 드 모르 나리? 헤헤헤.";
			link.l1 = "그래, 이게 함정이었군... 이제는 떨지도 않는 걸 보니. 열병 앓는 척하는 것도 지겨워졌나?";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "이제부터 내가 떨쳐낼 수 있는 건 네 순진함에 대한 비웃음뿐이야.";
			link.l1 = "그래, 그래. 차를리만 따라오지 않았으면 좋았을 텐데... 너 혼자라면 더 쉽고 조용하게 처리할 수 있었을 거야...";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "그래, 그거 참 멋지군!";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "소개하지...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "우리의 부선장 스토크스 씨.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "그리고 이쪽은 랄프 패글이야.";
			link.l1 = "그래서 저 사람이 랄프야? 인정해야겠군, 난 그를 다르게 상상했었지. 뭐, 상관없어. 더한 놈들도 상대해봤으니까.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "흠, 너 정말 아무것도 모르는 순진한 거냐? 아니면 너무 자만하는 거냐?";
			link.l1 = "내가 뭘 모른다는 거지, Adams 나리? 자, 놀라게 해 봐.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "보통 이런 상황에서는 사람들이 놀라거나 겁을 먹기 마련인데, 너는 좀 다른 부류인 것 같군. 네 그 잘난 미소를 지워버리는 게 더 통쾌하겠어, 드 모르 나리.";
			link.l1 = "무슨 협박이야! 우리 같은 편 아니야, Peter?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "저 늙은이 하나 데리고 우리 전부를 이길 생각은 아니겠지. 숫자에서 밀려, 나리.";
			link.l1 = "내가 말했잖아, 이해 못 하는 건 바로 너라고. 찰리가 좀 투덜거리긴 했지만, 혹시 몰라서 애들 데려오라고 시켰지. 결과적으로 헛수고는 아니었네. 이봐, 녀석들, 여기로 와!!!";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "뭐?..";
			link.l1 = "놀라고 겁먹었나, 아담스 나리? 그거 알아두지.";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "저런 거짓말쟁이 놈들은 그렇게 다뤄야 해. 아직도 저 자식들이 감히 영국 해군에 대해 거짓말을 했다는 게 믿기지 않아! 내가 있었으면 체인 샷으로 목을 졸라버렸을 거야!..";
			link.l1 = "이제쯤이면 어떤 놈들은 양심 따위 없다는 거 알았겠지, 찰리. 내가 처리하겠다고 했잖아, 너는 그냥 배에 있어도 됐어. 네가 정말 내가 이 '가치 있는 사람들'을 도울지 확인하고 싶었던 거야? 그리고 또 누가 옳았지, 네 생각만큼 그렇게 단순하지 않다고 한 사람이?";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "이봐, 나리...";
			link.l1 = "맞아. 하지만 말해 봐, 도대체 누가 너를 쫓고 싶어 하겠어? 이번이 처음도 아니잖아.";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "모르겠소, 선장님. 늙은 찰리는 그냥 평범한 포수일 뿐이오.";
			link.l1 = "흠, 그래, 그래. 좋아, 우리 불쌍한 결투꾼들한테선 쓸만한 게 아무것도 안 나왔으니... 아니, 아담스 집에 가서 뭐라도 찾을 수 있는지 보자.";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "그래서 이 여자도 사라졌군... 혹시 그 '결투' 직후에 도시를 도망칠 준비를 하고 있었던 건가? 그리고 급하게 떠난 모양이야 - 이렇게나 많은 금이 남아 있으니!\n";
			link.l1 = "네 말이 맞아, 놈들이 남기고 간 게 금뿐만이 아니야. 또 다른 편지도 있지. 얼마나 급했는지 태우는 것도 깜빡했나 봐. 이봐, 내용 보면 마음에 들 거야.";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(읽으면서) '늙었다'는 말엔 이의가 있는데.";
			link.l1 = "지금 그게 중요한 게 아니야. 이번이 두 번째야, 놈들이 자네를 노리고 용병들을 보내고, 돈이랑 정보까지 쥐여줬지. 그리고 자네만을 노리고 있어. 말해 봐, 이 멍청한 포수 녀석, 도대체 누구를 그렇게 화나게 했길래?";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "내게 딱 한 가지 짐작이 있어, 나리, 정말 하나뿐이고, 그게 사실이 아니었으면 좋겠어.";
			link.l1 = "그럼, 사실일 가능성이 크겠군. 말해 봐.";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "예전에 세인트 존스에서 여러 사람들에게 빚이 있었지, 그리고...";
			link.l1 = "... 그런데 이제 그놈들이 널 쫓고 있다고 생각하는 거야? 용병을 고용할 돈이랑 그런 큰돈을 댈 수 있는 놈들이 몇이나 되겠어?";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "생각 잘하고 계십니다, 나리. 결국 저는 거의 모든 빚을 돈놀이꾼에게서 빌려 갚았지요. 그 자는 이런 것쯤은 아무렇지도 않게 감당할 수 있겠지요, 물론. 하지만...";
			link.l1 = "근데 뭐? 우리가 네 빚 갚아주면 그걸로 끝이야. 뭐가 걱정인데?";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "있잖소, 선장님, 리처드가 내 대신 그 빚을 갚아주겠다고 약속했었소.";
			link.l1 = "그가 안 그랬을 것 같아?";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "이제는 뭘 생각해야 할지 모르겠소, 나리. 우리가 서로 알던 내내, 나는 그를 모범적인 신사로만 알았지. 하지만 그가 당신을 버리고 아비게일과 도망친 뒤로는... 놀랄 일도 아니오. 그래서 내가 사실이 아니었으면 한다고 말한 거요.";
			link.l1 = "짐작만으로 화내지 말고, 먼저 확인부터 해야지, 찰리. 가자, 세인트 존스에 다시 가보게 될 거야.";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "선장님!!!";
			link.l1 = "무슨 일이야, 찰리, 무슨 일 생겼어?";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "무슨 일이냐고?! 설마 결투를 잊은 건 아니겠지, 나리! 는 네가 여기서 빈둥거리는 사이에 이미 난도질당했을지도 몰라!";
			link.l1 = "좋아!.. 바로 마을 밖으로 나갈게.";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "샤를 드 모르 선장? 거기 찰리 크니펠도 같이 있나?";
			link.l1 = "아니, 이건...";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "부정하지 마시오, 나리 - 이 식민지에서 찰리 모르는 사람 없소.";
			link.l1 = "그럼 왜 묻는 거야? 내가 어떻게 도와줄까?";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "안 됩니다. 저항하지 마십시오 - 찰리는 이곳에서 수배 중입니다. 우리가 그를 구금해야 합니다.";
			link.l1 = "내 부하에게 어떤 죄목이 적용됐는지 알 수 있겠소? 빚 때문이오? 내가 대신 갚을 수 있소. 지금 당장, 당신 앞에서 은행가에게 가자고.";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "빚이라고? 처음 듣는 얘기인데. 자세한 건 모르겠지만, 제발, 일 더 복잡하게 만들지 마. 난 그냥 명령 따르는 것뿐이야.";
			link.l1 = "아, 정말 잘됐군...";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "선장님...";
			link.l1 = "찰리, 지금 도망치면 우리 머리에 걸린 현상금이 더 커질 거야. 그리고 싸워서 빠져나갈 수도 없잖아? 내가 널 빼내려고 해볼 테니, 제발 멍청한 짓은 하지 마!";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "시끄럽게 굴고 이 사람을 위협하는 짓 당장 그만둬, 나리. 무기를 내려놓고 지금 바로 나를 따라와!";
			link.l1 = "나는 아무도 협박하지 않았어, 뭔가 착오가 있었던 거야. 이건 사업 문제지, 살인미수 같은 게 아니야.";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "내 눈에는 그렇게 안 보여. 법에 답해야 할 거야.";
			link.l1 = "사과하고 떠나면 어쩌지?";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "그래서 네가 다시 몰래 들어와서 내가 방해한 일을 끝내겠다는 거냐? 내가 바보인 줄 아나?";
			link.l1 = "평화롭게 끝내고 싶지 않다면, 네가 그렇게 해야겠지. 신만이 아시겠지만, 나도 이렇게까지 가길 원하지는 않았어...";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "네가 그를 죽였잖아!..";
			link.l1 = "네 손으로 한 일이라고 생각해, 나리. 괜히 히스테리 부리지 말고 내 질문에나 제대로 답하지 그랬어. 맹세컨대, 한 번만 더 소리 지르면 네 대가리를 날려버릴 거다.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "그래, 내가 그 자를 죽였어. 나한테 그렇게 하라고 강요했으니까. 하지만 너는 그놈처럼 멍청하지 않으니, 똑같이 굴진 않겠지?";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "뭘 원하는 거야?!";
			link.l1 = "얼마 전에 찰리 크니펠이 당신에게 돈을 빌렸지. 그의 친구가 빚을 갚겠다고 약속했지만, 결국 갚지 않은 모양이야. 더 이상 우리한테 용병을 보내지 말라고 요구한다. 내가 감당할 수 있다면 지금 당장 찰리의 빚을 갚을 준비가 되어 있어.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "뭘 원하는 거야?!";
			link.l1 = "얼마 전에 찰리 크니펠이 당신에게 돈을 빌렸지. 그의 친구가 빚을 갚겠다고 약속했지만, 결국 갚지 않은 모양이야. 지금 당장 우리한테 용병들을 보내는 걸 멈추라고 요구한다. 내가 감당할 수 있다면 지금 당장 찰리의 빚을 갚을 준비가 되어 있어.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "찰리?! 난 그런 짓 절대 안 해. 그는 좋은 사람이자 정직한 사람이야. 게다가 그의 빚은 이미 오래전에 다 갚았어. 발키리호의 선장 플리트우드 나리가 마지막 페소까지 다 정산했거든.";
			link.l1 = "정말이야? 그가 누군지 나도 알아. 진작 그렇게 말하지 그랬어. 괜히 번거롭게 해서 미안하다, 잘 가.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "그냥 이렇게 끝내자고?! 너 나 협박했잖아! 그리고 사람도 죽였고!..";
			link.l1 = "내가 뭐라고 했는지 잊었어? 한 번만 더 소리 지르면 너도 저놈 꼴 나게 해주지. 잘 가라.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "아직도 여기 있고 교수대에 매달리지 않았네? 뭐, 서식스에서 인사 전한다, 찰리.";
			link.l1 = "누구든지 간에, 그대에게 인사하네.";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "아, Charles de Maure. 가엾은 Charlie를 찾아와 줘서 고맙군. 우리가 기대하고 있었지.";
			link.l1 = "우리가 누구지?";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "상관없어. 네 덕분에 우리 시간과 돈이 많이 날아갔지, 드 모어 나리. 여기서 찰리랑 너 둘 다 처리해도 아무도 신경 안 쓸 거다.";
			link.l1 = "뭐, 어차피 우리 둘 다 죽은 목숨이니, 대체 우리가 누구를 그렇게 화나게 했는지 마음씨 좋게 좀 말해줄 수 있겠나? 다시는 안 그러겠다고 약속하지. 그리고 서식스가 누구지?";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "못 해. 의무가 날 부르고 있거든. 너랑 달리 나는 말이 아니라 행동하는 사람이야.";
			link.l1 = "제기랄, 도대체 무슨 일이 벌어지고 있는지 누가 좀 설명해 줄 놈 없어?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Killer_5");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "이런 젠장, 선장님, 여기서 무슨 학살을 벌인 거요!";
			link.l1 = "불만 있나? 교수대가 더 좋겠어? 아니면 여기서 영영 썩고 싶은 건가?";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "아니오, 나리. 구해주셔서 감사합니다. 솔직히 말씀드리자면, 저를 그렇게 쉽게 넘기신 걸 생각하면 오신 게 놀랍군요. 그리고 경비병을 그렇게 쉽게 처리하신 것도 놀랍습니다 - 그 자는 시폭스 소속 해병이었으니까요.";
			link.l1 = "내가 널 꺼내주겠다고 했잖아, 의심하지 말았어야지. 이제 이 감방에서 나가, 곧 온 주둔군 전부가 몰려오기 전에.";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "알겠소, 선장님.";
			link.l1 = "...";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "젠장, 나리, 이게 믿기지가 않네요...";
			link.l1 = "그런데, 말해 봐. 무슨 죄로 걸린 거지? 그리고 Sussex는 누구야?";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "모르겠소, 나리. 그들이 누구를 말한 건지 전혀 모르겠소...";
			link.l1 = "좋아, 그건 나중에 알아보자. 지금은 여기서 나가야 해.";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "다음엔 어떻게 하실 건가요, 나리? 대낮에 저 피 빨아먹는 놈을 두들겨 패는 건 위험한 짓인데.";
			link.l1 = "지금 좋은 생각이 떠올랐어. 왜 대낮에 놈을 두들겨 패서 정신 차리게 해야 하지? 지금, 밤의 어둠을 틈타 할 수 있는데?";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "젠장, 그거 정말 기막힌 생각이군요, 선장님!";
			link.l1 = "맞아. 그런데 말이야, Charlie, 너 여기서 좀 살았잖아. 혹시 돈놀이꾼이 어디 사는지 아냐?";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "예전에 알았지, 나리, 하지만 내가 마지막으로 여기 왔을 땐 그가 집을 팔고 있었어. 새 집이 어디 있는지는 전혀 모르겠어.";
			link.l1 = "글쎄, 그거 문제인데...";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "뭔가 방법을 찾으시겠지요, 선장님. 결국 그 무시무시한 루카스 로덴부르크도 쓰러뜨리셨잖아요!";
			link.l2 = "좋아, 내가 처리할게. 하지만 돈놀이꾼 집이 어디 있는지 알았다면 더 좋았을 텐데!";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "그래, 내가 그랬지. 하지만 밤보다 아침이 더 현명하다고, 찰리. 여행 피로도 좀 풀고 낮에 가자고 – 우린 결국 그 사람을 죽이러 온 게 아니잖아.";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "그게 확실합니까, 나리? 우리가 기습의 이점을 잃게 될 텐데요.";
			link.l1 = "확실하고, 이제 지쳤어. 게다가 그냥 얘기나 좀 하고 싶다. 필요하면 좀 겁만 주면 돼.";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "내가 모르는 건 모르는 거요, 미안하오, 나리.";
			link.l1 = "아, 됐다, 그냥 그를 찾아보자.";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "나리, 혹시 나랑 같은 생각하고 계신 겁니까?";
			link.l1 = "유감이지만 그렇네, Charlie. 그 이름을 가진 유명한 선장은 카리브에 다른 사람이 없어. 그리고 Richard도 런던에 갔지. 그러니 우연일 가능성은 적어.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "끔찍하군... 내가 그에 대해 험한 말을 많이 했지만, 이런 꼴을 바라진 않았어! 그리고 불쌍한 아비!.. 아이를 기다리고 있었는데. 살아 있길 바란다...";
			link.l1 = "정말이지, 누구에게도 이런 일은 일어나지 않았으면 해. 아비가 무사하길 바라자고. 딕한테 이런 짓을 할 만한 사람이 누군지 짐작 가는 거라도 있어? 딕이 예전에 언급한 강한 적이라도 있나?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "농담하시는 겁니까, 선장님. 유럽은 잘 모르겠지만, 여기서는 네덜란드 놈들 모두가 리처드를 죽이고 싶어 했소.";
			link.l1 = "맞아. 어쩌면 여기 누군가가 큰돈을 써서 암살자들을 구세계로 보냈을지도 몰라. \n너를 노리는 자가 이 하찮은 고리대금업자가 아니라, 리처드의 정체불명의 적일 수도 있지 않을까?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "모르겠소, 나리. 지금은 뭐든 가능하지. 하지만 그러면 우리 모두 일이 더 복잡해질 텐데...";
			link.l1 = "그래, 네 말이 맞아, 나도 이런 가능성은 마음에 들지 않아.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "뭐, 누구... 뭐라고?! 무슨 일이야?.. 너 누구야?!..";
			link.l1 = "아, 그만해라. 내가 너를 죽이려고 했다면, 자는 사이에 끝냈겠지. 그러니 우리 인생을 복잡하게 만들거나 짧게 만들지 말자. 이해했으면 고개를 끄덕여.";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "으흠...";
			link.l1 = "아주 좋아. 진정해라 - 나는 네 물건을 훔치거나, 납치하거나, 해치러 온 게 아니야.";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "그럼... 왜 여기 있는 거지? 왜 아침에는 올 수 없었던 거야?";
			link.l1 = "어떤 부유하고 영향력 있는 자가 내 친구를 쫓고 있기 때문이야. 우리가 너라고 믿을 만한 이유가 있어서, 그 친구가 대낮에 이 거리를 돌아다니는 건 위험할 것 같아.";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "하지만 정말 무슨 말씀을 하시는지 모르겠습니다, 나리...";
			link.l1 = "찰리 크니펠. 이 마을 사람들은 다 아는 인물이야. 잘 생각해 봐. 그놈이 네게 돈을 빚졌지.";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "우리 늙은 찰리?? 맞아, 하지만 그의 빚은 오래전에 갚아졌지, 물론 그가 직접 갚은 건 아니지만.";
			link.l1 = "그 은인은 누구였지?";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "그의 선장은 리처드 플리트우드 경이야. 내 말을 못 믿겠으면, 내 기록을 보여줄 수도 있어.";
			link.l1 = "플리트우드라고 했나? 그럼 믿지. 그럼, 자네가 찰리한테 용병들을 보낸 건 아니란 말이지?";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "당연히 아니지, 내가 왜 그래야 해?? 그리고 말해 봐, 그게 무슨 의미가 있겠어?";
			link.l1 = "정말이군. 뭐, 늦게 찾아와서 미안하네. 잘 자게.";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "뭐야, 찰리, 오늘 밤에도 옛 주인 밑에 숨으려고 했냐? 거기 없어. 하지만 곧 만나게 될 거다. 서식스에서 인사 전한다.";
			link.l1 = "우린 이미 그건 알고 있었지. 그런데 서식스는 누구지? 그리고 넌 또 누구냐?";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "그건 네가 신경 쓸 일이 아니야, 드 모어 나리. 네가 이 엉망진창에 우리가 원하는 것보다 더 깊이 끼어든 게 유감이군. 넌 성가신 존재야.";
			link.l1 = "누구한테 성가신 거지? 설마 내가 엄청 영향력 있고 엄청 화난 영국놈의 아내랑 잤다는 소리는 아니겠지.";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "아주 웃기네. 농담할 시간은 있나 보지. 내가 너에 대해 들은 게 사실인 모양이군\n우리가 원하는 게 뭐냐고? 찰리의 목이면 충분하지. 하지만 네가 우리한테 끼친 골칫거리를 생각하면, 이번엔 너도 예외가 아니야 - 네가 자꾸 쓸데없는 데 참견하니까.";
			link.l1 = "우리가 체포된 거냐?";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "체포? 아니오, 나리, 이제 미적지근한 대처는 끝났소. 이번엔 처형이오, 드 모르 선장.";
			link.l1 = "동의하지. 문제는 누구의 것이냐는 거지.";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "씨 폭스 놈들이 끼어들 줄은 몰랐는데...";
			link.l1 = "뭐든 처음은 있는 법이지. 말해 봐, Charlie, Sussex가 누구지?";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "나...";
			link.l1 = "이게 얼마나 심각해졌는지 안 보여? 그리고 우리 둘 다 같은 처지인 것 같은데, 찰리. 그러니 내가 자세한 내용을 알아야 할 권리가 있어.";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "물론이지, 선장님. 하지만 여기서는 아니잖아? 섬에서 나가서 배에서 얘기하자.";
			link.l1 = "네 말이 맞아. 좋아, 서두르자.";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "부르셨습니까, 선장님?";
			link.l1 = "그래, 찰리. 우리 얘기 좀 해야겠어. 네가 벌써 무슨 일인지 짐작하고 있겠지.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "그래, 나리...";
			link.l1 = "좋아. 너는 범죄자도 아닌데 왜 너희 동포들, 그것도 정예병들까지 너를 쫓고 있는지 말해 봐.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "정말 모르겠소, 나리...";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "이건 농담이 아니야, Charlie. 널 쫓는 놈은 바다의 여우들에게 명령을 내릴 수 있는 자야. 아마 Richard가 죽은 것도 그놈 짓일 거다. 그러니 생각나는 게 있으면 말해 봐. Sussex에서 온 인사라니, 그게 누구야?";
			}
			else
			{
				link.l1 = "고개 돌리지 마, 찰리. 뭔가 알고 있는 거 다 보여. 네 선장으로서 명령한다, 전부 말해. 서식스가 누구지?";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "알겠소, 선장님. 서식스는 사람이 아니오. 그건... 배요.";
			link.l1 = "배에서 인사한다고? 말도 안 되는 소리야.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "설명 좀 하겠습니다. 앉아도 되겠습니까, 나리? 이야기가 길고 썩 유쾌하지는 않습니다.";
			link.l1 = "물론이지, 찰리. 해봐.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			SetLaunchFrameFormParam(StringFromKey("Knippel_11", NewStr()), "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
			LaunchFrameForm();
			//DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "이봐, 찰리, 나는 플리트우드 선장님이 보냈어. 선장님이 너를 보자고 하셔.";
			link.l1 = "고마워, 친구. 무슨 일이라도 있었나? 평소엔 모든 걸 바로 너를 통해 보내잖아.";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "모르겠어. 그가 직접 너랑 이 일에 대해 얘기하고 싶다더라.\n네 일이니까, 너희끼리 알아서 해결해.";
			link.l1 = "아, 왠지 불길한 예감이 드는데...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Kurier_3");
		break;
		
		case "DTSG_Cortny":
			dialog.text = "...";
			link.l1 = "안녕히 주무십시오, 나리!";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "좋은 밤이군. 지나가게 해.";
			link.l1 = "물론이지, 해. 미안하네, 나리.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Cortny_3");
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "아, 찰리, 너구나. 들어와, 들어와. 문도 닫고.";
			link.l1 = "좋은 밤입니다, 선장님. 무슨 일이십니까? 그리고 저 사람은 누구였죠? 거만한 공작새 같던데...";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "그건 말할 수 없어. 그리고 우리 대화를 누가 듣게 둘 수도 없지. 이 일은 아무한테도 말하지 마, 알겠나?";
			link.l1 = "그래, 나리. 무슨 일이라도 있었습니까? 평소와 다르게 몹시 걱정스러워 보이십니다.";
			link.l1.go = "DTSG_Fleetwood_3";
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "너도 그렇게 보이는군. 너도 별로 좋아 보이진 않아 – 밤이니까. 하지만 미안하군, 오늘 밤 잠은 끝난 것 같아, 친구야 – 우리에겐 급하고 비밀스러운 임무가 있거든.";
			link.l1 = "그게 무슨 일인지요, 선장?";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "배신자를 제거하는 거지. 우리 편에서 나온 놈을. 곧 구세계에서 온 외교선이 도미니카 해안에 나타날 거야 - 프리깃 '서식스'지.\n공식적으로는 네덜란드와 좋은 거래를 협상하러 온다고 하지만, 실제로는...";
			link.l1 = "... 우리 적들에게 정보를 넘길 생각인가요, 나리?";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "더 나빠. 완전히 적 편으로 넘어갔지. 대서양을 건너느라 녀석들이 지쳐 있겠지만, 결국 저건 좋은 프리깃이니까 우리가 중대형 함선으로 공격하면 분명 도망치려 들 거야\n그러니 신속하고 단호하게 움직여야 해. 믿을 수 있는 건 '발키리'뿐이야 – 그런 임무를 해낼 수 있는 건 저 배밖에 없어.";
			link.l1 = "늙은 '발키리'가 프리깃함을 감당할 수 있을까?..";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "하하, 찰리, 네가 네 선장을 의심하는 거냐? 게다가 내가 말했듯이, 저놈들은 지쳐 있을 거야. 우리가 기습하면 모든 이점은 우리 쪽이지.";
			link.l1 = "나는 절대 그런 짓 안 해! 하지만 나리, 정말 뭘 하는지 알고 있는 거겠지...";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "확실해. 그리고 한 가지 더. 이 변절자는 의회 안에서도 높은 자리에 있는 놈이야, 알겠어? 놈이 어디든 눈과 귀를 두고 있을 거다 - 본국뿐만 아니라 이미 여기, 카리브 해에도 말이지. 그러니 서식스나 우리 임무에 관한 세부 사항은 마을에서 입 밖에 내지 마.";
			link.l1 = "말 안 해도 됐소, 나리. 늙은 찰리만 믿으시오.";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "알고 있지. 이번엔 판돈이 그 어느 때보다 커. 짐 챙기고 준비해라 - 우리는 새벽에 출항한다.";
			link.l1 = "그래, 나리. 잘 자시오, 나리.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_9");
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "난 리처드가 이렇게 된 건 처음 봤어... 그렇게 걱정하거나, 아니면... 무서워하는 것 같았어?";
			link.l1 = "하지만 왜지? 나한테조차 말 안 했어. 뭐, 상관없지. 그는 훌륭한 선장이니까, 이 프리깃과 지친 선원들쯤은 우리가 분명히 처리할 수 있을 거야.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Knippel_SamSoboi_2");
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "'서섹스'가 지평선에 보여, 찰리, 준비해.";
			link.l1 = "언제든 준비됐소, 선장님.";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "좋아. 너와 네 체인 샷을 믿는다. 최대한 빨리 저놈들 돛을 갈기갈기 찢어버려라, 아니면 차라리 돛대 하나를 쓰러뜨려. 가라앉히려고 무모하게 싸우는 건 의미 없으니, 내가 직접 배에 올라탈 생각이다\n게다가, 배신자가 확실히 죽었는지도 확인해야 하니까, 배를 가라앉혀도 결국 가까이 가서 살아남은 놈이 없는지 확인해야 해.";
			link.l1 = "배신자 하나 때문에 동포들을 그렇게 많이 죽이라고...";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "슬프군. 나도 마음이 아프네, Charlie. 하지만 명령은 명령이지. 적어도 재미로 하는 일은 아니잖아. 그러니 빨리 끝내자고.";
			link.l1 = "그래, 나리...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_13");
		break;
		
		case "DTSG_Graf_Sheffild_1":
			dialog.text = "그만해! 나 칼 내려놓고 네 요구 조건을 들어볼 준비 됐어. 하지만 먼저, 네놈부터 소개해! 넌 누구고, 감히 우리를 공격하다니 무슨 배짱이지?! 이건 반역이야!";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "리처드 플리트우드 선장. 그리고 자네가 셰필드 백작이겠군? 그리고 자네 말이 맞아, 이건 명백한 반역이지.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "내가 누군지 알아? 젠장! 이런 일이 일어날 줄 알았지, 쥐새끼들이 사방에 들끓으니까. 그래서 내가 군함을 달라고, 아니 애원까지 했었지...";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "그렇게 했어도 널 구하지는 못했을 거야. 피할 수 없는 운명을 조금 늦출 뿐이지, 내가 다른 방법을 찾았을 테니까. 그리고 그래, 반역이라면 네 얘기다, 셰필드 백작.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "그럼 당신은 나에 대해 아무것도 모르는 거요, 나리! 나만큼 영국에 충성스러운 놈은 없다는 걸 모두가 알지! 이 실수, 반드시 후회하게 될 거요, 내 말 명심하시오.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "나는 네덜란드로 배신하는 놈이 아니니, 후회할 일 따윈 없어.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "뭐?! 무슨 헛소리를 지껄이는 거야?! 넌 속았고, 미친 사냥개처럼 엉뚱한 흔적만 쫓았잖아\n크흠, 맞아, 나 지금 네덜란드 서인도 회사와 협상하러 가는 중이야. 하지만 우리 영국을 위한 일이야, 선장. 이건 끔찍한 실수지만, 아직 바로잡을 수 있어.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "내가 결정할 수 있는 일이 아니야. 그리고 너희가 결정할 일은 더더욱 아니지. 너희는 잘못된 편을 골랐어, 이 친구들아. 잘 가라.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "여기서 끝났군. 저 뚱뚱한 놈이 언제까지나 비명을 지를 줄 알았지. 아, 이런 백작 놈들 말이야, 맞지, 찰리?";
			link.l1 = "난 그냥 궁금해서 그러는데, 나리, 만약 대령이 틀렸다면 어쩌죠? 아니면, 맙소사, 백작을 없애려고 우리한테 거짓말을 한 거라면요?";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "내 말 좀 들어, 친구야. 그리고 잘 들어둬. 우리가 하는 일은 정말 위험하고 힘든 일이야, 모든 면에서. 무슨 일이든 일어날 수 있지—슬픈 실수, 어이없는 우연, 아니면 비열한 배신까지도\n나라를 위해 복무한다는 건 그냥 대포에 포탄을 넣는 것만이 아니야, Charlie. 권력자들에겐 힘든 결정을 내리는 거고, 우리 같은 군인들에겐 그 결정을 실행하는 거지.";
			link.l1 = "하지만 언젠가 우리가 죄 없는 이의 피를 흘리게 된다면 어떡합니까, 선장? 그건 우리 손에, 우리 양심에 남게 될 겁니다.";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "그럼 그들도 우리만큼, 아니 우리보다 더 피에 손을 묻히게 되는 거야. 그걸 위안 삼으라고. 중요한 건 우리가 조국의 적을 제거하려는 순수한 의도로 행동했다는 거지\n이제 도와줘, Charlie. 아직 네덜란드 놈들이 공격한 것처럼 꾸며야 해.";
			link.l1 = "그래, 나리...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Graf_Sheffild_25");
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "그래서 우리는 네덜란드 놈들이 한 것처럼 보이게 가짜 증거를 남겼지. 그날 이후로 리처드랑 나는 그 일에 대해 다시는 얘기하지 않았어.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "이제야 많은 게 이해가 되는군. 리처드의 죽음 뒤에는 백작의 친척이나 측근이 있는 것 같아. 그런데 왜 너를 노린 거지? 넌 그냥 포수였고, 그 비참한 날에 아무 결정도 내리지 않았잖아.";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "그래. 이건 정말 구린 일이야, 냄새가 진동하지. 누가 이 사실을 알아내서 백작의 복수를 결심했을지도 몰라. 하지만 대포 쏘는 한 놈 때문에 이런 돈과 용병, 바다여우까지 동원할 가치가 있겠어? 말도 안 돼, 찰리.";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "혹시 이 자가 리처드의 옛 선원들을 모두 쫓고 있는 건 아닐까? 어떻게 생각해, 나리?";
			link.l1 = "나는 우리가 앤티과에서 멀어져야 한다고 생각해, 그리고 빠르면 빠를수록 좋아.";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "나도 그 질문을 해봤소, 선장. 하지만 아직 답을 못 찾았지.";
			link.l1 = "젠장. 누가 온다. 방해하지 말라고 했잖아!";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_103");
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "찰스!..";
				link.l1 = "헬렌, 무슨 일이야??";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "찰스, 당신이 아무도 들이지 말고 당신이랑 찰리를 방해하지 말라고 했던 거 기억하는데...";
				link.l1 = "... 직접 오기로 했군. 좋아, 괜찮아, 헬렌.";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "영국 군함이다! 좀 전에 발견됐어. 처음엔 신경 안 썼는데, 이제 곧 우리한테 닿을 거야! 그렇게 빠른 배는 처음 본다.";
				link.l1 = "그럼 알려줘서 고맙다. 그녀가 다가오기 전에 준비할 시간이 있길 바란다. 헬렌, 찰리, 전투 준비!";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "... 너희 비밀 회동은 나중에 계속해도 돼. 영국 군함이 이쪽으로 오고 있어. 중요한 일인 것 같아서 말이야.";
				link.l1 = "그래, 내가 가서 한번 살펴볼게. 고마워, 헬렌.";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "선장님, 빠른 배가 우리 쪽으로 다가오고 있습니다. 아주 빠릅니다. 영혼들이 내게 속삭이는데, 저놈들의 의도가 사악하답니다.";
			link.l1 = "경고해줘서 너와 신령들에게 감사한다. 만약을 위해 전투 준비해라. 그리고 이 말을 다른 녀석들에게도 전해줘.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "실례합니다, 선장님, 방해해서 죄송하지만 급한 일입니다.";
			link.l1 = "아, 정말 중요한 일이어야 할 텐데, Alonso. 보고해.";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "영국 배가 다가오고 있어. 저건... '미라지'야, 선장.";
			link.l1 = "뭐라고? 정말 확실해? 또 술 마신 거 아니야?";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "확실합니다, 선장님 - 카리브 해에는 그런 배가 또 없다는 거, 선장님도 아시잖아요.";
			link.l1 = "그래. 내가 직접 가서 확인해 보겠다 - 이 '미라주'가 진짜인지 두고 보자.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "오... 하지만 아직 끝난 게 아니야! 브라이언, 거기 있었구나! 도대체 어디 갔다 온 거야?";
			link.l1 = "이건 피할 수 없는 일을 잠시 미룰 뿐이야.";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Brian";
			sld.lastname = "Tasse";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "샤를 드 모르. 네가 이렇게까지 올라올 줄이야. 유감이군. 이 배에서 널 방심하게 만들길 바랐는데.";
			link.l1 = "내가 누군지 아나? 그러면, 최근 우리에게 닥친 골칫거리의 배후가 바로 너였군. 편안한 둥지를 떠나 직접 나설 수밖에 없었던 잘난 새처럼 보이네, 다른 독수리를 보내는 대신에 말이지.";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "맞아, 둘 다 정확하지. 귀족은 멀리서도 서로를 알아보는 법이지. 토머스 린치 대령이오. 이제 서로를 파괴하려 들기보단 신사답게 대화할 때가 된 것 같군. 어쩌면 우리 둘 다 이득이 되는 합의에 이를 수도 있겠지.";
			link.l1 = "아무것도 약속할 수는 없지만, 적어도 우리가 신사답게 대화는 할 거라는 점은 귀관에게 신사로서 맹세하오, 대령.";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "좋아. 플리트우드랑은 이런 대화를 할 수 없었지. 그래도 우리는 그 자에게 약점을 잡았으니, 이제 더 이상 우리를 괴롭히지 못할 거야. 너와는 잘 풀리지 않아 아쉽지만, 뭐 어쩔 수 없지.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "카리브 해 전체가 리처드의 죽음에 대해 떠들썩하더군. 그래서, 그게 바로 너였구나! 그리고 네가 말한 그 약점이 아비게일이었던 거지? 그런데, 그 아가씨는 어떻게 된 거야?";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "위협이 아니라고? ..그래서, 그를 죽였다는 거야? 자네, 백작 편이냐?";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "아비게일? 아, 그 젊은 유대인 아가씨, 그의 약혼녀 말이지. 역시, 자네는 참 눈치 빠른 사람이구만. 그녀는 무사히 살아 있어. 우리가 약속했고, 플리트우드가 협조하는 대가로 그 약속을 지켰지.";
				link.l1 = "꽤 협조적이군, 그래도 왜 그런 거지? 자네가 백작을 지지하는 건가?";
			}
			else
			{
				dialog.text = "지지자라고? 전혀 아니지. 오히려 반대야. 하지만 말이야, 어떤 패는 더 이상 쓸 수 없게 돼서 플레이어에게 짐이 되거든. 안타깝게도 리처드가 그런 패 중 하나가 되어버렸지.";
				link.l1 = "알겠어. 증인들은 다 없애는 거군. 아비게일은 어떻게 됐지? 걔도 죽였어?";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "전혀 아니야. 오히려 반대지. 하지만 리처드는 너무 많은 걸 알고 있었고, 구세계로 돌아가면서 위험한 인물이 되어버렸어. 여기 남았어야 했는데, 그랬다면 우리가 그의 목숨을 빼앗지 않았을 거야.";
				link.l1 = "대령, 당신 밑에서 일했던 사람은 전부 없애버리는 건가?";
			}
			else
			{
				dialog.text = "누구? 아, 그의 약혼녀 말이지. 그녀가 바로 인질이었어. 그의 목숨과 그녀를 맞바꾼 거지. 그녀는 무사해, 내 명예를 걸고 맹세한다.";
				link.l1 = "네가 무슨 짓을 했는지 생각해 보면, 명예가 뭔지 알기나 하는지 의심스럽군, 대령.";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "그 도발엔 대답하지 않겠소, 나리.";
				link.l1 = "그럼 대답해 봐라 - 이 배는 어떻게 손에 넣은 거지? 설마... '미라주'인가?";
			}
			else
			{
				dialog.text = "네가 한 번도 권력을 쥐어 본 적 없고 세상의 질서를 좌지우지해 본 적 없는 놈이니까, 이번 모욕은 그냥 넘어가주지.";
				link.l1 = "그건 그렇고, '미라주'는 어디서 구한 거지? 이 배가 그 배야?";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "정확히는 아니지. 멋진 배지, 안 그래? 안타깝게도 너한테는 제 역할을 못 했군. 이 배의 역사에 대해 알고 있나, 드 모르 선장?";
			link.l1 = "유령선이랑 영국 상인 사냥 얘기하는 거야?";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "그거? 아냐. 내가 말하는 건 잘 알려진 게 아니야. 눈에 보이지 않는 것들 말이지. 이 케치는 요한 판 메르덴이랑 루카스 로덴부르크가 설계한 거야\n그 둘이 온갖 계략을 꾸며서 결국 이 배가 아바나 조선소에서 진수됐지. 우리는 운 좋게도 원래 설계도를 손에 넣었어. 그리고 결국 미라주를 원래의 영광 그대로 재현했을 뿐만 아니라, 설계상의 몇몇 결함까지 고쳐서 더 나아지게 만들었지.";
			link.l1 = "안타깝군, 자네도 알다시피 그게 별로 도움이 되진 않았지, 대령.";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "웃을 기분이냐? 그러지 마라. 인정하지, 너는 선장으로서도 싸움꾼으로서도 나를 능가했지. 하지만 여기서는 아직 내가 우위에 있다.";
			link.l1 = "죽어가는 척하는 건가? 아니면 너 같은 놈들이 늘 그렇듯이 허세를 부리는 건가? 이 말들 뒤에 뭐가 숨겨져 있지?";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "좋은 질문이군. 내 조사로는 너도 그냥 여자나 쫓는 건달이나 결투꾼 그 이상인 것 같아. 나는 이 만남의 모든 결과에 대비해 두었지. 네 칼이나 총알, 아니면 어쩌다 날아든 포탄에 내가 죽는 경우까지도 말이야. 만약 내가 오늘 죽는다면, 너랑 Charlie는 Fleetwood와 손잡지 않은 걸 후회하게 될 거다.";
			link.l1 = "현상금 사냥꾼이 또 있다고? 웃기지 마. 그때도 불쾌하고 지루했을 뿐이지, 죽을 일은 아니었어. 그때도 쫓아냈고, 이번에도 쫓아낼 거다.";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "의심할 여지가 없어. 이제 또다시 태평한 결투꾼이 말하는 게 보이는군. 현상금 사냥꾼들만이 아니야. 시폭스 전부와 영국 해군 정보부까지, 어부의 배를 덮치는 폭풍 파도처럼 네 머리 위로 몰아칠 거다.";
			link.l1 = "나한테 뭘 원하지? 설마 내가 항복하길 바라는 건 아니겠지?";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "당연히 아니지. 그동안 너를 충분히 관찰해 왔으니까. 서로에게 이익이 되는 거래를 제안하고 싶네. 거절하면 어리석은 일이 될 거야. 그리고 우리 둘 다 신사이니, 합의에 이를 수 있기를 바라네.";
			link.l1 = "그럼 다시 묻지, 대령. 뭘 원하는 거지? 찰리 말인가?.. 그리고 나한테 뭔가 대가를 줄 수 있다고 생각하나? 나는 금화 몇 닢에 배신하지 않아.";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "또 맞췄군. 네 말처럼 금화 몇 닢이 아니라, 산더미만큼이지 - 만 두블룬이다. 우리가 합의만 하면, 포트 로얄의 은행가가 보증금을 준비해둘 거다\n하지만 내가 제일 중요한 조건으로 내거는 건 네 목숨이야, 드 모르 선장. 잘 들으라고. 지금 당장 모두 무기를 내려놓고, 네가 찰리를 우리에게 넘기면 추격은 완전히 멈춘다\n‘인간 대 사회’라는 말 들어봤나? 네 경우엔, 거절하면 ‘인간 대 국가’가 될 거다. 결정해, 찰스. 바로 여기서, 지금.";
			link.l1 = "네놈은 자기 직함이랑 영향력을 써서 멍청이 한두 놈쯤은 쉽게 겁줄 수 있겠지. 하지만 나는 그런 멍청이가 아니야. 그리고 절박함이란 놈은 멀리서도 냄새 맡을 수 있거든. 나가. 그리고 내가 널 죽이지 않은 걸 다행으로 여겨. 넌 그럴 만한 짓을 했으니까.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "콜로넬, 당신에게 정말 필요한 건 찰리가 아니라, 그의 침묵이오.";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "나랑 내 부하들의 안전을 위해 이 일에 동의하는 거지, 네 돈에 눈이 멀어서가 아니란 걸 알아둬.";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "인생에서 가장 최악의 결정을 내렸군, 드 모르 선장. 부럽지 않아. 정말이야. 이제 네가 자초한 일이야 – 다시는 이런 제안을 받을 일 없을 거다. 특히 나한텐 더더욱. 잘 가라.";
			link.l1 = "잠깐만요, 대령.";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "뭐야, 마음이 바뀐 거야? 내 말이 드디어 통했나?";
			link.l1 = "그래, 완전히 반대지.";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "무슨 말이야? 제대로 설명해 봐.";
			link.l1 = "네 말은 내 결심만 더 굳게 만들었어. 그렇게 쳐다보지 마라 - 널 죽일 생각은 없어. 그리고 말했듯이, 널 풀어주기까지 할 거다. 하지만 배 없이도 네가 알아서 살아남을 수 있을 것 같군.";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "나는 필요 없어, 내게는 배가 있으니까.";
			link.l1 = "네 말이 맞아. 하지만 그건 필요 없다는 점에서만 그래. 너는 영향력 있는 사람일지 몰라도, 눈치도 없고, 분수도 몰라. 내가 네가 늘 하던 대로 해줄게. 상황의 주인이 되어주지.";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "너는 아니야, 드 모르 선장. 자신을 속이지 마.";
			link.l1 = "완전히? 아마도 아니지. 하지만 너도 마찬가지야 - 이제 네 목숨은 내 손에 달렸어, 대령. 나중에 내가 어떻게 되든 상관없어 - 지금은 내가 원하는 대로 할 수 있지. 그리고 나는... 이 배를 가져간다. 넌 자유야. 해안은 멀지 않아.";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "감히 그러진 못하겠지. 그런데 네 표정을 보니... 작은 승리를 즐겨라. 네가 만든...";
			link.l1 = "그래, 그래, 내 인생에서 최악의 결정 중 하나였지. 그 얘긴 이미 들었어. 이 배에서 내려. 내 배야. 네가 스스로 뛰어내릴 거야, 아니면 우리가 바다에 던져줄까?";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_PkCh_7");
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "이렇게까지 망신당하고, 창문으로 뛰어내려서 네 발로 기어서 해안까지 헤엄치는 그를 보게 될 줄은 꿈에도 몰랐지.";
			link.l1 = "봤어? 만족했어? 좋아. 다음은 네 차례야.";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "무슨 말을 하는 거요, 나리? 우리는 적이 아니오; 나는 명령을 따랐을 뿐이오!.. 최소한 배라도 부탁할 수 있겠소? 다시는 내 얼굴 안 보게 될 거요!";
			link.l1 = "네가 내 입장이었고 나한테 방금 전투에서 졌다면, 나를 살려두지 않았겠지. 그러니 내가 널 죽이지 않은 걸 감사하게 생각해. 창문 밖으로 나가. 지금. 네 후원자를 따라잡을 수 있을지도 모르잖아.";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "차라리 죽는 게 이런 치욕을 당하는 것보다 낫소, 나리!";
			link.l1 = "원하시는 대로.";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "그게 바로 그 대령이었지, 선장?";
			link.l1 = "그래. 창밖을 봐, Charlie, 후회하지 않을 거야.";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_PkCh_13");
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "대령님이?.. 이런 꼴을 보게 될 줄은 꿈에도 몰랐소, 나리. 그런 높은 작위를 가진 사람을 평범한 선원처럼 바다에 던져버릴 줄이야! 리처드는 절대 그럴 사람이 아니오 - 계급을 존중하는 건 그 사람의 근본이었으니까.";
			link.l1 = "그건 수년간의 훈련으로 몸에 밴 거야. 그는 군인이고, 그에 맞는 사고방식을 가졌지. 나는 그렇지 않아. 더 넓게 생각하지, 그런... 제약 없이.";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "이렇게 해도 우리가 곤란해지진 않겠지?";
			link.l1 = "헤, 너는 리처드를 탓하지만 생각은 그놈이랑 똑같군. 우리가 감히 저항했으니 당분간 쫓기게 되겠지. 하지만 머지않아 영국 해군조차 우리를 포기할 거다. 그리고 린치에게는 이게 개인적인 일이 되겠지. 하지만 다음번엔 그놈이 국가의 지원을 받지 못하게 우리가 확실히 해뒀어.";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "있잖소, 선장님, 오늘부터 나는 당신을 더 존경하게 되었소. 디크랑 발키리호를 타고 떠나지 않고 당신을 따르기로 한 걸 절대 후회하지 않을 거요.";
			link.l1 = "고맙다, 친구야! 준비해라 - 폭풍이 우리에게 다가오고 있어. 하지만 있잖아? 왠지 또 우리가 이길 것 같은 기분이 들어. 가자, 갑판으로 돌아갈 시간이야.";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "그건 완전히 사실은 아니야. 솔직히 말해서, 앞으로 찰리가 입만 다물고 있으면 난 신경 안 써. 하지만 내 동료들은 그의 시체를 보고 싶어 해. 그리고 그들은 찰리가 어떻게 생겼는지 알아\n이건 현실이야, 찰스. 유모가 어릴 적 우리에게 읽어주던 동화나 기사 이야기 같은 게 아니라고. 모두가 만족할 만한 해결책은 없어 보여.";
			link.l1 = "하지만 나는 달라. 비슷한 시체는 언제든 구할 수 있지. 비슷한 옷도 살 수 있고, 뇌물도 먹일 수 있어. 내가 찰리와 얘기할게. 그리고 내 명예를 걸고 약속하지.";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				dialog.text = "이건... 큰 위험이야. 그리고 내가 네 말을 믿을 수 있느냐의 문제만이 아니지.\n동료들이 찰리와 닮은 시체를 보고 정말 믿을 수 있을지, 그게 더 문제야.\n그리고 나는... 그렇게 쉽게 그 위험을 감수하지 않을 거다.";
				link.l1 = "얼마야?";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				Notification_Reputation(false, 71, "low");
				dialog.text = "네 명성의 사내가 하는 말을 믿으라고? 웃기지 마. 고귀한 혈통만으론 신뢰를 얻을 수 없어.";
				link.l1 = "비슷한 출신과 행동을 가진 다른 남자에게서 이런 말을 듣다니, 용서해주시오, 대령.";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "네 말이 맞아, 물론이지. 하지만 이번에는 내 신뢰에 관한 문제야, 다른 누구도 아니고. 그리고 너는 보증인으로 내 마음에 들지 않아\n마지막으로 한 번 더 말한다. 찰리를 넘겨. 물론 플리트우드처럼 되고 싶지 않다면 말이지.";
			link.l1 = "네놈은 네 지위와 영향력을 이용해서 멍청이 몇 놈쯤은 쉽게 겁줄 수 있겠지. 하지만 나는 그런 멍청이가 아니야. 그리고 절박함이란 놈은 멀리서도 냄새를 맡을 수 있지. 나가. 그리고 내가 널 죽이지 않은 걸 다행으로 여겨라 - 넌 그럴 만한 짓을 충분히 했으니까.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "드디어 본론이군. 백만 페소. 마지막 제안이다.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "돈은 내가 내겠다. 내가 가난하다거나 내 부하들의 목숨을 소중히 여기지 않는다고 생각하지 마라. 둘 다 사실이 아니니까. 받아라.";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = " 넌 참 식욕이 좋구나, 뭐 그럴 줄 알았지만. 하지만 지금은 그렇게 많이 가진 게 없어, 그리고...";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "은화 없으면 거래도 없어. 내가 자비라도 베풀 줄 알았나? 내가 성인처럼 보이냐, 나리?";
			link.l1 = "그런데 혹시 조금만 기다려줄 수 있겠나? 어디서, 언제 다시 만나는 게 편하겠어? 내가 돈놀이꾼한테 두블룬을 빌릴 수도 있거든.";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "그럼 내가 생각했던 것보다도 더 순진하다고 생각하는 거야?\n나는 시골 처녀처럼 누군가가 한 번 건드리고는 영원히 기다릴 그런 여자가 아니야\n돈? 애초에 난 그런 거 바라지도 않았어. 나는 오직 찰리만 원해. 너는 내가 겪은 모든 고생에도 불구하고 내게 아무 쓸모도 없어.";
			link.l1 = "네놈은 자기 직함과 영향력을 이용해서 멍청이 몇 놈쯤은 쉽게 겁줄 수 있겠지. 하지만 나는 그런 멍청이가 아니야. 그리고 절박함이란 놈은 멀리서도 냄새 맡을 수 있거든. 나가. 내가 널 죽이지 않은 걸 다행으로 알아라 – 넌 그럴 만한 짓을 충분히 했으니까.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "정말 그 불쌍한 찰리에게 그렇게 정이 들었나?\n어쨌든, 너의 고결함은 존중받을 만하지. 네 포수 입을 무덤처럼 꼭 다물게 해. 그렇지 않으면 너희 둘 다 거기 가게 될 거다.";
			link.l1 = "약속하지. 그리고 너도 약속 지키고 추격은 전부 멈춰.";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "나도 약속하지. 그리고 한 가지 더. 네가 정정당당하게 이겼지만, 내 배는 내가 가져가겠어. 맞춤 제작한 거거든. 게다가 아주 비싸지.";
			link.l1 = "승자의 권리는 어쩌고? 하지만 이번엔 운을 너무 믿진 않겠어.";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_FadeLong("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "이 말 하게 되어 거의 미안하군, 브라이언. 하지만 우리 협력은 여기서 끝인 것 같아.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "나... 이제 자유인가요, 대령님? 제 머리에 걸린 현상금을 거둬 주실 건가요, 그러면 제가 마치 법을 지키는 사람처럼 새롭게 시작할 수 있는 겁니까?";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "네가 너무 많은 걸 봤다고 해야겠군 - 고 Fleetwood처럼 말이야. 방금 네 눈앞에서 사실상 뇌물을 받은 셈이지.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "나... 아무한테도 아무 말도 안 할게, 맹세코 신께 맹세해!";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "당연히 안 그러겠지.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "안 돼!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "그렇게 쳐다보지 마, Charles. 내가 Brian이 입을 놀릴까 봐 계속 걱정하면, 한숨도 못 잘 거야.";
			link.l1 = "내가 본 걸 보고 놀라야 할지 말아야 할지조차 모르겠군.";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "그러면 안 돼. 나는 이미 각오했어. 너희 둘한테 바라는 건, 일어난 일에 대해 입 다무는 것뿐이야.\n비슷한 시체를 찾아서 얼굴을 제대로 손보고, 돈도 잘 써서 동료들을 설득해 볼게.";
			link.l1 = "감사합니다, 대령님.";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "아직은 나한테 고마워할 일 없어. 놈들이 내 말을 안 믿으면 언제든 다시 추적이 시작될 수 있지. 일단은, 안녕히 계시오, 드 모르 선장. 난 내 배로 떠난다. 이의는 없어 – 이미 너랑 찰리한테 큰 신세를 졌으니까.";
			link.l1 = "그래, 그럼 잘 가라.";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_LT_25");
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "선장, 자네 지금 누구랑 얘기한 건지 알기나 해? 대령이었어! 이 모든 난장판을 꾸민 게 그 사람이었나?";
			link.l1 = "알아, 그가 자기소개했지. 그리고 네 말이 맞아 - 그랬어.";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "이상하군, 나리. 예전에 나는 그가 리처드의 상관이었던 걸로 알고 있었는데. 어떻게 이런 일이 가능하지? 그리고 왜 아무 일도 없었던 것처럼 떠나는 거지? 대체 뭘 원했던 거야?";
			link.l1 = "사실, 그건 전혀 이상한 일이 아니야. 수상쩍은 명령을 수행하는 자들은 적 때문이 아니라, 윗사람들 때문에 목숨을 거는 경우가 더 많지. 그리고 그자는 네 목을 원했어, 찰리.";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "이해가 안 돼요, 선장님. 그럼 왜 저 사람이 떠나는 거죠? 패배를 받아들인 건가요?";
			link.l1 = "그 사람답지 않지. 네 머리만큼 무거운 금을 줘야 했거든. 어쩌면 그보다 더 됐을지도 몰라. 정확히 말하면 백만 페소였어.";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "그리고 너... 그 엄청난 돈을 그에게 줬다고? 나 때문에?..";
			link.l1 = "글쎄, 너만을 위해서가 아니야. 나 자신을 위해서도 그렇고, 우리 선원들 모두를 위해서도 그렇지. 하지만 맞아, 찰리, 주로 너를 위해서였어. 우리가 그자를 죽였더라면, 그 뒤로 영원히 보복 원정에 시달렸을 거야.";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "나는... 이게 믿기지 않아, 나리. 그냥... 고맙소. 플리트우드가 당신 대신 그런 짓을 할 거라고는 생각도 못 했지.";
			link.l1 = "그가 도망친 후로 너무 편견을 가지는군. 리처드는 그냥 에비게일과 조용하고 평화로운 삶을 원했을 뿐이야. 그게 이루어지지 않아 유감이야. 게다가 그는 약속을 지켰고 네 빚도 갚았지. 허, 나, 플리트우드― 넌 정말 선장 복이 터졌구나, 찰리?";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "농담 아니야, 선장. 그래서 이제 다 끝난 거야?";
			link.l1 = "그래, 내 값비싼 친구. 적어도 지금은 말이야. 싸움은 끝났으니, 녀석들에게 무기를 집어넣으라고 전해. 그리고 돛 올릴 준비도 하라고 해.";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Bombardier Unlocked", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "네가 왜 동의하든 난 전혀 상관없어 - 탐욕이든, 두려움이든, 부하들에 대한 의무감이든 말이지. 중요한 건 네가 동의했다는 거야. 내 부하를 포트 로얄로 보내 은행가에게 지시를 전하겠다.";
			link.l1 = "좋아. 드디어 끝났다는 게 믿기지 않는군.";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "있잖아, 돈은 집어치워. 돈은 언제든 다시 구할 수 있지. 내가 찰리를 대신해서 진짜로 원하는 건 따로 있어, 대령.";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "오? 솔직히 말해서, 너한테 좀 놀랐군, 드 모르 선장. 그럼 네 생각엔, 산더미 같은 금도 마음에 안 든다면, 늙은 포수의 대머리만큼 값어치 있는 게 뭐가 있겠냐?";
			link.l1 = "네가 직접 말했잖아 - 결함이 보완된 훌륭한 배라고. 나도 직접 타보고 싶어 죽겠어. 설계도는 아직 네가 가지고 있고. 하지만 찰리란 놈은 세상에 하나뿐이지. 게다가, 날 만족시키는 게 너한테도 이득일 거야.";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				Notification_Perk(true, "Trustworthy");
				dialog.text = "협상 실력이 만만치 않군. 이런 거 하나 만드는 데 우리한테 얼마나 돈이 들었는지 알기나 해?";
				link.l1 = "(믿음직함) (명예) 나도 그걸 잘 알지, 그래서 묻는 거야. 네 손이 내 턱에 팔꿈치까지 들어와 있어. 이 늑대를 쏴 보려고 해도 좋아. 하지만 넌 그 손을 잃게 될 거다. 그것만이 아니지.";
			}
			else
			{
				dialog.text = "이런 걸 하나 짓는 데는 우리가 준비한 금보다 훨씬 더 많은 돈이 들어가. 그래도 너 때문에 재미있었어, 찰스. 좋은 의미로 말이야.";
				link.l1 = "시도해볼 만했지.";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "네가 원하는 게 뭔지 알고, 인생의 목표를 향해 나아가는구나\n좋아, 케치는 네 거다. 하지만 돈은 잊어라 - 돈꾼은 아무것도 모른다고 할 거야.";
				link.l1 = "그거면 나도 괜찮아.";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "확실하지. 내 인생은 기회를 잡고 위험에서 내 몸을 지키는 이야기였지\n그러니 찰리를 여기로 데려와. 그럼 우린 평화롭게 헤어질 수 있어. 그 다음엔 보증금도 가져가도 돼. 하지만 이 배는 내가 타고 떠난다.";
				link.l1 = "그럼 끝을 보자.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "완전히 만족한다고는 할 수 없어. 하지만 이 일은 빨리 끝내고 싶어. 이제 내가 원하는 걸 내놔.";
			link.l1 = "'무엇'이 아니라 '누구'지. 하지만 네가 원하는 대로 해.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "나도 그래. 이제는 사람이 어떤 존재냐뿐만 아니라 누구와 함께하느냐가 더 중요하다는 생각이 들어. 늙은 포수 하나 잡는 단순한 일이 그 선장, 그러니까 너 때문이야, Charles, 골치 아픈 일이 되어버렸지\nCharlie를 이리로 불러. 이 엉망진창도 이제 끝이다 – 닻을 올리고, 우리 배들은 각자 갈 길로 떠날 거야.";
			link.l1 = "버린다고, 너?";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "놀란 표정이군? 케치가 당연히 네 전리품이라고 생각했나 보지? 우리는 해적이 아니야, 드 모르 선장. 문명인은 훨씬 더 복잡한 규칙에 따라 살아. 그 배는 내가 가진다.";
			link.l1 = "그럼...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "괜찮으십니까, 나리? 저 사람이... 그 대령입니까?";
			link.l1 = "그래, 찰리, 내가 바로 그 대령이야. 네가 딱 맞춰 왔구나 - 내가 직접 널 데리러 갈 참이었어.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "나를 데리러 오라고요, 선장?.. 지금 당장? 왜 이렇게 오래 저... 저 인간이랑 얘기하고 있었던 거요? 무슨 일이라도 생긴 줄 알고 내가 직접 온 거라네.";
			link.l1 = "맞아. 우리가 이겼어도 여전히 곤경이야. 내가 대령이랑 해결책을 찾지 못했다면 지금도 계속 그랬을 거야.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "그 자를 우리를 내버려 두게 설득했나, 나리?";
			link.l1 = "안타깝게도, 나만이야. 우리 모두가 아니고. 너는... 그와 함께 가게 될 거야, 찰리.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "뭐?.. 왜?.. 우리가 이겼잖아!";
			link.l1 = "이해 못 해? 우리가 계속 이길 수만은 없어 - 놈들은 네 목을 얻을 때까지 절대 멈추지 않을 거야.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "늙은 찰리한테 이럴 수가 있나, 선장. 딕이랑 똑같군. 너희 둘 다 한때는 내 친구라고 했지. 그런데 결국 나랑 내 곁에 있던 사람들 모두를 버렸잖아.";
			link.l1 = "그게 바로 선장의 짐이고, 그의 책임이지. 너는 그걸 이해 못하는 것 같군. 네가 할 일이라고는 대포에 포탄이나 넣는 것뿐이었으니까.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "이해 못 하겠어?.. 내가 너 같은 배신자가 아니라서 그런 거 아냐? 어디로 가야 할지 알겠지?";
			link.l1 = "지옥으로? 어쩌면 네 말이 맞을지도. 우리 모두 그럴 자격은 있지.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "엿 먹으시오, 나리.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "우습군. 거의 웃을 뻔했어. 브라이언, 들었지?\n가끔 저런 평민들이 떠드는 걸 들으면 바람처럼 시원하지, 전혀 거슬리지도 않고. 잘한 결정이야, 찰스. 네가 얼마나 힘든지 이해해. 하지만 이제 너도, 네 부하들도 더는 고생하지 않을 거라는 사실에 위안을 삼아.";
			link.l1 = "이 약속 꼭 지키시길 바랍니다, 대령님.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "나는 내 말에 책임을 지는 사람이야. 아비게일의 운명이 그 증거지. 브라이언도 봐. 프랑스 해적이지만, 결정적인 순간에 옳은 편을 선택했어. 그리고 우리에게 충실히 복무하는 한, 아무도 그를 건드리지 못하지. 너도 그처럼 제대로 가고 있어, 드 모르 선장.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "움직이는 얘기가 나와서 말인데. 난 여기서 최대한 빨리 나가고 싶어. 네가 약속한 그 빠른 배, 의심할 여지 없이 정말 빠른 배 말이야, 대령.";
			}
			else
			{
				link.l1 = "나는 해적이 아니야. 그리고 아직 영국 함대에 합류할 생각도 없어. 하지만 약속된 보상은 반드시 챙길 거다.";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "숨기진 않겠네 - 마치 내 심장에서 그녀를 떼어내는 기분이야. 새 배를 사려면 돈을 써야겠지만, 어쩌면 그럴 만한 가치가 있지 - 찰리가 비밀을 털어놓을까 봐 너무 오래 걱정했거든\n네가 입을 다물고 영국에 심각한 죄를 짓지 않는다면, 이제 우린 더 이상 적이 아니라고 생각하겠네. 새 배를 즐기게나; 정말 멋진 배야. 잘 가게, 찰스. 브라이언 - 우리를 위해 보트를 준비하게. 찰리 - 넌 이 일에 발언권이 없으니 따라오게.";
				link.l1 = "잘 가라. 모두들.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "안타깝군, 우리는 언제나 유능한 인재가 필요하지, 국적이 뭐든 상관없어. 하지만 물론, 보상은 받을 자격이 있지. 안심하고 포트 로열로 가. 이 케치로라면 어떤 배보다 내가 먼저 도착할 테니까.";
				link.l1 = "그러길 바란다. 그리고 포트 로열에 무장 호위대가 날 기다리고 있지 않길 바란다.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "또 내 말을 의심하는 거야? 부끄러운 줄 알아라. 자네는 영국 해군 전체의 감사를 받았어. 뭐가 필요하거나, 우리와 함께할 생각이 들면 언제든 연락해, 드 모르 선장.";
			link.l1 = "한때, 영국 정보부와 연줄을 만들려고 했지. 실패했지만. 그럼 이만, 대령.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 
