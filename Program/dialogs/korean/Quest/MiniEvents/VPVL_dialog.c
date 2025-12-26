
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"! 실례하지만, 혹시 항해사요"+GetSexPhrase("또는","oress")+"?";
			link.l1 = "나는 선장이오 "+GetFullName(pchar)+", 당신을 위해 준비되어 있습니다.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "나는 레아야. 레아 카르노... "+GetSexPhrase("Monsieur","Mademoiselle")+" 선장님, 최근에 오셨나요? 혹시 바다에서 'Cormorant'라는 어선 못 보셨습니까? 사실 제 남편이... 제 남편 피에르가... 이틀 전에 출항했는데 아직 돌아오지 않았어요.";
			link.l1 = "'코르모런트'호? 아니, 그런 배는 본 적 없어. 그 이름이라면 기억했을 거야. 유감이오, 부인. 남편분이 무사히 항로에서 잠시 지체된 것일 뿐이길 바라오.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "'Cormorant'라고? 하! 그게 배 이름이냐, 아니면 선주 별명이냐? 뭐든 간에, 난 둘 다 본 적 없어.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "무슨 생각을 해야 할지 모르겠어... 이렇게 오래 집을 비운 적이 한 번도 없었거든. 항상 어김없이 정오까지는 돌아왔지. 그런데 지금은... 뭔가 일이 생긴 거야. 느낌이 와.";
			link.l1 = "당국에 가 보시오. 그들이 순찰선을 보내 해안가 바다를 샅샅이 뒤질 수 있을 것이오.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "무슨 생각을 해야 할지 모르겠어... 이렇게 오래 집을 비운 적이 한 번도 없었거든. 항상 어김없이 정오까지는 돌아왔지. 그런데 지금은... 뭔가 일이 생긴 거야. 느낌이 와.";
			link.l1 = "당국에 가 보시오. 그들이 순찰선을 보내 해안가를 샅샅이 뒤질 수 있을 것이오.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "오, "+GetSexPhrase("Monsieur","Mademoiselle")+" 선장님, 물론 이미 사령관에게 말씀드렸지요. 하지만 무슨 소용이 있었겠습니까? 그는 그냥 어깨만 으쓱했어요... 수색에 보낼 배가 없다고 하더군요, 제 남편을 위해서 말이에요.\n그리고 저는요? 이렇게 서서, 지평선을 바라보며, 기다리고... 바랄 수밖에 없지요.";
			link.l1 = "자자, Lea 부인. 아직 절망하지 마시오. 하루쯤은 당신을 도와 수색할 수 있을 것 같소.";
			link.l1.go = "Agree To Help";
			link.l2 = "뭘 그렇게 걱정해? 아침 바람이 그를 어디 매력적인 아가씨 품으로 데려갔을 수도 있잖아. 산책도 하고, 신선한 공기도 마시고, 곧 돌아올 거야.";
			link.l2.go = "bad joke";
			link.l3 = "조언 하나 해줄까? 지평선만 뚫어지게 보지 말고, 르 프랑수아의 선술집에 가서 네 남편을 찾아봐. 기분 나빠하지 말고, 아마 집안일에서 잠시 벗어나고 싶었던 것뿐일 거야. 네가 괜히 비극으로 만들고 있는 거지. 행운을 빌어.";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" 선장님, 저... 어떻게 감사드려야 할지 모르겠습니다... 선장님은... 이게 저한테 얼마나 큰 의미인지 모르실 거예요! 모두들 그냥 무관심한데... 그런데 선장님은... 도와주려고 하시네요. 정말 감사합니다!";
			link.l1 = "아직은 고마워할 필요 없어. 그냥 말해 봐—네 남편은 주로 어디서 고기 잡았지? 단골 자리가 있었어, 아니면 여기저기 돌아다니는 걸 좋아했나?";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "매력적인 숙녀라니?! 지금 농담할 때라고 진심으로 생각하는 거야? 그 사람이 곤경에 처한 거 나도 알아... 그런데 내 슬픔을 비웃다니! (울음) 지금 세상 모든 것이 나를 등지고 있어. 아무도 도와주려 하지 않고... 아무도 내 마음이 얼마나 무거운지 이해하지 못해.";
			link.l1 = "레아 부인, 제발, 제 경솔함을 용서해 주십시오. 모욕할 의도는 전혀 없었습니다! 맹세코, 남편분을 꼭 찾아드리겠습니다. 어디서부터 시작해야 할지 말씀만 해 주십시오.";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = "너...? 정말로 나를 도와주겠다는 거야?";
			link.l1 = "물론이지. 변명의 여지 없는, 때 아닌 농담을 속죄하기 위해 내가 할 수 있는 최소한이야.";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "감사합니다, "+GetSexPhrase("Monsieur","Mademoiselle")+" 선장님. 감사합니다... 정말, 이렇게 당황스러울 줄은 몰랐습니다—무슨 말을 해야 할지 모르겠군요...";
			link.l1 = "아직은 감사할 필요 없어. 대신 말해 봐—네 남편은 보통 어디서 고기잡이를 하냐? 단골 자리가 있나, 아니면 여기저기 옮겨 다니나?";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "음... 피에르... 걔는 자기가 어디서 고기 잡는지 잘 안 알려줬어. '자기만의 비밀'이라고 했지. 하지만 그걸로 걔를 찾는 데 도움이 된다면... 아마도... 잘 모르겠네... 정말로 도와주려는 거지, 그렇지, "+GetSexPhrase("Monsieur","Mademoiselle")+" 선장이라고? 정말이야?";
			link.l1 = "남편의 비밀 낚시터를 나와 공유할지 고민하고 계신가요? 당신 가족의 비밀은 내게서 절대 새어나가지 않을 것이오—선장으로서 맹세하오. 수색을 시작하려면 그 장소를 알아야 하오.";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "네 말이 맞아, "+GetSexPhrase("Monsieur","Mademoiselle")+" 선장님... 용서해 주십시오. 그곳은 피에르에게 정말 소중한 곳이었습니다. 그는 항상 거기가 자기만의 진짜 비밀, 작은 보물이라고 말했지요.\n하지만 어디 있는지 저는 압니다. 그를 집으로 데려오는 데 도움이 된다면... 그는 르 마랭 만 근처에서 낚시를 했어요. 남쪽 해안에 있는데, 마을에서 멀지 않습니다. 제발 부탁드립니다—그를 찾아 주세요!";
			link.l1 = "걱정하지 마, 레아. 내가 할 수 있는 건 다 해볼게. 그에게 원한을 가진 사람이 있었나? 최근에 누가 그를 위협한 적은?";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "적이라고? 피에르? 그는 세상에서 가장 착한 사람이야! 파리 한 마리도 못 잡을 정도라고... 그냥 평범한 어부일 뿐이야. 도대체 누구한테 잘못을 했겠어? 무슨 일이 있었는지 전혀 이해가 안 돼... 모든 게 너무 이상하고... 무섭기만 해...";
			link.l1 = "두려워하지 마시오, Lea 부인. 내가 곧바로 출발하겠소. 당신 남편은 분명 무사할 것이오. 사랑하는 당신 곁으로 꼭 데려오겠소. 힘내시오.";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" 선장님, 제발—소식이 있습니까? 뭔가 알아내셨나요? 뭐든 괜찮으니 알려주십시오?";
			link.l1 = "아직 아니야, 미안해. 그래도 계속 찾고 있어, Lea!";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
			LocatorReloadEnterDisable("FortFrance_Town", "gate_back", true);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "뭘 더 바라는 거야? 불쌍한 여자를 가지고 놀면서 아직도 재미가 부족하냐?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" 선장님! 피에르! 아, 이렇게 다시 보게 되어 얼마나 기쁜지! 그를 찾으셨군요!";
			link.l1 = "Lea 부인, 피에르 카르노를 직접 모셨습니다. 무사히 온 건 아니지만, 부인께서 돌봐주시면 곧 나을 거라 믿어 의심치 않습니다.";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "피에르! 성모 마리아님! 너 때문에 걱정이 이만저만이 아니었어! 어디 갔다 온 거야? 얼굴에 핏기 하나 없네... 이렇게 창백하다니... 어머! 이게 뭐야?! 이 끔찍한 상처들은 뭐지?! 베인 자국에... 화상까지...";
			link.l1 = "조용히 하렴, 내 마음의 보물아. 그냥 긁힌 상처일 뿐이니, 곧 사라질 거야. 다시 네 얼굴을 볼 수 있다니... 그게 내가 바란 전부였지. 선장님이 아니었더라면... 내가 빚을 졌구나\n "+GetSexPhrase("그를","그녀")+" 내 목숨 그 자체.";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" 선장님... 저... 어떻게 감사드려야 할지 모르겠어요... 그이를 찾아주셨군요! 제 피에르를 구해주셨어요! 감사합니다... 모든 것에 감사드려요! 주님께서 선장님을 지켜주시길 바랍니다, "+GetSexPhrase("Monsieur","Mademoiselle")+" 선장님!";
			link.l1 = "자, 자, 이제 그만하게. 피에르에게 정말 필요한 건 따뜻한 식사와 제대로 된 휴식이네.";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   Контры   //////
		
		case "Kontr Le Maren":
			dialog.text = "제기랄! 드디어 모습을 드러냈군, "+GetSexPhrase("이 더러운 똥개 놈아","이 비참한 계집아")+"! 도대체 어디 갔다 온 거야? 이 빌어먹을 해변에서 사흘이나 썩고 있었잖아! 우리 화물은 어디 있지?!";
			link.l1 = "내가 없으면 잔치가 시작도 못 하는 모양이군, 이봐, 자네들? 뭐, 내가 좀 늦었을지도 모르지만—아예 안 오는 것보단 조류를 타고 오는 게 낫지 않겠어!";
			link.l1.go = "Exit_Sneak";
			link.l2 = "나한테 말 거는 거냐? 쥐새끼처럼 함부로 떠들기 전에 예의부터 배우는 게 어때?";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-3.53, 2.35, 6.35, true, 1.93, -0.60, 11.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Experience gained", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Experience gained", SKILL_FORTUNE);
		break;

		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+", 이 멍청한 놈아! 눈 좀 똑바로 떠, 이 얼간이야—이 사람은 우리가 찾는 접선자가 아니잖아!";
			link.l1 = "아르... 또 총독의 앞잡이군! 조수처럼 확실하네! Since "+GetSexPhrase("이 악당","이 어리석은 계집애")+" 끌려갔다 "+GetSexPhrase("그 자신","자신")+" 여기서, 끌어올리자 "+GetSexPhrase("그를","그녀")+" 다른 쥐와 함께 동굴로. 우리가 보여주지\n "+GetSexPhrase("그를","그녀의")+" 어떻게 비밀을 빼내는지—얼마나 빨리 주인의 더러운 계획을 죄다 털어놓게 만드는지 알 거야!";
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.53, 2.35, 6.35, false, -0.03, 0.40, 7.77);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_2"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;
		
		case "Kontr Le Maren1":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = "네 머릿속에선 대체 무슨 더러운 망상이 썩고 있는 거냐, 이 소금에 절은 짐승아? 침이나 그만 흘려! 차라리 그녀를... 알지, 그놈한테 파는 게 낫지. 그런 멋진 아가씨라면 놈이 금화 상자 하나쯤은 내놓을 거고, 우린 한 달 내내 술 마시고 여자랑 놀 수 있잖아!\n";
			if (pchar.sex == "man")
			{
				dialog.text = "데이비 존스의 금고에 또 다른 허드렛일꾼이 우리 감방에 끼어들 이유가 뭐야? 저 놈 동료를 더 세게 조이면, 해 뜰 때 갈매기처럼 다 불어댈 거다. 이 놈은 여기서 당장 배를 갈라버리자, 두 번 다시 그놈 얼굴 볼 일 없게!\n";
			}
			link.l1 = "천 마리 굶주린 상어가 네 창자를 갉아먹어라, "+sld.name+"! 너야말로 이 군도에서 제일 교활한 밀수꾼이구나!";
			link.l1.go = "Kontr Le Maren2";
		break;

		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
					notification("No pistol equipped", "NONE");
					link.l2 = "저 따개비 대가리가 네놈들 중 제일 똑똑하다면, 나머지 놈들 머릿속엔 대체 얼마나 썩은 헛소리만 굴러다니는지 상상도 하기 싫군!";
					link.l2.go = "Kontr Le Maren3";
					CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
					locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
					sld = CharacterFromID("VPVL_contr_1");
					CharacterTurnByChr(sld, CharacterFromID("Blaze"));
					CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
				}
				else
				{
					link.l1 = "(속으로)(권총) 이 바다 쥐들이 쓸데없는 잡담이나 늘어놓는 동안, 나는 맑은 하늘의 번개처럼 빠르고 정확하게 공격할 기회가 있군.";
					link.l1.go = "murder";
					notification("Check passed", SKILL_PISTOL);
					locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
				notification("Skill too low (20)", SKILL_PISTOL);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_2");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
				CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
			}
			link.l2 = "저 따개비 대가리가 네놈들 중 제일 똑똑하다면, 나머지 놈들 머릿속엔 대체 얼마나 썩은 헛소리가 굴러다니는지 상상도 하기 싫군!";
			link.l2.go = "Kontr Le Maren3";
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "그 잘근거리는 혀를 네 머리에서 도려내주마, 이 건방진 놈아"+GetSexPhrase("","—더러운 창녀년")+ ", 그리고 갈매기 밥으로 던져버릴 테니 다시는 입도 못 열게 해주지!";
			link.l1 = "베어내 보라고, 알겠어? 자, 악마랑 한판 붙을 배짱 있으면 덤벼봐.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			//locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		
		case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"... 용서해 줘... 정신이 혼미하군... 너, 그들이 시작한 일을 끝내러 온 거냐?";
			link.l1 = "너 피에르 카르노냐?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;

		case "Pier_1":
			dialog.text = "아유, 그게 나야. 내 이름을 아는 거야?";
			link.l1 = "당연하지. 아니면 내가 여기서 뭐 하고 있겠어?";
			link.l1.go = "Pier_2";
		break;

		case "Pier_2":
			dialog.text = "용서해 주시오, 아무것도 이해하지 못하겠소... 고통과 굶주림에 정신이 혼미하오... 왜 오셨소?";
			link.l1 = "간단하오. 그대가 사라진 뒤, 충실한 아내분께서 부두에서 밤낮으로 기다리며 코르모란트의 돛을 애타게 찾았소. 그녀의 슬픔이 내 마음을 깊이 찔러, 그냥 지나칠 수 없었기에 그대를 찾기로 결심했소.";
			link.l1.go = "Pier_3";
		break;

		case "Pier_3":
			dialog.text = "내 아내... 내 사랑하는 레아... 다시는 그녀를 볼 수 없을 거라 확신했었지...";
			link.l1 = "그 조류는 이미 지나갔어. 그녀는 아직 희망을 품고 부두에서 널 기다리고 있어. \n여기서 나가자. 내 팔을 잡아.";
			link.l1.go = "Pier_4";
		break;

		case "Pier_4":
			dialog.text = "자비를... "+GetSexPhrase("Monsieur","Mademoiselle")+"... 잠깐만... 다리가 마치 표류목 같아... 정말 고맙소. 당신이 아니었다면... 마치 전능하신 분이 당신을 보내신 것만 같소... 아직 이름을 안 들었는데, 내 구원자를 어떻게 불러야 하오?";
			link.l1 = "Captain "+GetFullName(pchar)+". 힘을 좀 추스르는 동안, 어떻게 이곳에 오게 되었는지 이야기해 보시오. 이... 놈들과 거래라도 했소?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;

		case "Pier_5":
			dialog.text = "천만에요, 선장님. 저는 그저 평범한 어부일 뿐입니다. 오늘 아침만 해도 모든 게 순조로웠죠. 서쪽 해안에서 고기를 잡고 있었는데, 그날 조황이 정말 대단했습니다.\n생선을 통에 담고 다시 그물을 던지려고 서둘렀지만, 조류가 내 배를 암초 쪽으로 끌고 가는 걸 눈치채지 못했습니다. 선체는 달걀껍질만큼 얇아서 한 번 부딪히자마자 바닷물이 들이쳤죠. 아침에 잡은 고기로 가득했던 코르모란트호는 금세 가라앉고 말았습니다.";
			link.l1 = "그럼 결국 네가 상륙했더니 밀수꾼들이 널 총독의 첩자로 착각했다는 거야?";
			link.l1.go = "Pier_6";
		break;

		case "Pier_6":
			dialog.text = "그래, 맞아. 저주받은 파도에 휩쓸려 겨우 해안에 닿았지. 그냥 몸을 말리고 좀 쉬었다가 마을로 가려고 했을 뿐이야. 그런데 그 악마들이 어디선가 갑자기 나타났어.\n놈들은 나를 한 번 쓱 보더니 곧장 첩자라고 단정짓더군. 나는 말 한마디도 못 했는데, 바로 결박해서 여기로 끌고 왔지. 이틀 동안 굶기고 고문하면서 내가 모르는 것들—첩자니, 계획이니—자백하라고 했어... 하지만 나는 아무것도 몰랐어!";
			link.l1 = "저 무리 중에 머리 쓸 줄 아는 놈은 거의 없었지—그래서 지금쯤 게밥이 됐을 거다. 하지만 그건 이제 다 지난 일이야. 넌 자유야. 이제 아내와 다시 만날 시간이야—분명 애가 타고 있을 거다.";
			link.l1.go = "Pier_7";
		break;

		case "Pier_7":
			dialog.text = "나는 그저 다시 그녀를 안고 싶을 뿐이야. \n이제... 이제 걸을 수 있을 것 같아.";
			link.l1 = "그럼 더 이상 시간 낭비하지 말자.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "선장님, 제발 부탁드립니다—내일 저녁 여섯 시에 선술집으로 와주십시오. 제대로 감사 인사를 드리지 못한다면 제 양심이 결코 편치 않을 것입니다. 지금은... 제 마음을 어떻게 표현해야 할지 모르겠습니다. 꼭 와주십시오. 저에게 정말 큰 의미가 될 것입니다.";
			link.l1 = "좋아, 피에르. 걱정 마—내가 갈 테니까.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;

		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;

		case "PierTalkTavern":
			dialog.text = "선장님! 오셨군요! 제발, 이리로 와 주십시오!";
			link.l1 = "기꺼이!";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // Just in case
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;

		case "PierTalkTavern1":
			dialog.text = "당신의 계속되는 행운과 건강을 위해 우리 잔을 높이 들어 올리자!";
			link.l1 = "내 것뿐만 아니라, 피에르, 네 것도 마찬가지야. 내가 그 지독한 동굴에서 널 발견했을 때보다 훨씬 좋아 보이네. 건배!";
			link.l1.go = "PierTalkTavern2";
		break;

		case "PierTalkTavern2":
			dialog.text = "선장님, 제 끝없는 감사의 마음을 어떻게 다 표현해야 할지 모르겠습니다! 저를 그냥 지나치지 않으시고, 외면하지 않으시고—이렇게 이름 없는 어부를 도와주셨지요. 이런 고귀함에는 그에 걸맞은 보상이 있어야 한다 생각하여, 가진 것을 모두 드리고 싶습니다.\n여기—태양빛처럼 빛나는 호박 스무 개와, 침몰한 난파선에서 건져낸 희귀한 푸른 돌 다섯 개가 있습니다. 이제 모두 선장님의 것입니다.\n그리고 제 항해 도구와 낚시 장비도 받아주십시오. 이제 더는 배가 없으니, 저에겐 필요 없는 물건들입니다.";
			link.l1 = "고맙네, 피에르. 이건 분명 도움이 될 걸세. 하지만 가장 중요한 건 자네가 다시 집에 돌아왔다는 거지—이제 자네 아내도 더 이상 두려움에 떨지 않아도 되네. 두 사람 모두에게 상황이 나아질 걸세.";
			link.l1.go = "PierTakeGift";
			link.l2 = "피에르, 고마운 마음은 알겠지만, 그 돈은 네가 가져야 해. 배를 수리하고, 장비랑 그물, 통을 사려면 동전 한 푼이라도 아껴야 할 거야... 네 고마움, 그리고 너랑 네 아내가 다시 만난 것만으로도 충분한 보상이야. 서로 잘 챙기고 살아.";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "아직도 이 모든 일이 정말로 일어났다는 게 믿기지 않소... 내 가문의 새로운 시작을 위해, 그리고 그대의 고귀한 마음을 위해 건배합시다, 선장 나리!";
			link.l1 = "행운을 빌지, 피에르. 우리 모두에게 그게 좀 필요하거든!";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;

		case "PierWontGift1":
			dialog.text = "선장님, 이렇게 그냥 넘어갈 수는 없습니다... 제 목숨을 구해주셨으니 모든 걸 빚진 셈이지요. 호박이나 다른 선물은 거절하셨으니, 적어도 얕은 바다에서 고기 잡는 법을 당신 선원들에게 가르치게 해주십시오. 그러면 선원들이 배불리 먹을 수 있고, 식량비도 줄어들 겁니다. 어떻습니까?";
			link.l1 = "이거 정말 좋은 생각이군! 옛말에도 있잖아—그물 던지는 법을 가르치면 평생 굶지 않는다지.";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;

		case "PierWontGift2":
			dialog.text = "현명하게 말씀하셨군, 선장! 도움이 되어 기쁘네. 이제—한 잔 더 할까?";
			link.l1 = "피에르, 당신의 건강과 번영을 위하여!";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Four hours have passed...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
			int foodDays = CalculateShipFood(&pchar);
			dialog.text = "넵튠의 수염에 맹세코! 이거 진짜 독한 그로그잖아! 한두 모금만 더 마시면... 힉... 내가 크라켄도 깨울 만큼 큰 소리로 뱃노래를 부를 거야! 여기서부터 항구까지 모든 놈들이 내 목소리를 듣게 될걸!\n";
			link.l1 = "잔잔한 바다에선 그 노래 집어치워, 피에르. 목소리는... 헉... 다음 기항지까지 아껴둬. 네가 고래고래 소리 지르기 시작하면 나도 곧 따라 부르게 될 거야. 그리고 나는... 음... 급한 일이 있어서 말이지. 조수는 아무도 기다려주지 않아... 헉... 술에 취한 놈이라도 말이야! 몸조심하고... 헉... 네 착한 여인도 잘 챙겨!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			notification("Ship's provisions consumption reduced by 15%", "None");
			}
			else
			{
			dialog.text = "네푸튠의 수염에 맹세코! 이거 독한 그로그잖아! 한두 모금만 더 마시면... 헉... 내가 크라켄도 깨울 만큼 큰 소리로 뱃노래를 부를 거야! 여기서부터 항구까지 모든 놈들이 내 목소리를 듣게 될걸!";
			link.l1 = "잔잔한 바다에서나 그 노래 부르라고, 피에르. 목소리는... 헉... 다음 항구에서 아껴둬. 네가 고래고래 소리 지르면 나도 곧 따라 부르게 될 거야. 그리고 난... 음... 급한 일이 있어서 말이지. 조수는 아무도 기다려주지 않아... 헉... 술에 취해도 마찬가지지! 몸조심하고... 헉... 네 착한 아내도 잘 챙겨!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;

		case "PierTalkTavern4":
			dialog.text = "아, 선장... 그대는 진짜 뱃사람의... 크흑... 심장을 가졌구먼! 내가 진 빚은 평생 갚을 수 없지, 들리나? 다시 우리 항구에 닻을 내리거든... 우리 집, 우리 집은 마치 한... 한 어미에게서 난 것처럼 그대의 것이오! 내 영혼과 명예를 걸고 맹세하오! 포르투나가 그대를 다시 이 땅으로 이끌면, 또 같이 술잔을 기울이세!";
			link.l1 = "침착하게 가자, 피에르! 나 말이지... 헉... 내 바다 다리가 젤리처럼 풀리기 전에 닻을 올리는 게 좋겠어, 안 그러면 이 선술집 바닥에서 표류하게 될 테니까! 순풍이 네 돛을 가득 채우길 바라!";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
		break;

		case "Exit2":
			DialogExit();
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;

		case "RepeatTavern":
			dialog.text = "푸우우, 깊고 푸른 바다아아, 그리고 순풍이 불어오네... 헉... 해 뜨자마자 어장으로 항해한다!.. 젠장, 이 럼에 절어버린 머리로군! 가사가 생각이 안 나! 선장!.. 아직도 여기 정박 중이오? 주점 주인! 가져오시오... 헉... 네 창고에 있는 최고의 서인도 술을!";
			link.l1 = "출항한다, 피에르! 히끅... 아직 내 배로 돌아가는 위험한 길을 좌초하지 않고 항해할 수 있을 때 말이야!";
			link.l1.go = "Exit";
		break;

		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+"! 이 소금기 가득한 눈으로 이런 걸 보다니! 카리브 최고의 술 한잔 어때? 인생이라는 드넓은 바다에서 우리가 만난 걸 기념해서 말이야!";
			link.l1 = "네 얼굴을 보니 내 마음도 기쁘구나, 피에르. 하지만 오늘은 의무 때문에 술을 삼가야 하네. 내 항로는 맑은 정신과 흔들림 없는 손이 필요한 위험한 바다로 정해져 있거든. 다음에 우리 운명이 다시 맞닿을 때를 기약하세나?";
			link.l1.go = "MeetingInTneCity1";
		break;

		case "MeetingInTneCity1":
			dialog.text = "아유, 아유, 선장 나리! 배는 정박하기 전에 먼저 항해해야 하지. 상인들 말마따나, 장부가 먼저고 한가로움은 그 다음이야. 하지만 다시 운명의 여신이 우리 편이 된다면, 옛 블랙비어드조차 자랑스러워할 만큼 성대한 건배를 올리자고!";
			link.l1 = "배의 항해일지에 기록해 두게, Pierre. 조류가 우리를 다시 만나게 할 때까지!";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;

		case "ExitRepeat":
			dialog.text = "선장님! 당신 배는 의무라는 폭풍에서 무사히 피항했소?";
			link.l1 = "상업의 물결이 아직도 내 닻을 끌어당기고 있네, 피에르. 내 의무 때문에 한동안은 키를 놓을 수 없겠어.";
			link.l1.go = "Exit";
		break;
	}
}   