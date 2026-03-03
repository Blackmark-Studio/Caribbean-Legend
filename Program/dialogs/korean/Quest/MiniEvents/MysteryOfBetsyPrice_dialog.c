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

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "이봐, 미녀야, 네 아가씨의 소장품에 어울릴 만한 근사한 장신구 어때? 진짜 보물이야! 너한텐 부러운 시선이, 나한텐 빵이랑 럼 한 모금 살 동전 몇 닢만 주면 돼.";
			}
			else
			{
				dialog.text = "이봐, 선장, 네 여인에게 근사한 선물 하나 어때? 진짜 보물이야! 너한텐 그녀의 따뜻한 감사, 나한텐 빵이랑 럼 한 모금 살 동전 몇 개면 돼.";
			}
			link.l1 = "그래서 한 시간 뒤에 군인들이 나를 잡으러 와서 도둑질했다고 감옥에 쳐넣으라는 거냐? 이봐, 그걸 어디서 구했지, 떠돌이?";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "근사한 선물이라고? 그런데 너 같은 집 없는 놈이 그런 걸 어디서 구했겠어?";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("선장, 나","I")+" 카메오가 박힌 이 아름다운 펜던트를 발견했어, 정말이야! 내가 거짓말하면 바다에 가라앉아도 좋아! 그냥 아무도 원하지 않는 듯이 바닥에 놓여 있었어. 이런 아름다움을 흙 속에 그냥 두고 올 수는 없잖아?";
			link.l1 = "좋아. 거기 뭐가 있는지 보여 줘.";
			link.l1.go = "Poorman_3";
			link.l2 = "그렇게 존경받는 신사인 자네 말을 누가 믿겠나? 더 잘 속을 만한 다른 사람을 찾아보라고.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("선장, 나","I")+" 카메오가 박힌 이 아름다운 펜던트를 발견했어, 정말이야! 내가 거짓말하면 바다에 빠져 죽어도 좋아! 그냥 거기 버려져 있었어, 아무도 원하지도 않고. 이런 아름다움을 흙바닥에 그냥 둘 수는 없잖아, 안 그래?";
			link.l1 = "좋아. 거기 뭐가 있는지 보여 줘.";
			link.l1.go = "Poorman_3";
			link.l2 = "당신처럼 그렇게 존경받는 신사의 말을 누가 믿겠소? 더 잘 속아넘어갈 만한 다른 사람을 찾아보시오.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "봐봐... 이거 꽤 괜찮은 물건이야! 내가 꽃밭에서 찾았어, 등불이 달린 집, 선술집 근처에 있는 그 집 말이야. 그런데 오랫동안 아무도 거기 안 살아서 돌려줄 사람도 없어.";
			link.l1 = "재미있는 작은 장신구군. 그리고 그걸 얼마에 팔 생각이지?";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "겨우 백 페소지"+GetSexPhrase(", 선장","")+"... 너 같은 사람에겐 그저 푼돈이지! 하지만 나한텐—일주일 내내 빵 한 조각 걱정 없이 살 수 있는 돈이야. 이것 좀 봐—정말 멋지지 않나!";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "좋아, 여기 네 백 페소다.";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "난 사양할게. 다른 사람한테 시도해 봐.";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "감사합니다, "+GetAddress_Form(NPChar)+"! 이제 행운이 틀림없이 당신에게 미소 지을 거야! 당신은 좋은 사람이란 게 딱 보여.";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;
		
		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "오-오-오, 누가 우리를 찾아왔나? 문 잘못 찾아온 건 아닌 것 같은데, 자기야... 어서 들어와, 들어와! 옷 벗고 편하게 있어.";
				link.l1 = "오, 이거 이거... 여기 누가 왔나? 너희, 혹시 베시한테 그 '다정한' 협박 메시지 남긴 그 악당들 아니냐?";
			}
			else
			{
				dialog.text = "아, 아, 이건 또 무슨 오징어야?! 문 잘못 찾았냐, 이 염소 대가리야? 내가 배 갈라버리기 전에 썩 꺼져라!";
				link.l1 = "오, 이게 누구야... 여기 웬 놈들이지? 너희, 혹시 베시한테 그 멋진 협박 메시지 남긴 그 바보들 아니냐?";
			}
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "베치? 그딴 베치는 집어치워! 더 재밌는 건 네가 여기서 뭐 하고 있냐는 거지, 이쁜이... 어차피 여기 왔으니 서두를 필요 없어, 널 바쁘게 해줄 방법은 얼마든지 있으니까...";
			}
			else
			{
				dialog.text = "뭐야, 베시? 운명을 시험하지 마, 이 바보야. 아직 네 두 발로 나갈 수 있을 때 나가. 그렇지 않으면 우리가 너를 조각조각 주워서 양동이에 담아 내보내야 할 테니까!";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;

		case "BetsiPrice_1":
			dialog.text = "도와줘! 제발 도와줘!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;
		
		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "저기 그녀가 있군. 자네 지금 큰일 났어, 친구. 이게 마지막 실수가 되길 원치 않으면, 내 충고를 듣고 그녀를 당장 풀어줘.";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "하! 들었지, 레지? "+GetSexPhrase("그는","그녀는")+" 우리에게 협박까지 하고 있어. "+GetSexPhrase("뭐 이렇게 건방진 놈이야","뭐 이런 건방진 놈이 다 있나")+". 이봐, 보여주자 "+GetSexPhrase("이 건방진 놈 배알 색깔이 어떤지 보여주지","이 건방진 놈에게 진짜 고통이 뭔지 보여주지")+".";
			link.l1 = "그건 네가 죽을 일이지.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "이제 그 여자애를 풀어 줘라. 아니면 네 친구 옆에 같이 눕게 될 거다.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "이 빌어먹을 개새끼들! 내가 가만있을 줄 알았냐?!";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;

		case "BetsiPrice_2_1":
			dialog.text = "그리고 너... 너는 그들과 한패가 아닌 것 같군. 누구냐?";
			link.l1 = "Captain "+GetFullName(pchar)+", 당신을 위해 대기 중입니다.";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "그래서, 내가 네게 목숨을 빚진 거냐?";
			link.l1 = "그렇게 보이네. 하지만 지금은 다른 게 더 중요해 – 저 사람들이 누구고, 너는 도대체 무슨 일에 휘말린 거야?";
			link.l1.go = "BetsiPrice_3";
		break;
		
		case "BetsiPrice_3":
			dialog.text = "이 사람들... 그들은 영국의 중요한 관리가 보낸 자들이오. 한때 그는 나와 매우 가까웠지... 하지만 지금 보시다시피, 이제는 내 죽음을 바라고 있소.";
			link.l1 = "네 얘기가 이제 좀 이해가 가는군. 너는 그 자의 정부였지만, 어느 순간 그걸 이용할 수 있겠다고 생각했지. 겁을 주고 싶었던 거야... 그의 가족에게 말하려고?";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "의외로 아주 가까워"+GetSexPhrase(" 진실로, 잘생긴 놈아"," 진실로, 귀염둥이")+"... 그리고 동시에 그곳과는 아주 멀리 있지. 만약 그랬다면 나는 이미 죽었을 거야. 그래, 나는 그의 정부였지만, 가족 문제를 만들 생각은 한 번도 해본 적 없어\n모든 게 훨씬 더 복잡했지. 어느 날 그가 새로운 장난감을 찾아내고 나를 빈손으로 내쫓으려 한다는 걸 알게 됐어. 그냥 쓸모없는 물건처럼 버리려고 했지. 하지만 나는 아무것도 없이 떠나는 데 익숙하지 않아\n그래서 진짜 가치 있는 걸 챙겼어. 그의 인생을 망칠 수도 있는 서류들을 가지고 신세계로 도망쳤지. 그리고 거래를 제안했어. 내 안전과 후한 보상과 맞바꿔 그의 비밀을 넘기겠다고 했지\n그래서 내가 아직 살아 있는 거야. 그들이 그 서류를 필요로 하거든. 그리고 나는 그게 어디 숨겨져 있는지 서두르지 않고 말하지 않았지.";
			link.l1 = "음, 너는 아름다울 뿐만 아니라 악마처럼 교활하구나. 대담하게 놀았지만, 솔직히 말해서 이 게임은 이미 네 손을 벗어났어. 아직 기회가 남아 있을 때 다른 방법을 생각해보는 게 어때? 만약 여기서 들켰다면, 다른 데 숨어도 들키지 않을 거라고는 장담 못 해. 네 운도 언젠가는 다할 테니까.";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "무슨 소리야? 그냥 그 자식한테 서류를 넘기고 나는 빈손으로 남으라고? 내가 지금까지 겪은 게 얼만데?";
			link.l1 = "그놈들한테 너는 그냥 없애야 할 문제일 뿐이라는 거 알지? 자기들이 원하는 걸 얻을 때까지 절대 멈추지 않을 거야. \n하지만 아직 선택지는 있어. 저기 멍청이한테 서류를 넘겨. 그가 자기 주인한테 전달하게 하고, 네가 모든 의도를 포기하고 이 일이 끝나기만을 바란다고 확신시켜 줘.";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "그게 내 유일한 기회라면... 좋아, 위험을 감수할 준비가 됐어. 나는 항상 서류를 몸에 지니고 다녔어. 한순간도 떨어지지 않으려고 코르셋에 꿰매 넣었지. 잠깐만, 지금 바로...\n";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "여기, 가져가. 내가 가진 서류는 이게 전부야. 저 괴물한테 이별 인사라도 해줄래? 설득은 잘하지, 그렇지?";
			link.l1 = "그자는 이미 가장 중요한 교훈을 배운 것 같소. 이제 그에게 무엇을 해야 하는지 분명히 알려주기만 하면 되겠군.";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;
		
		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "일어나. 그리고 잘 들어, 이 자식아. 네가 받으러 온 서류들 여기 있다. 이걸 네 주인한테 가져가서 전해라. 만약 그자가 계속해서 베츠이를 죽이려고 자객을 보낸다면, 네 친구들과 똑같은 꼴을 당하게 될 거라고. 그녀는 이제 그의 인생에서 영원히 떠난다고, 더 이상 쫓을 이유가 없다고 전해. 이건 그녀가 화해를 위해 자발적으로 내딛는 마지막 걸음이라고 생각하라고 해. 이쯤에서 끝내길 바란다. 네 주인이 이성적으로 행동하길 바라지. 다 이해했나, 아니면 네 머리에 쑤셔 넣어줘야겠나?";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "모든 걸 이해했어, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "그럼 당장 꺼져. 그리고 얼쩡거릴 생각도 하지 마라 – 여기서 또 보이면 두 번은 없다.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "음, "+GetSexPhrase("나의 영웅","내 분노")+", 고마운 인사조차 잊어버렸던 것 같군... 다 흥분해서 그래. 이런 용감한 사람 덕분에 포로가 되었다가 다시 자유를 찾는 일이 매일 있는 것도 아니니까\n "+GetSexPhrase("구조자","구조한 여자")+". 말해 봐요, 아가씨들을 곤경에서 구해주는 게 원래 습관인가요, 아니면 내가 엄청 운이 좋은 건가요?";
			link.l1 = "뭐라고 할까, Betsy, 나는 극적인 등장에 약하거든 그리고\n "+GetSexPhrase("아름다운 아가씨들","온갖 모험")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "내 이름은 미란다야. 미란다 벨. 사라져야 했을 때 베치라는 이름을 썼지 – 새로운 삶, 새로운 이름, 무슨 말인지 알겠지. 나는 유럽에서 너무 급하게 도망쳐서 동전 몇 닢과 보석 몇 개만 챙겼어\n나머지는 아마 날 쫓던 그 개자식들 손에 들어갔겠지. 이제는 호화로운 연회나 값비싼 옷 대신, 변두리의 초라한 오두막과 선술집 일뿐이야. 언젠가 좋은 사람들과 와인을 음미하는 대신 럼주를 따라주게 될 줄은 상상도 못 했는데...";
			link.l1 = "이 모든 상황에도 불구하고, 당신은 마치 운명을 손에 쥔 사람처럼 보이는군. 어쩌면 그게 진짜 재능일지도 모르지.";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("아첨쟁이군. 하지만, 있잖아, 그게 너한테 잘 어울려\n","나를 치켜세우는군")+"... 이 모든 일이 있고 나니, 좀 불안하군. 혹시 저 모퉁이에서 벌써 나를 기다리고 있으면 어쩌지? 집까지 바래다줘, 내 \n "+GetSexPhrase("구세주","구세주")+" 조금만 더 오래.";
			link.l1 = "나는 일을 대충 끝내는 사람이 아니오. 그러니, 부인, 내 도움이 필요하다면 말씀만 하시오. 가시지.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "여기 도착했군. 그런데 말이야, 무슨 바람이 불어서 그 집에 가게 된 건지 묻지도 않았네?";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "나는 우연히 거기에 있었던 게 아니야. 이 펜던트가 나를 그곳으로 이끌었지. 받아.​ 선주가 네가 사라진 일로 몹시 속상해 보이더라. 그래서 무슨 일이 있었는지 알아봐 달라고 내게 부탁했어. 뭐, 내가 거절할 선택지가 있었겠어? 곤경에 처한 숙녀를 버리는 건 선장으로서 부끄러운 짓이지.";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
			else
			{
			link.l1 = "나는 우연히 거기에 있었던 게 아니야. 선술집 주인이 네가 사라진 일로 몹시 속상해 보이더라, 그래서 무슨 일이 있었는지 알아봐 달라고 부탁했지. 뭐, 내가 거절할 선택지가 있었겠어? 곤경에 빠진 숙녀를 내버려두는 건 선장으로서 할 짓이 아니지.";
			link.l1.go = "BetsiPrice_12";
			}
		break;
		
		case "BetsiPrice_12":
			dialog.text = "아, 정말 고귀하십니다, 선장님 "+pchar.name+"! 뭐, 선술집 주인은 나보다 자기 이익에 더 관심이 많았던 게 분명해. 안타깝게도 오늘은 너를 안에 들일 수 없어 – 좀 쉬어야 하거든. 지하실에서 보낸 시간 덕에 내가 더 예뻐진 것도 아니고 말이야. 하지만 우리가 다시 못 본다면 – 그건 절대 용서 못 해. 그러니 내일 꼭 선술집에 와, 너한테... 선물이 있을 거야.";
			link.l1 = "이제 또 들를 이유가 하나 더 생겼네. 잘 있어, M... 베시.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "아, 참 고귀하십니다, 선장님 "+pchar.name+"! 하지만, 선술집 주인은 나보다 자기 이익에 더 관심이 있었던 게 분명해. 유감이지만 오늘은 너를 안에 들일 수 없어 – 회복이 필요하거든. 지하실에서 보낸 시간 때문에 내가 더 예뻐진 것도 아니고. 하지만 우리가 다시 못 본다면 – 그건 절대 용서 못 해. 그러니 내일 선술집에 꼭 와, 너한테... 선물을 줄 테니까.";
			link.l1 = "이제 또 들를 이유가 하나 더 생겼군. 잘 있어, M... 베치.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "흠, 흠... 참 달콤한 작별이로군. 이 헝클어진 여자는 누구지? 지하실에 일주일은 처박혀 있었던 것처럼 보이는데, 그래도 넌 눈으로 핥아먹을 기세였지, 안 그래,\n "+pchar.name+"?";
			link.l1 = "네가 생각한 그런 게 아니야. 그 아가씨가 곤란한 처지에 있었고, 내가 도와준 것뿐이야. 그게 전부야.";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "그리고 너는 당연히 그녀의 빛나는 갑옷을 입은 기사라도 되기로 한 거냐?";
			link.l1 = "있지, 누가 위험에 처해 있는데 가만히 있을 수는 없어.";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "좋아. 하지만 다음번엔, "+pchar.name+", 좀 더 조심해... 그리고 나를 질투하게 만들지 마.";
			link.l1 = "물론이지, 자기야. 여기서 나가자, 아직 할 일이 많으니까.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "흠, 흠... 참 다정한 작별이군. 저렇게 신경 써주고, 다정한 약속까지... 이름도 그렇게 애틋하게 불러주고, 그래. 나도 며칠 사라져볼까? 그럼 너도 똑같이 애타게 나를 찾아주려나?";
			link.l1 = "메리, 너는 내가 행운을 부르는 부적인 거 알지. 그리고 그 여자는... 그냥 곤경에 빠진 아가씨일 뿐이야.";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "아, 그렇지! 그냥 기사님이 필요하다는 불쌍한 여자라 이거군! 그리고 너 그 눈빛은 뭐였냐 – 그것도 예의 차린 척한 거냐? 눈으로 거의 옷을 벗길 뻔했잖아!";
			link.l1 = "메리, 너 너무 과장하는 거 아냐! 내가 너를 어떻게 바라보는지 좀 봐. 차이가 느껴지지 않아? 아니면 내가... 가까이에서 다시 상기시켜줘야겠어?";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "알겠어, "+pchar.name+", 이번엔 간신히 빠져나갔군. 하지만 또 이런 꼴을 보면...";
			link.l1 = "그럼 내 마음속 첫 번째이자 유일한 자리가 누구인지 다시 한 번 상기시켜 줘야겠군. 어서, 자기야, 아직 할 일이 많아.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;
		
		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "음... 이렇게 가까이 있으니 내 머릿속에 온갖 생각이 떠오르는 걸 너는 상상도 못 할 거야... 그리고 그걸 얼마나 현실로 만들고 싶은지 모를 거야.";
					link.l1 = "그럼 생각만 하지 말고... 하나하나 다 보여줘.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "아, 내 사랑"+GetSexPhrase("","")+"... 네가 가까이 있으면 내가 얼마나 참기 힘든지 너는 모를 거야...";
					link.l1 = "그럼 이 달콤한 고문은 이제 그만하고... 내게로 와...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			switch (rand(1))
			{
				case 0:
					dialog.text = "아, "+GetSexPhrase("내 사랑스러운 선장님","내 사랑 "+pchar.name+"")+"... 나는 아직도 이 달콤한 광기에 사로잡혀 있어.";
					link.l1 = "어쩌면 이 광기는 기억할 만한 가치가 있을지도 모르지... 언젠가 다시 반복할 수도 있고.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "오, "+pchar.name+"... 내가 대단했다고 하면, 자만하지는 않겠지"+GetSexPhrase(", 그렇지?",". 그렇겠지?")+"?";
					link.l1 = "다시 한 번... 속삭이면서 말해준다고 약속하면 말이야.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}