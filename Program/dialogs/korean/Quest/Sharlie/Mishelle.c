// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "어서 오게, 방랑자 샤를! 마르티니크 동해안에서 해적들을 물리쳤다는 소문을 다 들었네. 이제야 확신이 서네, 내가 자네를 믿은 게 틀리지 않았다는 걸, 형제여.";
				link.l1 = "개자식들이 나를 함정에 빠뜨렸지. 하지만 우리를 얕봤던 거야. 내 항해사, 내 선원들, 그리고 나, 우리가 결국 이겼어. 솔직히 말하자면, 사랑하는 형제여, 처음엔... 상황이 꽤 암울했지.";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "안녕, 형제여! 나를 여기서 꺼내려는 네 진심 어린 열정은 고맙지만, 아직 다음 단계로 나아갈 준비가 안 되었구나. 내 계획에는 노련한 선장이 필요하다네. 계속해서 카리브를 탐험하고, 보상을 얻으며 배워라! 준비가 되면, 계속하자꾸나.";
						link.l1 = "뭐, 형이 뭐라 하든 상관없어. 여기 갇혀 있는 건 형이지, 난 아니니까.";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "형, 만나서 반갑네. 다른 이들에게 한 약속 잊지 마. 네가 한가해지면 바로 기다리고 있을게 – 다음 단계에 대한 아이디어가 있거든!";
						link.l1 = "알겠어, 형. 내 할 일은 처리할 테니, 곧 돌아올게!";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("Level 12 is required");
					dialog.text = "항해자 샤를! 자네의 모험담을 들었네! 이제 내 계획의 다음 단계에 거의 준비가 다 된 것 같군. 경험을 좀 더 쌓으면 바로 돌아오게.";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "안녕, 형제여! 나를 여기서 꺼내려는 너의 진심 어린 열정은 고맙지만, 아직 다음 단계로 갈 준비가 되지 않았구나. 내 계획에는 노련한 선장이 필요하다네. 계속해서 카리브 해를 탐험하고, 보상을 얻으며 배워라! 준비가 되면, 우리가 계속할 것이네.";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "형, 만나서 반갑군! 네가 진전을 이루고 있다고 들었어! 하지만 아직 내 계획의 다음 단계로 갈 준비는 안 됐지. 지금처럼 계속 해 보고, 준비가 되면 다시 찾아오게.";
						}
					}
					link.l1 = "그래, 뭐라 하든 형이니까. 여기 앉아 있는 건 형이지, 난 아니거든.";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "난 그렇게 생각하지 않아, 형. 너야 이 감옥에 이미 익숙해졌을지 몰라도, 난 오래 있을 생각 없어 – 우리 아버지는 영원히 기다려주지 않으시거든. 이제 말해.";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "안녕하시오, 샤를. 자네를 보니 내 마음이 기쁘구려. 확실히 더 나은 사람으로 변하고 있군.";
					link.l1 = "그런가? 그런데 그걸 어떻게 알았지?";
					link.l1.go = "gambit";//переход на Гамбит
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "알겠네. 샤를, 자네가 내게 소식을 가져온 것 같군! 자, 무슨 일인가? 부디 나쁜 소식은 아니길 바라네?";
				link.l1 = "지난번에 주신 조언을 따랐습니다...";
				link.l1.go = "saga";//переход на Сагу
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "드디어 왔구나... 무슨 소식이냐, 사랑하는 형제여?";
				link.l1 = "지난번에 주신 조언을 따랐습니다...";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "반갑네, 샤를! 푸앵시 기사님을 봤나? 만남은 어땠는가?";
				link.l1 = "그래, 사랑하는 형제여. 우리 만났지. 그리고 너에게 전할 소식이 두 가지 있어, 좋은 소식과 나쁜 소식이지. 좋은 소식부터 말하마. 내가 드 푸앵시에게 진 너의 빚을 해결했어. 나쁜 소식은, 내가 네가 약속한 이단자 문제를 해결하기 전까지는 그가 널 풀어주지 않겠다는 거야...";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "라 베가에서는 어땠소, 형제여?";
				link.l1 = "자랑할 건 정말 없어. 타이렉스는 개성 있는 녀석이지만, 그 녀석 식으로 일하는 건 내 스타일이 아니거든.";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "라 베가에서는 어땠나, 형제여? 소문을 들었는데, 솔직히 말해서 그리 유쾌하지 않구나... 찰리 프린스.";
				link.l1 = "그 소문이 뭔지 이제 알 것 같아. 하지만 그건 다 지난 일이야. 이제 타이렉스랑은 일하지 않아, 그 일은 내 취향에 너무 더러워졌거든.";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "흠, 인사하지... 코르세어 찰리 프린스. 말해 봐라, 샤를, 어쩌다 이렇게까지 추락했느냐? 믿을 수가 없군. 예전에 내가 스페인 상인 갤리온을 약탈하자고 한마디 했을 때조차 인상부터 찌푸리던 내 동생이, 이제는 이 지역에서 가장 위험하고 수배받는 해적이 되다니! 나조차 이 구덩이에서 허우적거리며 네 악명이 내 귀에 들릴 때마다 얼굴이 화끈거린다. 너를 라 베가로 보낸 그날을 저주했지. 이런 수치가 또 어디 있겠느냐! 프랑스 귀족이 해적 무리에 들어가 순식간에 그들 중 최악이 되다니! 이제 어쩔 셈이냐, 형제여? 해적 남작 자리라도 노리는 것이냐?";
				link.l1 = "아니. 이제 해적질은 완전히 끝냈어.";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "또 뭐가 있지, 샤를? 다 이야기한 것 같은데. 시간은 돈이야, 사랑하는 동생아 - 서둘러!";
			link.l1 = "그래, 그래, 간다...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "샤를!.. 만나서 반갑다, 형제여! 물론 네가 믿기 힘들 수도 있다는 건 알지만, 네가 여기 와서 나는 정말 기쁘다...";
			link.l1 = "하! 저 녀석 좀 봐라! 아주 신났군! 너는 그 잘난 '질서'를 들먹이며 잘난 척할 때, 샤를은 집안의 수치였지. 하찮은 화가에, 기생들 돈으로 연명하고, 궁정의 '기사'랍시고 굴었잖아, 안 그래? 그런데 이제 네 동료들 손에 감옥에 쳐박히고 나니, 그 한심한 동생을 보니 '세상 행복하다' 이거냐!\n";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "샤를, 너...";
			link.l1 = "아직 끝나지 않았어! 왜 프랑스에 네 소식을 전혀 알리지 않은 거지?! 서신을 주고받을 권리라도 박탈당한 거야?! 우리 아버지는 네 걱정으로 완전히 병이 드셨다고! 그래서 내게 네 운명에 대해 뭐라도 알아오라고 하셨단 말이야!..";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "샤를, 내가 아버지께 내게 무슨 일이 있었는지 어떻게 말씀드릴 수 있겠어? 뭐라고 편지를 써야 하지? 아니야, 형제여, 힘들더라도 아직은 아버지께 아무것도 알리지 않는 게 나아. 그리고 너한테 편지를 써도 소용없을 거야 – 파리에서 항상 주소가 바뀌니까... 그런데 어떻게 나를 찾은 거지?..";
			link.l1 = "아버지의 부탁으로 내가 몰타에 갔네. 그곳에서 자네 친구인 라 브리네 기사에게서 몇 가지 정보를 받았지. 그는 자네가 곤경에 처했다는 것과 마르티니크 어딘가에 있을 것 같다고 내게 편지를 썼네. 그 후 나는 프랑스로 돌아가 아버지를 찾아뵈었지. 그리고 이 모든 일이 끝난 뒤, 나는 이 찜통더위의 지옥 같은 곳까지 오게 되었네. 여기서는 모기들이 정말 사람을 갉아먹을 지경이야...\n";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "이 모든 걸 아버지께 말씀드렸어?";
			link.l1 = "아니. 그리고 라 브리녜 나리도 불행한 결과를 두려워하여 편지에 답하지 않았지... 아버지는 아직도 네 운명에 대해 아무것도 모르신다네. 나는 너를 찾고 이 일을 밝혀내기로 결심했어. 알아두라고 말하는데, 나는 너 때문이 아니라 불쌍한 우리 아버지 때문에 마르티니크에 온 거야!";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "정말이야? 샤를, 네가 가족을 신경 쓴 게 언제부터였지? 솔직히 말해보자, 형제여, 파리 사람들은 다 네 아버지가 누구인지 알고 있잖아. 네가 드 모르라는 가문 이름을 달고 있을지 몰라도, 드 몽페르의 이름이 더럽혀지는 건 원치 않지. 왜냐하면 그렇게 되면 네 혈통을 내세워서 모두에게 네 영웅담을 멋대로 떠벌릴 수 없게 되니까, 맞지? 파리 최고의 저택 문이 네게 닫힐 테고, 루브르 근처에도 얼씬 못 할 거야. 네가 전장에서 조국을 위해 싸우는 남편들을 두고 바람피우는 그 기생들과 정부들이, 나 같은 국가 범죄자의 동생과 기꺼이 주인을 배신하리라 정말 믿는 거야? 네가 여기 온 것도 어딘가 유부녀 침대에서 막 나온 거 아니냐, 맞지? 샤를, 왜 그렇게 얼굴이 굳었어? 내가 아픈 데를 찔렀나?";
			link.l1 = "너... 너!..";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "좋아, 형. 서로 쏘아붙였으니 이제 됐지. 나도 완벽하지 않다는 건 인정해. 하지만 형도 천사는 아니잖아. 샤를, 지금은 정말 다툴 때가 아니야. 우리 둘 다 같은 목표를 가지고 있잖아. 몽페르 가문의 명예와 위신을 지키는 것... 동기가 뭐든 간에 말이야. 형, 이번 한 번만이라도 우리 평화를 위해 감정은 접어두자. 어때?";
			link.l1 = "한번 해보자... 그런데 무슨 죄로 고소당했는지 설명해 줄 수 있겠어?";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "공식적으로는 협회 자금 지출에 관한 일처럼 들리지만, 실제로는 훨씬 더 깊은 사정이 있소.";
			link.l1 = "그래서 네가 조직의 돈을 횡령했다는 거냐? 흠, 그래...";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "그게 공식적인 혐의라고 말했잖아. 나는 루이도르 한 푼도 안 챙겼어. 어떻게 된 일이냐면... 있잖아, 내가 감옥에 갇혀 있는 한 모든 걸 자세히 설명할 수는 없어. 우리 협회의 비밀을 누설할 도덕적 권리가 내게는 없거든.";
			link.l1 = "부디 설명해 줘, 사랑하는 형제여. 나도 알 권리가 있지 않겠어?";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "좋아. 나는 카리브 해의 정치적 균형을 뒤흔들 아주 위험하고 섬세한 작전을 위해 돈을 받았네. 나는 프랑스 식민지의 총독 필리프 드 푸앵시의 직접 명령을 받고 행동했지. 하지만 내 모든 노력에도 불구하고 그 작전은 실패하고 말았네.\n푸앵시 나리는 자신의 무모한 계획이 모두 무너진 데 분노를 참지 못했지. 그는 내 체포 명령서에 직접 서명했고, 그 명령이 반드시 집행되도록 했네. 그리고는 이곳에 와서, 만약 내 가족이나 내가 작전에 쓰인 돈을 돌려주지 않으면 횡령과 기사단에 대한 반역죄로 고발하겠다고 선언했지.";
			link.l1 = "이거 참 꼴이 좋구나. 도대체 어디 있느냐, 네 멍청한 짓 때문에 우리 집안이 내야 한다는 그 돈이?";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "작전을 준비하는 데 썼지. 뇌물, 원정 조직, 온갖 물품과 장비 구입까지. 지출이 꽤 컸어. 내가 말했듯이, 나는 동전 한 닢도 챙기지 않았어.";
			link.l1 = "그리고 요구하는 금액이 얼마요?";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "백만.";
			link.l1 = "젠장! 농담하는 거지?!";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "내가 지금 농담할 기분으로 보이냐? 아니, 사랑하는 동생아, 이건 씁쓸한 진실이야. 우리는 드 푸앵시에게 백만 페소를 전달해야 해.";
			link.l1 = "하지만 젠장! 우리 집안엔 그런 돈이 있을 리가 없어! 이십 년을 모아도 그만큼은 못 모아!";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "내가 감옥에 갇혀 있지 않고 학회의 의무에 얽매여 있지 않았다면, 6개월에서 1년, 길어도 1년 반이면 해낼 수 있었을 거야.\n샤를, 여긴 신세계야. 모든 게 달라. 의욕 있고 야심찬 사람이라면 유럽에서처럼 평생을 바치지 않아도 이곳에선 스스로 큰돈을 벌 수 있지.";
			link.l1 = "반 년 만에 백만이라고?! 미쳤나? 그렇게 확신한다면, 그 얘기를 네 드 푸앵시 나리에게 해보지 그러냐? 그분이 널 풀어주게 말이야. 잘해 보라고...";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "아, 허튼소리 하지 마, 샤를! 푸앵시가 날 이 감방에서 풀어줄 리가 없어. 그렇게 쉬웠으면 내가 네 도움을 청하지도 않았겠지.";
			link.l1 = "그래서 내가 네 자유를 위해 돈을 마련해야 한다는 거냐?!";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "내 자유만이 아니지. 잊은 건 아니겠지? 궁전, 무도회, 그리고 귀족 창녀들과의 잠자리에 대한 이야기를 다시 해볼까? 그래, 샤를, 네가 해야 할 일이야. 물론, 예전처럼 파리에서 그 허영 가득한 삶을 계속 살고 싶다면 말이지. 그걸 원하지, 그렇지, 형제여?";
			link.l1 = "젠장, 도대체 어디서 그걸 구하란 말이야?! 이 근처에 잎 대신 루이 도르가 열리는 오래된 숲이라도 있는 줄 알아?";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "신세계 전체가 돈나무 숲이건만, 사람들은 게을러서 어리석은 머리를 들고 가지를 뻗을 생각조차 하지 않지. 걱정 마, 샤를, 넌 잘 해낼 거야. 어릴 적부터 널 알아왔고, 네가 어리석거나 게으르다고 생각했다면 아버지를 설득해 여기로 보내달라고 애쓰지도 않았을 거야.\n전에 말했던 단점들이 있긴 하지만, 넌 용감하고, 야망도 있고, 영리하지. 말도 잘하고, 레이피어 다루는 법도 알지. 여기서는 그게 정말 중요한 기술이야...";
			link.l1 = "정말 감사합니다. 내 사랑하는 형님께서 정말로 저를 칭찬해 주셨습니까? 저는 그저 한심한 화가이자 궁정 신하일 뿐이라고만 생각했는데...";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "헛소리 집어치워. 합의 본 거야, 아니야?";
			link.l1 = "미안해, 형. 저절로 튀어나왔어. 네 입에서 그런 말을 듣는 게 익숙하지 않아서 그래. 마치 거리의 창녀가 영혼 구원에 대해 설교하는 것 같잖아.";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "가자, 형제여. 내가 말했듯이, 넌 여기서 성공할 모든 자질을 갖췄어. 게다가, 넌 혼자가 아니야. 내가 무엇을 어떻게 해야 할지 조언해 줄 테니. 내 말만 잘 들으면 우린 멋지게 해낼 거야. 내 경험을 따라올 자는 없다는 걸 믿어도 좋아. 이제 쓸데없는 말은 그만하고 본론으로 들어갈 준비 됐지?";
			link.l1 = "그래, 당분간 여기 머물러야 할 것 같군... 좋아. 다 듣고 있네, 미셸.";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "그래, 형. 너는 여기서 한동안 머물게 될 거야. 이제야 그 사실을 받아들이니 다행이군. 파리에서 네가 돌아오길 기다리는 어떤 창녀가 있다면, 그냥 잊어버리는 게 좋을 거다. 그렇다고 너무 상심하지는 마. 이곳 여자들도 나름의 매력이 있으니까.\n하지만 이들은 진짜 남자, 강하고 당당하며 거친 남자를 좋아하지. 그러니 식민지 처녀와 함께 밤을 보내고 싶다면, 시나 그림 이야기, 달빛 산책 따위는 기대하지 마라. 그런 건 안 통할 테니까.";
			link.l1 = "좋아, 형. 허풍에 맞이라도 당한 거야? 본론으로 들어가자고. 충고라면 들을 용의가 있지만, 더러운 암시는 사양이야.";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "훌륭하오. 성공을 거두려면 우선 배를 소유해야 하오. 카리브는 군도라는 것, 알고 있겠지?\n이곳의 삶은 바다와 얽혀 있소. 자기 배를 가진 자는 끝없는 기회의 지평선을 갖게 되는 법이오.";
			link.l1 = "하지만 나는 선원이 아니야!";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "그럼, 이제 하나가 될 시간이야. 어차피 다른 선택지는 없잖아. 항만 사무소 서기가 되거나 주둔지에 등록할 생각은 안 했지? 아니지? 그럼 선장이 되는 거다.";
			link.l1 = "내 인생에 이런 일이! 그런데 내가 어디서 배를 구해야 한단 말인가?";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "우리 조선소에 훌륭한 루거선이 한 척 기다리고 있네. 크진 않지만 아주 편안한 배라서 항해의 세계에 첫발을 내딛기에 딱 알맞지. 이 루거선은 나를 위해 특별히 지어진 거야. 친구들의 도움을 받아서 오천 페소를 선금으로 내고 예약해 두었지. 조선공에게 가서 미셸 드 몽페르가 보냈다고 말하게. 그러면 자네가 왜 왔는지 바로 알 거야.";
			link.l1 = "배가 겨우 오천밖에 안 한다고? 좀 이상한데...";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "형, 내 말 듣고 있어? 오천 페소는 그냥 계약금이야. 루거 배 값은 대략 이만 페소쯤 해. 그러니까 나머지 돈은 네가 직접 벌어야 해. 게다가 선원들이랑 항해사 고용할 돈도 필요해.";
			link.l1 = "좋아! 그런데 그걸 어떻게 받지?";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "별로 놀랄 일도 아니지. 직접 벌어. 달리 방법 있나? 여기선 돈이 길가 풀숲에도 널렸으니, 어디를 찾아야 할지 알고, 고생을 두려워하지 않으면 돼. 이곳저곳 가게들을 돌아다녀 봐. 현지 사람들과도 얘기해 보고. 분명 무슨 일거리는 찾게 될 거야. 하지만 조심해, 정직한 사람보다 사기꾼이 훨씬 많으니까. 네가 정직하지 않다면, 집에서 값진 걸 좀 훔쳐보는 것도 방법이지.";
			link.l1 = "하지만 우리는 귀족이잖아, 그렇지?";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "여기서는 작위 따위 아무 소용도 없다. 모두와 똑같이 일하고, 싸우고, 훔쳐야 하지. 배를 사면 선원부터 구해라. 처음엔 네가 직접 배를 조종할 수 없으니 항해사가 필요할 거다. 이 모든 건 선술집 주인과 상의해라, 그가 도와줄 거다. 그리고 길 잃지 않게 조심하고. \n 바다로 나가면 곧장 과달루페로 향해라...";
			link.l1 = "저게 뭐지? 마을인가?";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "여기서 거의 이틀 거리 떨어진 섬이네. 군도 지도를 최대한 빨리 구해서 '주기도문' 외우듯이 익혀 두게. 그래야 마을과 섬 구분도 못 하는 바보로 안 보일 걸세. 군도를 이리저리 많이 돌아다녀야 할 테니 미리 준비해 두게나.";
			link.l1 = "흠. 좋아. 그럼, 이... 과들루프에서 내가 뭘 해야 하지?";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "거기서 '파데이'라는 이름의 남자를 찾아라. 그는 부두에서 멀지 않은 곳에 자기 집이 있다네.\n나를 안다고 전하고, 카드놀이에서 나에게 크게 졌으니 빚을 갚으라고 해라.\n네가 받는 돈은 다시 일어서는 데 도움이 될 것이네. 그 돈으로 시작해 보게.";
			link.l1 = "무슨 뜻이오, 일이 잘 돌아가게 하라는 게?";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "내 말은, 이 돈을 이용해서 더 많은 돈을 벌라는 거야. 예를 들면 무역 같은 걸로 말이지. 이 이야기는 나중에 다시 하자. 지금은 배를 확인하고, 과들루프로 항해해서 그 뚱뚱한 모스크바 놈을 찾아가 빚을 받아와야 해. 물론 말 그대로 받아내라는 건 아니야. 파데이는 과들루프에서 아주 존경받는 인물이자 현지 총독의 친구거든. 그러니 괜히 싸울 필요 없어. 오히려 친하게 지내도록 해. 돈을 손에 넣으면 바로 나에게 돌아와. 알겠지, 형제?";
			link.l1 = "알겠어. 아, 왜 이러지... 내가 뭘 잘못해서 이런 벌을 받아야 하는 거야...";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "슬퍼하지 마라, 샤를. 이것을 피할 수 없는 악으로, 아니면... 뜻밖의 축복으로 받아들여라. 나중에는 네 인생이 이렇게 흘러간 것을 운명에 감사하게 될 거다. 이제야, 형제여, 네가 진짜 사내임을 증명할 기회가 온 거다. 어쩌면 제대로 된 인간이 될 수도 있겠지...";
			link.l1 = "(튜토리얼 시작) 또 그 헛소리야?";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "(튜토리얼 건너뛰기) 형, 나 이럴 시간 없어. 지루한 건 건너뛰고 당장 바다로 나가고 싶어. 내가 빨리 배를 가지면, 너도 이 구덩이에서 빨리 나갈 수 있을 거야. 아니면 여기 더 있고 싶은 거야?";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "아니, 아니야. 오해하지 마... 좋아, 샤를, 시간 낭비하지 말고 바로 가. 무엇을 해야 하는지 알잖아. 네가 과들루프에서 파데이의 돈을 가지고 네 배의 선장으로 돌아오기를 기다릴게. 행운을 빈다, 형제여. 믿고 있네.";
			link.l1 = "실망시키지 않도록 노력할게. 좋아, 미셸. 다음에 또 보자!";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// таверна закр
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// ЦЕРКОВЬ закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// ростовщик закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// тюрьма закр
			bDisableFastReload = false;//open быстрый переход
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//устанавливаем прерывание на джунгли
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "헤! 이 '지루한 부분'이 언젠가 네 목숨을 구해줄지도 몰라... 뭐, 됐다. 지금 당장 돈을 구할 수 있는 쉬운 방법이 있다.\n현지 교회에 가서 베누아 아빠트에게 이야기해. 그는 우리 아버지의 오랜 친구야. 상황을 설명하고 무릎을 꿇고 배 한 척 살 만큼의 돈을 빌려 달라고 간청해.";
			link.l1 = "(튜토리얼 건너뛰기) 이제 훨씬 낫군! 이제 아빠트에게 가자.";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "(튜토리얼 시작) 내가 네 빚을 더 늘려주면서 시작해 주길 바라나? 나를 바보로 아는 거야, 형제? 이 일에선 네가 아무 도움이 안 된다는 거 뻔히 보여. 결국 다 내 몫이로군.";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "오! 내 예상이 틀리지 않았구나, 형제여. 과들루프에서 네 배의 선장으로, 파데이의 돈까지 챙겨 돌아오길 기대하고 있네. 행운을 빈다!";
			link.l1 = "다음에 보자. 여기서 잘 놀아.";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "그게 무서웠다는 말이야? 긴장하지 마, 형제. 정말 괜찮아. 나도 첫 해전 때는 영웅 같은 기분 전혀 안 들었어. 말도 안 돼. 한두 달만 지나면 이런 일쯤은 아주 평범하게 느껴질 거야... 파데이를 방문해 본 적 있어?";
			link.l1 = "나는 해냈지... 하지만 이런 식의 성공이라니... 대체 왜 애썼던 거지?";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "흠. 그게 왜지?";
			link.l1 = "그가 곤경에 처해 있기 때문이야. 최근에 도둑을 맞아서 자기 돈 문제도 있거든. 그래서 자기 소장품 중에서 단도를 하나 대신 주겠다고 하더라고. 값진 물건이고, 그 가치가 빚 전체 금액을 넘는다고 했어. 그래서 내가 그걸 받았지...\n";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "파데이? 빈털터리라고? 돈 문제라도 있나? 하하하! 네 덕분에 한바탕 웃었구나, 사랑하는 동생아! 그 빌어먹을 모스크바 놈이 널 단번에 초짜로 알아봤지, 그리고... 아, 그 자식! 아버지가 빚 대신 준 단검 좀 보여줘.";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "여기 있어...";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "지금은 가지고 있지 않아. 겉보기엔 그냥 평범한 단검일 뿐이지. 파디가 인디언 주술사가 마법을 걸었고 '족장의 발톱'이라고 불린다고 말해줬어.";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "흠. 그래, 어디 보자... 저 뚱뚱한 곰은 신께서 심판하실 거다. 저런 고물은, 샤를, 아무 상점에서나 살 수 있지. 네가 경험이 없다는 걸 이용해서 한탕 해먹은 거야... 자, 이 쇳조각 돌려줄게. 기념으로 간직해라. 선실 침대 머리맡에 걸어두면 되겠군.";
			link.l1 = "개새끼! 아, 알 게 뭐야... 과들루프로 돌아가서 그 기름진 놈을 한 번 흔들어줘야지!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "주술사에게 홀렸다고? 추장의 발톱? 그래... 다 알겠군. 신께서 그 뚱뚱한 곰을 심판하실 거야. 그런 잡동사니라면, 샤를, 아무 상점에서나 살 수 있지. 네가 경험이 없다는 걸 이용해서 한 수 속인 거야... 나한테도 무슨 요상한 이야기들을 늘어놓길래, 바로 제자리로 돌려보냈지. 그러니 이 발톱은 침실 위에 기념품으로 걸어두든가... 아직 쓰레기통에 버리지 않았다면 말이지.";
			link.l1 = "개새끼! 아, 알 게 뭐야... 과달루프에 가서 그 기름진 놈 한 번 흔들어 줄 거야!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "진정해, 형님, 좀 쉬어. 그런 짓 할 필요 없어, 바세테르 감방에서 두어 달 썩고 싶지 않다면 말이야. 내가 뭐라고 했는지 잊었어? 저 거드름 피우는 곰탱이는 과들루프 총독 클로드 프랑수아 드 리옹의 친구야. 내가 여기서 나가자마자 그와 얘기 좀 할 거야... 진심으로 말이지. 그 자는 도망 못 가.";
			link.l1 = "좋아. 네가 그를 처리하는 게 낫겠군... 그럼 나는 약속된 초기 자금도 못 받게 되는 건가?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "그런 것 같군, 샤를. 하지만 고개를 들어. 배도 있고 머리도 제대로 달려 있으면 카리브 해에서는 망할 일이 없지. 그리고 너는 둘 다 있잖아, 안 그래?";
			link.l1 = "무슨 말을 하려는 거지? 내가 이 단검으로 일을 망쳤다, 그래서 어쩌란 말이야...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "진정해, 형님! 왜 갑자기 그렇게 예민해졌어? 침착해, 오래 살려면 말이야. 아무런 암시도 안 했어. 그런 생각조차 안 했다고!";
			link.l1 = "미안해, 미셸. 그냥 내가 좀... 그러니까, 나도 좀 이해해 줘!";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "알겠소. 그리고 정말로 도와주고 싶소! 그러니 잘 들으시오. 좀 더 경험을 쌓고, 최소한 약간의 돈이라도 모은 뒤에야 더 중대한 일에 나서야 하오. 준비도 없이 모험에 뛰어드는 건 그야말로 자살행위요. 아직은 이곳에 짓눌려 무너지는 걸 보고 싶지 않으니.";
			link.l1 = "아주 감명 깊군. 무슨 모험 이야기를 하고 있는 거지, 미셸? 네 횡설수설을 듣다 보니 어느새 놓쳐버렸네.";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "형, 다시 한 번 상기시켜 주겠네. 내가, 아니, 정확히 말하면 우리가 드 푸앵시에게 백만 페소나 빚졌다는 사실을 말일세. 자네 정말로 그걸 정직하게 벌 수 있다고 생각하나? 물론, 그만큼의 무역을 할 수도 있겠지. 운이 따라준다면 가능하긴 하네. 하지만 카리브에서의 무역이란 것도 결코 평화로운 장사가 아니지.\n모험은 자네가 원하든 원치 않든 반드시 찾아온다네—문제는, 그때 자네가 준비되어 있을지의 여부지. 먼저 치는 것이 낫네. Si vis pacem, para bellum, 샤를...";
			link.l1 = "또 그 번지르르한 말투냐? 제발 좀 쉽게 말해 줘...";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "라틴어야, 사랑하는 형제여. 내가 말한 건 '평화를 원한다면 전쟁을 준비하라'였지. 이 말을 행동하는 지도자의 마음가짐으로 삼아라. 항해일지에 적어두고 매일 아침 기도 후에 다시 읽어도 좋을 게다. 배워야 할 것도 많고, 네가 깨달아야 할 것도 아직 많이 남았으니...";
			link.l1 = "좋아, 이제 그만하지. 네 과학 논문 따위는 지겨워졌다. 본론으로 들어가자.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "나는 구체적으로 말하고 있네, 그대가 아직 이해하지 못할 뿐이야. 좋아. 우선, 군도에 익숙해지고 배의 선장으로서의 새로운 삶에 적응해야 하네. 자신의 안위와 선원들의 급여를 보장하려면 열심히 일해야 할 걸세. 돈을 벌 수 있는 방법은 많지.\n화물이나 승객을 태우는 것이 가장 간단하지. 상점의 상인들은 그대에게 화물 운송 계약을 줄 수도 있고, 승객들은 거리에서 직접 찾아올 걸세. 항만 사무소도 확인해보게. 루거나 빠른 배가 있으면 심부름꾼으로 좋은 돈을 벌 수 있지.\n더 큰 배를 갖게 되면 항만 관리인들이 아주 수익성 좋은 화물 계약을 제공할 걸세. 사람들과 대화하되, 가문을 자랑하지 말고 친절하게 대하면 모든 일이 잘 풀릴 것이네. 식민지 총독들도 방문해 보게. 그들은 종종 보수가 좋은 일을 제안하네.\n무역을 시도해볼 수도 있지만, 그럴 경우 믿을 만한 경리 담당자를 고용하는 게 좋지. 바다에서는 조심하게. 스페인 군함이나 전함은 피하고, 만약 혼자 다니는 스페인 상인이나 방호 없는 호송대를 만나면, 붙잡으려고 시도해도 좋을 걸세.";
			link.l1 = "뭐라고?! 미셸, 내가 귀라도 먹었단 말인가? 네가 나보고 해적 생활을 하라고 제안하는 거야? 너, 소사이어티의 자랑이자 하느님과 삼위일체의 종인 네가, 그런 삶을 나에게 권하다니?";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "아, 샤를... 네가 그 깐깐함을 이제 완전히 버리는 게 좋겠어, 여기서는 전혀 환영받지 못하니까. 그리고 기사단에 대해서는... 순진하게 굴지 마, 형제여. 유럽에서는 루브르와 에스코리알이 그럭저럭 평화를 유지할지 몰라도, 여기서는 전쟁이야. 스페인 약탈선이라면 네 배를 약탈하고 너랑 선원들을 돛대에 매달아 말리는 것도 주저하지 않을 거다.\n그러니 적대국의 무역선을 약탈한다고 해서 아무도 너를 탓하지 않을 거야, 내가 장담하지. 사략 허가장만 있으면 관헌의 공식적인 지원까지 받게 될 테니까...";
			link.l1 = "당신의 인생 원칙이 이제야 조금 이해가 되는군. 마치 당신이 반년 만에 백만을 '벌' 수 있는 방법도 알 것 같은 것처럼 말이오.";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "그리고 이런 방법들을 써야 할 것이오, 샤를. 결국 이 모든 것은 당국이 앞에서는 물론 뒤에서도 지지하는 일이니. 설령 장사만 하려 해도 언젠가는 해적이나 스페인 약탈자들과 싸울 수밖에 없을 것이오. 그들에게 있어 그대는 전리품일 뿐이니까.\n이제는 예전의 인생관을 잊는 것이 그대에게 이로울 것이오. 내 말을 믿으시오, 형제여. 체면을 잃지 않을 뿐 아니라, 당국의 총애와 백성들의 사랑까지 얻으면서 할 수 있는 일이 참으로 많으니.";
			link.l1 = "넌 정말 나를 계속 놀라게 하는구나, 미셸. 이제는 해적이 되라고? 다음엔 또 뭘 시킬 셈이야?";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "지나치게 호들갑 떨지 마, 샤를. 정말 간단해. 사냥하든가, 아니면 사냥당하든가. 그게 전부야. 나는 전자를 선호하고, 너도 내 본을 따랐으면 한다. 그리고 해적이 되라는 게 아니라, 적대적인 국가에 대해 정당한 이유가 있을 때만 군사 행동에 나서라는 거야.";
			link.l1 = "보조금 말인가?";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, небольшое изменение диалога
		case "trial_15":
			dialog.text = "봐라, 네가 이해하고 있구나, 형제여. 하지만 말은 이쯤에서 그만두자. 이제 네 실력을 시험할 때다. 준비가 됐다고 느낄 때만 나를 찾아오거라. 돈도 좀 벌고, 더 좋은 배도 구하고, 제도도 익히고, 네 실력도 키워라.\n하지만 명심해라, 앞으로 몇 달을 선술집과 창관에서 허비하면서 아무것도 배우지 못한다면... 그땐 돌아오지도 마라. 알겠나, 샤를?";
			link.l1 = "걱정 마시오. 나는 놀러 온 게 아니오... 그 다음은 무엇이오?";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "나중에 그 다음에 무엇을 해야 할지 알려주지. 이미 계획은 세워두었네. 내 조언과 권고를 잘 따른다면, 샤를, 자네 앞날은 밝을 것이네.";
			link.l1 = "나는 그런 찬란하고 거창한 미래보다는 내 소박했던 과거가 더 좋겠어...";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "나를 믿어, 형제여. 네가 쓸모없던 과거를 비웃으며, 그곳에서 벗어나게 해준 운명에 감사하게 될 거야. 낙관적이고 긍정적으로 살아. 이 삶을 사랑하게 될 거다. 곧 알게 될 거야.\n아, 한 가지 더. 우리 공통 친구 파데이를 찾아가서 일자리를 부탁해 봐. 그 곰은 인맥이 넓으니 분명 뭔가 찾아줄 거야. 머뭇거리면 기회를 놓칠 수도 있으니 서둘러. 그리고 제발 나를 실망시키지 마.";
			link.l1 = "또 도덕 설교인가... 주여, 이 모든 게 언제 끝날까? 알겠네, 미셸... 이제 가도 되겠나?";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "잠깐. 전술적으로 몇 가지 더 조언을 해주지. 만약 어떤 국가와 충돌해서 무법자가 된다면, 현지 교회에 가서 브누아 아빠스를 찾아가게. 내가 보냈다고 전해라. 그 사람은 교황파와 칼뱅파 양쪽 모두에 연줄이 있어서, 나도 그런 문제로 여러 번 큰 도움을 받았지. 하지만 쉽지도, 싸지도 않으니 가급적 적을 만들지 않도록 하게.\n아, 한 가지 더! 우리는 귀족이지만, 특히 이곳에서는 손수 뭔가를 만드는 걸 꺼리는 건 어리석은 짓이네. 필요한 도구와 재료만 있다면 쓸모 있는 물건을 많이 만들 수 있지... 그런데, 형제여, 자네는 권총에 화약을 어떻게 넣는지 알고 있나?";
			link.l1 = "흠. 언제나 그렇듯이, 총알 하나랑 화약 한 줌이면 되지.";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "하! 딱히 다른 말을 들을 줄은 몰랐지.";
			link.l1 = "다른 방법을 아시오, 사랑하는 형제여?";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "물론이지. 하지만 무지와 게으름 때문에 그렇게 하는 사람은 드물어. 몇 시간만 투자하면 화약과 탄환으로 종이 탄약을 만들 수 있지. 그걸 쓰면 총 재장전 시간이 절반으로 줄어든다네. 감탄했나?";
			link.l1 = "흠. 그런 것 같군. 흥미롭네.";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "이 종이 탄피 제작법을 받아두고, 틈날 때 공부해. 그리고 새로 배운 걸 써먹는 걸 게을리하지 마라\n잠깐만, 형제여. 우리 소중한 총독님께 들르는 것도 잊지 마.";
			link.l1 = "무슨 일이라도 있습니까?";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, намёк на "Травлю крысы"
		case "trial_22":
			dialog.text = "총독들과 연락을 유지하는 건 언제나 좋은 일이야, 특히 그들이 네 친척을 자기 섬에 가둬두고 있다면 말이지.";
			link.l1 = "그에 대해 말해 보시오.";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "마르티니크의 왕좌를 지키는 건 아무나 할 수 있는 일이 아니지. 기사단의 이익, 왕실의 이익, 해적들의 이익... 그리고 귀족이라면 자신의 이익도 잊어선 안 되오. 파르케가 그렇게 물러터지고 죄에 쉽게 흔들리지 않았다면, 푸앵시도 그를 좀 더 진지하게 대했을지도 모르지.";
			link.l1 = "내가 그에게 무슨 쓸모가 있겠소?";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "관리들은 항상 자유 선장들에게 일을 맡기지. 하지만 대가를 짜게 주고, 그것도 공적인 일에만 해당될 때만 주지, 사적인 일에는 안 줘. 어쨌든, 카리브 해에서 명예를 지키고 국가 관계를 개선하는 데 총독들을 위해 일하는 것만큼 좋은 방법은 없어. 지금이 기회야, 특히 파르케가 요즘 곤란을 겪고 있으니 말이야. 무슨 곤란인가?";
			link.l1 = "무슨 문제인데?";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "미안하네, 형제여. 기사단의 이익이 걸려 있네. 우리가 빠르게 부자가 되길 원하는 유일한 사람들이 아니라는 것만 말해두지.";
			link.l1 = "또 뭔가 숨기고 있군... 뭐, 시간 나면 들르지.";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "이제 가거라. 행운을 빌어, 형제여!";
			link.l1 = "감사해... 나중에 보자, 미셸.";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			DialogExit();
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Sharlie_Mishelle_OpenWorld");
		break;
		
		case "gambitA":
			dialog.text = "네 뜻대로 하게. 나는 너를 믿어, 형제야. 지금의 너를 보면, 분명 더 나은 사람으로 변하고 있다는 걸 알 수 있어.";
			link.l1 = "정말이야? 어떻게 된 거지?";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "보이네, 사랑하는 형제여. 네가 걷는 모습과 얼굴 표정이 보여. 결국 너를 미치게 만들었던 그 잘난 척하는 어린아이의 가면이 완전히 벗겨졌구나. 이제는 새로운 삶이 분명히 너에게 도움이 되었겠지.";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "형, 네 말이 칭찬인지 모욕인지 도무지 알 수가 없군. 하지만 진실을 말해주지. 네가 나를 어떻게 생각하든 나는 전혀 신경 쓰지 않아. 네 빚을 갚기 위해 필요한 백만을 이미 모았으니 곧 자유의 몸이 될 거야. 드 푸앵시를 어디서 찾을 수 있지?";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "형, 네 말이 칭찬인지 모욕인지 도무지 알 수가 없군. 하지만 진실을 말해주지. 네가 저기서 나를 어떻게 생각하든 나는 전혀 관심 없어. 내가 처리해야 할 일은 산더미가 아니라 바다처럼 많으니, 여기 서서 너랑 말장난할 시간 따위는 없거든. 할 말이 있으면 해라. 아니면 난 이만 가겠다...\n";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// уберем маркеры, если ФМК не стали проходить
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "백만을 모았다고? 잘했네, 샤를, 정말 흠잡을 데 없군!\n하지만 유감스럽게도 필리프 드 푸앵시는 더 이상 저택에 없네; 사회의 일로 떠났고, 비밀 원정에 나섰지. 그러니 그를 만나려면 좀 더 기다려야 할 걸세.";
			link.l1 = "네 놈이랑 그 비밀 거래도 다 엿이나 먹어라! 이딴 거 다 끝내고 집에 갈 줄 알았는데, 이제 와서 또...";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "그리고 이제 너 덕분에 훨씬 더 많은 돈을 벌 기회가 열렸지, 그것뿐만이 아니야. 형제여, 네가 그 늙은 여우가 요구한 금액을 모았다는 건 대단한 일이지만, 내가 너라면 그렇게 자신만만하거나 태평하진 않을 거야... 드 푸앵시는 정말 미꾸라지 같은 놈이고, 네 보잘것없는 존재에 꽤 많은 관심을 보였으니, 그리고...\n";
			link.l1 = "이제 와서 백만도 그에게 부족할까 봐 두려운 거야?! 아니면 지난번에 뭔가 빠뜨린 게 있나?";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "나는 아무것도 두렵지 않지만, 푸앵시는 결코 만만한 사람이 아니라는 점은 경고해야겠소. 그가 자리를 비운 동안, 자네는 스스로의 위신을 세울 기회를 얻은 것이니, 그와 주종 관계가 아닌 동등한 입장으로 대화할 수 있도록 하시오. 그러니 내 계획을 반드시 따르라고 강력히 권하겠소. 지금 바로 설명해 주겠소.";
			link.l1 = "좋아. 이미 엎질러진 물이니 한탄해 봐야 소용없지. 이 지옥 같은 곳에서 좀 더 버티는 수밖에. 드 푸앵시도 영원히 바다를 떠도는 건 아니니까. 네 계획이 뭔지 설명해 봐.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "오! 훌륭한 대답이구나. 샤를, 네가 이제 어른이 되어 기쁘다. 하지만 네 형에게 너무 엄격하게 굴지는 말아라. 그건 그렇고, 할 말이 있단다. 다시 만나기를 고대해왔고, 네가 앞으로 무엇을 할지 이미 계획도 세워두었다.";
			link.l1 = "좋아. 그럼 자세히 말해 봐.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "봐라. 물론 카리브에서도 돈이 큰 역할을 하지, 어디서나 그렇듯이. 하지만 돈만으로는 모든 걸 해결할 수 없어. 성공한 사람은 두둑한 지갑뿐만 아니라 폭넓고 다양한 인맥도 갖춰야 해. 그리고 그 인맥이란 게 하찮은 놈들이 아니라, 이 세상에서 영향력 있는 사람들이어야 하지.\n그들이 어떤 국적이든, 어떤 신분이든 상관없어. 인맥은 돈만으로는 열 수 없는 문을 열어주지. '돈과 인맥'이 결합될 때, 사람은 세상에서 가장 귀한 것, 즉 권력을 손에 넣게 되는 거야.\n너도 그런 인맥을 쌓는 걸 생각해 봐야 해. 그런데 그건 단순히 화물 운송이나 무역, 소소한 해적질, 심지어 총독들의 환심을 사는 것만으로는 이룰 수 없어.";
			link.l1 = "무엇을 제안하시오?";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "카리브 해에는 그렇게 강력한 조직이 많지 않네. 그중 하나가 네덜란드 서인도 회사지. 자네도 그들에게 들어갈 수 있어. 본부는 퀴라소의 빌렘스타드에 있네. 회사는 종종 외부 선장들을 고용하고, 그중 가장 쓸모 있는 이들에게는 특별한 장기 계약도 제안하지.\n운이 좋으면 그곳에서 괜찮은 경력을 쌓을 수도 있을 걸세. 지금 회사가 심각한 곤경에 처했다는 소문을 들었네. 어떤 영국 사략선장이 회사를 상대로 무기를 들고, 계속해서 그들의 배를 침몰시키고 있다더군. 그들은 그를 어찌할 도리가 없어. 그는 해군 장교라서, 그들에게는 너무 벅찬 상대지.\n들리는 말로는, 그가 영국 군사 정보부와도 뭔가 연관이 있다더군. 그쪽 사람들은 아주 무서운 자들이지. 그러니 어쩌면, 그 선장 편에 서는 것이 자네에게 더 이득이 될 수도 있겠네. 문제는, 내가 그의 이름을 모른다는 거야. 다만 그의 근거지가 앤티가라는 것만 알고 있지.\n자네가 그곳으로 가서 수소문해 볼 수도 있겠지. 또 이 영국-네덜란드 분쟁에 관여하는 이상한 조직에 대해서도 들었는데, 어느 쪽 편인지는 모르겠네. 내가 아는 건, 그 흔적이 바베이도스, 브리지타운으로 이어진다는 것뿐이야...";
			link.l1 = "그러니까 네 말은 내가 네덜란드인들에게 입대하거나, 수상쩍은 선장이나 더 수상한 '조직'을 찾아보라는 거냐?";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "선택은 그대의 몫이오. 어쨌든, 카리브에서 남의 운명을 좌우하고 큰 권력을 쥔 자들과 빠르게 어울릴 다른 방법은 없을 것이오.\n혹시 총독에게 두세 번만 신세를 지면 곧바로 왕립 해군에 들어갈 수 있다고 생각한 건 아니겠지?";
			link.l1 = "알고 있지, 형님. 나는 프랑스 해군에서 군 경력을 쌓을 생각은 애초에 없었어. 신이시여, 내가 형처럼 어떤 임무를 못 해냈다고 감옥에 갇히는 신세가 되는 건 정말 싫으니까... 알겠어, 이해했어. 네덜란드 회사 총본부는 그리 어렵지 않게 찾을 수 있을 것 같은데, 나머지 일행들을 어떻게 찾아야 할지는 전혀 감이 안 와.";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "영국 사략선에 대해서는 앤티가의 세인트 존스에서 수소문해 보시오. 분명히 누군가가 알려줄 것이오. 영국 함대에서 일자리를 찾고 있다고 말하시오.\n'제3세력'에 관해서는 브리지타운 사람들에게 물어보면 되오. 그곳에도 이 조직과 연관된 이가 반드시 있을 것이오.";
			link.l1 = "그들의 일에 최소한 보상이 주어지는 건가? 회사, 그리고 저 사략선... 아니면 결국 다 '인맥'을 위해서만 하는 건가?";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "샤를, 자네는 나를 놀라게 하는군. 네덜란드 서인도 회사가 다루는 돈은 왕도 부러워할 만큼이지. 내가 말한 그 사략선장은 네덜란드 배를 워낙 많이 털어서 이미 부를 쌓고도 남았을 거야. 그리고 그 '조직' 사람들이 가진 건 단순한 돈이 아니야. 그야말로 어마어마한 재산이지. 그들과 일하면 언제나 달콤한 몫을 챙길 수 있어. 그런 사람들은 항상 크게 노리거든. 자네가 머리를 잘 쓰면, 자기만의 판을 벌여서 더 많은 걸 얻을 수도 있지.";
			link.l1 = "좋아. 곰곰이 생각해 보고 내가 할 수 있는 최선의 선택을 결정하겠소. 다른 지시사항이라도 있소?";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "그래. 항해 도구를 다루는 법을 배워야 하네. 안타깝게도 많은 항해사들이 나침반과 별만으로 방향을 잡을 줄 알고, 좌표를 제대로 계산하지 못하지. 그런데 이건 아주 중요한 일이야.\n좋아. 위도를 계산하려면 부솔을 사용하게. 이건 꽤 희귀한 도구라서 상점에서는 구할 수 없지만, 나침반과 아스트롤라베라는 흔한 두 가지 물건만 있으면 직접 만들 수 있네. 자, 여기 제작법을 가져가게.\n경도를 계산하는 건 좀 더 까다롭지. 등급이 매겨진 크로노미터가 필요해. 일반 선박용 크로노미터에 모래시계를 맞춰서 만들 수 있지. 문제는 이런 도구가 오차 때문에 한 달 정도만 제대로 작동하고, 그 이후에는 너무 부정확해진다는 거야.\n크로노미터는 항상 재설정이 필요하네. 모래시계는 네덜란드 서인도 회사 사무실에서 살 수 있어. 나도 거기서 크로노미터를 샀지. 자, 이 제작법도 받아두게.";
			link.l1 = "감사합니다. 바로 공부를 시작하겠습니다.";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "가능한 한 빨리 이 도구들을 모두 구비하도록 하게. 경험 많고 존경받는 선장들은 위도와 경도를 보고 항해하지. 그 숫자가 무엇을 의미하는지 알기 전까지는 항해술 초보로 여겨질 것이네.\n자, 최근에 우리가 논의한 일에서 성공을 거두면 곧장 자랑하러 오게나. 행운을 빌네, 샤를!";
			link.l1 = "고마워, 사랑하는 형제여. 이건 분명히 쓸모가 있을 것 같아!";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, убираем марки
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "그래서 자네는 자랑할 게 뭐가 있지?";
			link.l1 = "지금은 아무것도 없어. 세 조직 모두 찾아가서 일해 보려고 했지만, 시가처럼 처음부터 연기만 남기고 다 날아가 버렸지. 마치 운명이 나한테 등을 돌린 것 같아...";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "그럼 소문이 사실이었군... 사랑하는 동생아, 운명이 너를 거스르는 게 아니야. 그저 네 머리가 둔하고 손이 비뚤어진 탓이지. 실망스럽구나. 프랑스로 돌아가라, 여기서 네가 할 일은 더 이상 없다.";
			link.l1 = "하지만 어떻게...";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "이제 네가 상관할 일이 아니야. 내가 직접 처리할 거다. 내 문제를 해결하는 데 더 유능한 사람들이 따로 있지. 너한테 털어놓으면 평생 여기 붙잡혀 있을까 봐 두려웠다. 아무튼. 여기서 나가, 네 기녀들한테나 돌아가.";
			link.l1 = "좋아, 지옥에나 가버려...";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "너랑 이야기할 건 없어. 가.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "I've entered service with the Dutch West India Company and become a special tasks agent and close friend of the vice administrator of the Company, Lucas Rodenburg. I managed to carry out several serious missions, in particular, I liquidated the actual English privateer. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "holl_fail": sTemp = "I've entered service with the Dutch West India Company, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "eng_win": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship' and did away with Lucas Rodenburg himself, vice administrator of the Company. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "eng_win_half": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship'. Of course, Fleetwood departed to England and my service with him is over, but still..."; break;
				
				case "eng_fail": sTemp = "I've entered service with the English privateer from Antigua, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "self_win": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, and achieved quite a bit: I did away with that English privateer, Richard Fleetwood, put Lucas Rodenburg, the vice administrator of the Company, behind bars, become a close friend of governor Matthias Beck and the company's director Peter Stuyvesant. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "self_fail": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, however it all went down in dust at the moment of truth..."; break;
			}
			dialog.text = "그래서? 어서 말해봐, 사랑하는 형제여, 질질 끌지 말고. 좋은 소식이라도 있나? 네가 열심히 일한다는 소문이 내 귀에 들려오긴 했지만, 직접 네 입으로 듣고 싶었거든.";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "훌륭해! 정말 잘했어, 샤를! 나는 한순간도 네가 실패할 거라 의심하지 않았어! 멀리 나아갈 거야, 사랑하는 동생아... 그렇게 바쁘게 지내고 중요한 인물들과 인맥을 쌓다니—솔직히 기대하지 못했어. 축하한다!";
			}
			else
			{
				dialog.text = "속상해하지 마, 샤를. 일이 안 풀렸다면 어쩔 수 없는 거야. 우리가 원하는 결과를 얻기 위해 다른 방법을 쓰면 되지.";
			}
			link.l1 = "이제 어떻게 할까, 미셸? 드디어 슈발리에 드 푸앵시를 찾아갈 때가 된 건가? 그와 대화할 준비는 충분히 됐다고 느껴.";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "이미 필요한 백만 페소를 마련했소?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "예, 지금 필요한 금액을 가지고 있습니다.";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "아니, 아직 그만한 돈은 없어.";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "훌륭해! 그럼 나도 이 감방에 오래 앉아 있지 않아도 되겠군... 이제 캡스터빌로 가게, 그곳은 생크리스토퍼에 있네. 그리고 드 푸앵시를 만나겠다고 요청하게. 그는 총독 관저에 있을 것이야. 그 다음부터는 상황을 보아가며 판단하고, 한 가지 명심하게. 푸앵시는 교활해, 아주 교활하지... 이 모든 일이 그렇게 쉽게 끝나지 않을 것 같은 불길한 예감이 드는군. 가게, 형제여, 그리고 조심하게!";
			link.l1 = "네 조언 명심할게, 미셸. 걱정 마, 나도 바보는 아니니까. 이제 그 늙은 여우한테 가볼 테다. 나중에 보자!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "그렇다면 드 푸앵시와 얘기해 봐야 소용없겠군. 넌 안으로 들여보내주지도 않을 거야. 돈을 모아, 형제여. 이미 충분히 경험이 있으니 그리 어렵진 않을 거다. 돈이 준비되면 곧바로 세인트 크리스토퍼의 캡스터빌로 항해해라.\n슈발리에가 총독 관저에 있을 테니, 알현을 요청하면 들여보내 줄 것이다. 직접 확인하고 조심해라. 드 푸앵시는 교활해, 아주 교활하지... 내 느낌엔 이 이야기가 그렇게 간단히 끝나진 않을 것 같다.";
			link.l1 = "네 충고 명심할게, 미셸. 걱정 마, 나도 바보는 아니니까. 돈만 모이면 바로 그 늙은 여우한테 가겠어. 나중에 보자!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "이런 젠장! 내가 딱 그걸 걱정했지. 푸앵시가 오래전부터 네 뒤를 쫓고 있었어, 샤를. 그래서 네게 그렇게 관심을 보인 거야! 네가 카리브에서 꽤 이름을 날렸으니, 그놈이 너를 자기 망가진 임무를 대신 처리할 인물로 삼으려는 거지...";
			link.l1 = "미셸, 내 느낌엔 너 이미 다 알고 있었으면서 일부러 나한테 말 안 한 것 같구나. 일이 너무 술술 풀리고 있어... 돈도 그렇고, 이제 네 일까지... 이건 우연이 아니야.";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "샤를, 없는 데서 비밀 메시지를 찾으려 하지 마라. 네가 도착한 첫날 푸앵시에게 돈을 줬더라면... 뭐, 네가 그 돈을 갖고 있었다면 말이지. 그랬다면 슈발리에가 너에게 더 이상 아무것도 요구하지 않았을 거다. 하지만 이제 그가 너에게 흥미를 느끼고, 네가 이곳에 얼마나 쉽게 적응했는지, 또 무엇을 이뤄냈는지 보았으니, 네 재능을 이용하기로 마음먹은 거다.";
			link.l1 = "그렇지... 이제 네 재능이 그 자에게는 더 이상 쓸모없다는 거군, 안 그래? 제기랄! 좋아. 이제 막다른 골목에 다다른 것 같군. 그 이단자는 누구지? 어떻게 찾아야 하지?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "그를 찾으러 다닐 필요 없어! 그는 절대 토르투가를 떠나지 않고, 자신이 세운 요새와 충성스러운 위그노 병사들로 이루어진 수비대의 보호 아래 머물고 있지. 그래서 모든 병사가 그에게 충성한다네. 푸앵시는 프랑수아 르바쇠르, 토르투가의 총독을 말한 거야.\n스페인 놈들도 아직 그를 거기서 끌어내지 못했고, 푸앵시는 내가 해군의 지원도 없이 혼자서 그 일을 해낼 수 있을 거라 진지하게 믿었지. 왜냐하면 산토도밍고 수비대가 가까이 있기 때문에 내전을 일으키는 건 심각한 정치적 실수이기 때문이야.\n그 늙은 악당은 자신의 흠 없는 경력과 곧 다가올 연금을 위해 모든 걸 걸 위험을 감수할 생각이 없어. 하지만 르바쇠르는 도를 넘었고, 이제는 왕관에 위협이 되고 있지.\n르바쇠르를 지금의 자리에 직접 임명한 푸앵시는 이 무시무시한 위그노를 개인적인 원수로 여기고, 그를 몰타에서 여기로 데려온 내 직속 상관인 몰타 기사 드 퐁트네로 교체하고 싶어 하지.";
			link.l1 = "영광스럽군! 우선 백만을 벌고, 그다음엔 토르투가 총독을 암살하라니. 내 다음 임무는 뭔가? 에스코리알에서 음모를 꾸미라는 건가? 젠장! 네가 그 일을 망친 것도 놀랍지 않다. 총독을 제거하는 건 스페인 상인을 털 때와는 다르지. 네가 불 속에서 밤을 꺼내오겠다고 맹세했을 때, 최소한 어떤 계획은 있었길 바란다?";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "솔직히 말해서, 나는 아무런 계획도 없었어. 어차피 이 일만 끝나면 관직을 떠나고, 내 위험한 모험이 성공하면 우리 가문 저택으로 돌아갈 생각이었으니까. 개인적으로는 드 푸앵시의 문제 따위엔 전혀 관심 없어.\n인디언 금을 보기만 하면 저 인간도 훨씬 유연해졌겠지... 뭐, 지금은 그자가 우리를 상대로 모든 패를 쥐고 있으니 어쩔 수 없군. 레바쇠르가 토르투가의 총독으로 있는 한, 나도 여기 머물 수밖에 없을 것 같아.";
			link.l1 = "그런데 왜 드 퐁트네가 이끄는 몰타인들이 총독 자리를 노리며 토르투가를 직접 습격하지 않겠소?";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "상상해 보게. 기사단이 루이에게 선전포고를 한다고? 말도 안 되는 소리 하지 마시오! 그런 스캔들은 있을 수 없네. 토르투가를 점령할 수 있는 건 오직 사인뿐이야. 해적이든, 자네 같은 가톨릭 모험가든 말이지.\n그 후에야 그가 섬을 드 푸앵시가 새로 파견할 총독의 통제하에 넘길 수 있겠지. 그런 행동은 고위 정책 입안자들 입장에서도 아주 훌륭하게 보일 걸세.";
			link.l1 = "그럼 해적들과 협상하는 게 무슨 의미가 있나?";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "문제는 르바쇠르가 해적 형제단뿐만 아니라 그 밖의 많은 해적들을 지배하고 있다는 거요. 그는 그들이 토르투가의 포대 뒤에 숨고 약탈한 물건을 자유롭게 팔 수 있도록 허락하며, 전리품의 일부를 가져가지요.\n예전에는 드 푸앵시와 나누었지만, 이제는 더 이상 그러지 않습니다. 해적선들이 토르투가와 그 수비대를 지킬 것이니, 요새를 습격하는 일이 훨씬 더 어려워졌소.";
			link.l1 = "이 일이 가망 없다고 생각하시오?";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "항상 해결책은 있단다, 동생아. 다만 겉으로는 잘 보이지 않을 뿐이지. 모든 해적들이 토르투가의 위그노들에게 호의적인 것은 아니야. 나는 최소한 두 명의 영향력 있는 해적이 르바쇠르를 배신자이자 쓰레기로 여긴다는 걸 알고 있지. 내가 말하는 건 상어로도 알려진 스티븐 돗슨, 그리고 모스키토 만의 전설적인 남작 얀 스벤손이야.\n상어가 어디 있는지는 모르겠구나. 무슨 일이 생겨서 이슬라 테소로의 근거지를 떠났다는 소문만 들었지. 하지만 스벤손은 블루웰드에서 언제든 찾을 수 있어. 그곳에서 꽤 중요한 인물이거든.";
			link.l1 = "그럼... 스벤손이 나를 도와줄 거라 생각하시오?";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "네가 도와주면 그도 그렇게 할 거야. 지금 그 사람 상황이 그리 좋지 않아서, 충성스럽고 유능한 사람이 필요하지. 하지만 진지한 대화를 나누기 전에 먼저 네가 쓸모 있는 사람임을 증명해야 할 거야. 거기 도착하면 어떻게 해야 할지 방법을 찾게 될 거다. 여기서 조언해 주는 건 쉽지 않구나.\n계속 질문하는 걸 보니, 샤를, 네가 가기로 결심한 것 같군?";
			link.l1 = "있잖아, 미셸, 나는 방금 내 은화를 한 뭉치나 드 푸앵시에 넘겼어. 피와 땀, 눈물로 모은 돈이란 말이지! 내가 네 입장이었다면 너는 나를 위해 루이 도르 한 닢이라도 내놓았을지 모르겠군.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "샤를...";
			link.l1 = "내 말 끊지 마! 빈손으로 아버지께 돌아가는 건 어리석은 짓이야. 문제는 아직 해결되지 않았고, 넌 감옥에 갇혀 있을 뿐 아니라 협회 배신죄로 유죄 판결을 받을 위협까지 받고 있어. 내가 푸앵시의 '요청'을 이행하지 않으면, 그는 주저 없이 몽페르 가문의 이름을 더럽힐 거야. 그건 그의 얼굴에 다 쓰여 있었지. 그러니 난 스벤손에게 접근할 방법을 찾으러 블루웰드로 갈 거야. 그동안 네가 나한테 '말 안 한' 게 또 뭐가 있는지 곰곰이 생각해 봐. 예를 들어, 네가 드 푸앵시에게 가져다줘야 했던 인디언 금에 대해선 이번에 처음 듣는 얘기거든.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "숨겨두는 게 나은 일들도 있지. 네 말이 맞아, 내가 아는 걸 전부 말하진 않았어. 언젠가 더 말해줄 수도 있겠지만, 그건 네가 르바쇠르 문제를 해결한 뒤의 일이야. 지금은 알아도 쓸모없는 정보거든.\n네가 나를 걱정하는 그 감동적인 마음이 오직 우리 집안의 명예를 지키고자 하는 바람에서 비롯된 거라는 건 의심하지 않아. 나를 구함으로써 네 자신을 가장 먼저 구하는 셈이고, 덤으로 파리 최고의 저택들을 방문할 기회도 지키는 거지. 내가 틀렸나?";
			link.l1 = "이제는 더 이상 그렇지 않네, 형. 네 말이 옳았어. 내가 지난 몇 달 동안 카리브에서 보낸 시간은 내 몸과 마음, 그리고 세상에 대한 시각까지 완전히 바꿔 놓았지. 그리고 분명 더 나은 사람이 된 것 같아. 이제는 파리의 살롱도 더 이상 필요 없고, 언젠가는 몽페르라는 이름 없이도 살아갈 수 있을 것 같아. 드 모르라는 이름도 결코 뒤지지 않으니까...\n";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "...";
			link.l1 = "이제 나를 정말 아프게 하는 건, 네 불명예가 우리 늙은 아버지께 오점을 남길 거라는 사실뿐이다. 아버지는 진짜 상황이나 여기서 무슨 일이 벌어지는지 전혀 모르시지. 그리고 네 말대로, 가문 재산도 이 비참한 상태에서 반드시 회복되어야 하네. 네 석방을 위해 지불한 백만 때문에 내 금고도 크게 줄었으니, 분명히 다시 채워 넣어야 할 걸세.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "샤를, 그대는 인생의 모든 교훈을 훌륭히 깨달았구려. 진심으로 기쁘오. 그리고 프랑스로 돌아가는 대신 드 푸앵시의 부탁을 받아들인 것도 잘한 일이오. 모든 일이 잘 풀리길 바라며, 내가 이루지 못한 일까지 그대가 완수하길 바라오.";
			link.l1 = "어쩔 수 없을 것 같군. 카리브에 온 첫날부터 모든 걸 혼자 해왔지. 나중에 보자, 미셸. 다음에 만날 땐 네 석방 명령도 함께할 것 같아.";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "잠깐만! Jan Svenson에게 가기 전에 Marcus Tyrex를 꼭 만나고 가. 그는 해적 규약의 수호자야. Hispaniola의 La Vega를 다스리고 있지. 해적들 사이에선 무한한 권력을 가졌고, 스페인 놈들은 그를 무서워서 벌벌 떨어.";
			link.l1 = "그가 우리 일에 도움을 줄 수 있을까?";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "의심스럽군. 그가 어느 편인지 나도 잘 모르겠어; 아마 자기 자신만을 위해 움직이는 놈일 거야. 어쨌든 샤크와 스벤손은 필요할 테지만, 지금 이 바다에서 가장 힘센 해적은 타이렉스야. 그를 규약 수호자로 뽑은 데는 이유가 있지. 그렇게 중요한 인물을 무시해서는 안 돼. 스벤손을 만나기 전에 해적들을 좀 더 알아두는 것도 쓸모가 있을 거야. 어쩌면 그들 사이에서 네 이름을 알릴 수도 있겠지...\n";
			link.l1 = "또다시 해적 말투로 돌아가는군. 도무지 벗어날 수가 없나 봐? 좋아. 그에게 찾아가 보지.";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "해적이 되는 것과 해적들과 거래를 하는 것은 완전히 다른 일이오, 형제여. 그 차이를 알게 되길 바라오. 라 베가로 가서 타이렉스에게 일거리를 부탁해 보시오. 둘이 잘 맞지 않으면, 그 사람은 잊고 내게 돌아오시오.";
			link.l1 = "좋아, 미셸. 또 보자!..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "적어도 시도는 했군. 악명 높은 해적 남작과 '교류'할 기회도 있었지. 신경 쓰지 마라. 블루웰드에 있는 얀 스벤손에게 가게. 그를 네 편으로 만들어 보거라, 그렇지 않으면 르바쇠르와의 거래가 유혈 사태로 번질 것이니.";
			link.l1 = "좋아. 가는 중이야.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "멈춰줘서 다행이야, 형제여. 내가 예전에 말했지, 해적이 되는 것과 해적들과 거래하는 건 완전히 다르다고. 그런데 너는 길을 잃었어. 상어와 스벤손에게는 같은 실수를 반복하지 않길 바란다. 일은 하되, 그들과 거리를 두어라. 너는 프랑스 귀족이니, 그들보다 한 수 위에 있어야지. 이제 얀 스벤손에게 가거라. 그는 블루웰드에 있다. 그를 네 편으로 만들어 보아라. 그렇지 않으면 우리와 르바쇠르의 거래는 피로 끝날 것이다.";
			link.l1 = "좋아. 가는 중이야.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "진심이라면 참으로 기쁘오. 하지만 아무리 스페인 도시라 해도 불태우고, 여자까지 포함한 민간인을 죽이는 해적의 말을 내가 과연 믿을 수 있겠소?";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "멈춰... 타이렉스와 함께하던 시절에 내가 저지른 일들, 진심으로 미안하다. 나는 내 두 눈으로 지옥을 보고 왔어, 형제여... 아니, 이제 끝이야! 해적질은 더 이상 못 하겠고, 라 베가에는 절대 다시 가지 않을 거야. 내 명예를 되찾기 위해서라면 뭐든지 하겠어.";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "믿거나 말거나. 감옥에 갇힌 건 네놈이지, 내가 아니야.";
					link.l1.go = "saga_17gxa";
				}
			}
			else //заглушка
			{
				link.l1 = "그만해... 타이렉스와 함께 일하면서 저지른 온갖 악행을 진심으로 뉘우치고 있어. 내 두 눈으로 지옥을 보고 왔어, 형제여! .. 아니, 이제 해적질은 끝났어! 더 이상 라 베가에 있지 않아. 내 명예를 되찾기 위해 할 수 있는 모든 걸 다 하겠어.";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "오, 형제여... 신을 노하게 하지 마라... 이런 일이 스벤손과 샤크에게도 다시는 일어나지 않기를 바란다. 해야 할 일은 하되, 거리를 두고 저들이 어떤 자들인지 잊지 마라. 프랑스 귀족이 저들처럼 되는 것은 체통에 어긋난다. 스스로를 높여라. 이제 블루웰드에 있는 얀 스벤손에게 가서 그 늙은 코르세어에게 접근할 방법을 찾아보아라. 그가 없으면 르바쇠르 문제를 피로 적시지 않고 해결하는 것은 불가능하다.";
			link.l1 = "좋아. 지체하지 않겠어.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "상당한 노력이 필요할 거야, 형제여. 전에 내가 한 말을 기억하나? 해적이 되는 것과 해적들과 거래하는 것은 완전히 다르다고 했지. 너는... 됐다, 상어와 스벤손에게는 같은 실수를 반복하지 않길 바란다. 일을 처리하되 그들과 거리를 두어라. 너는 프랑스 귀족이니 그들보다 위에 있어야 하지 않겠나. 이제 얀 스벤손에게 가거라, 그는 블루웰드에 있다. 그를 네 편으로 만들어 보아라. 그렇지 않으면 르바쇠르와의 거래가 유혈 사태로 번질 것이다.";
			link.l1 = "좋아. 가는 중이야.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "지금은 대화할 때가 아니야, 형제여! 적이 우리 은신처에 들어왔어!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) sTemp = "I see you've become a captain of the navy... I didn't see that coming to be honest. I truly congratulate you!";
			dialog.text = "딱 맞춰 왔구나, 사랑하는 동생아! 이렇게 다시 보니 정말 기쁘다! 저 빌어먹을 카스티야 놈들이 이미 생피에르를 완전히 장악해 버렸어. 우린 이제 끝장이라고 생각했지! "+sTemp+"";
			link.l1 = "아직 안심하긴 이르다네, 도시는 깨끗하지만 그 쓰레기들은 요새에 틀어박혀 있고 전열함이 이끄는 대규모 함대도 있어. \n하지만 아주 기쁜 소식이 있네: 미셸, 자네는 이제 자유야!";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "내 귀를 의심하겠군! 이게 정말인가? 자유라니?!";
			link.l1 = "르바쇠르는 죽었고, 토르투가는 이제 그대의 옛 상관이 이끌고 있으며, 늙은 여우 푸앵시는 그대에게 모든 혐의를 취하했소. \n이제부터는 우리 가문의 명예를 위협할 것은 아무것도 없소.";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "나는 마지막 순간까지 의심했었네... 나를 놀라게 했군, 샤를. 내가 참담한 실패를 겪었던 곳에서 자네가 성공했어.";
			link.l1 = "행운은 용감한 자의 편이지, 형제여... 보다시피, 이제 나도 라틴어쯤은 안다네. 자네 감방 열쇠는 어디 있나?";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "내 감방 열쇠는 당직 장교 책상 위에 있을 거야. 거기서 찾아봐. 어쩌면 바닥에 떨어져서 어디로 굴러갔을 수도 있어...";
			link.l1 = "내가 가서 그놈들을 찾아올게!";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "드디어 자유다! 이 순간을 얼마나 오래 기다렸던가!";
			link.l1 = "나도 이 순간을 얼마나 오래 기다렸는지 모를 거야! 미셸, 우리가 반격할 사람들을 모을 수 있을까?";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "무슨 생각이야, 샤를?";
			link.l1 = "스페인 놈들이 주는 위협은 아직 사라지지 않았소. 나는 저들을 요새에서 몰아낸 뒤, 육지와 바다 양쪽에서 함대를 공격하기 위해 힘을 합치고 싶소! 성채의 대포를 이용하면 전열함과 맞붙을 수 있을 것이오!";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "우리에겐 인력이 있어. 많은 기사들이 총독 관저를 지키러 떠났지. 도시 안에서 누군가는 반드시 찾을 수 있을 거야... 내가 찾을 수 있는 사람은 모두 모을게. \n성문 밖에서 보자!";
			link.l1 = "...";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "여기 있다, 형제여, 우리의 군대가. 내가 찾아낸 모든 사람들일세. 수는 많지 않지만, 우리는 조국을 위해 싸울 것이오! 저 피비린내 나는 침입자들을 요새에서 완전히 몰아내자! 기습의 효과가 우리를 도울 것이니, 그들은 우리의 공격을 예상하지 못하고 있소. 앞으로 나아가자!\n";
			link.l1 = "Dulce et decorum est pro patria mori! 앞으로 나아가라!";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "끝났어, 형제야! 요새는 이제 우리 거다!";
			link.l1 = "스페인 함대와의 전투에서 그렇게 큰 타격을 입은 건 안타깝지만... 그래도 여전히 싸움을 이끌 만한 능력은 충분하지.";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "내 역할은 다 하겠소. 우리가 대포를 장전해서 적에게 큰 타격을 줄 테니!\n하지만 당신 함대가 접근하는 걸 보기 전까지는 움직이지 않겠소. 그렇지 않으면 전열함이 우리를 금세 산산조각 내버릴 거요.";
			link.l1 = "사람들을 모아라, 미셸! 나는 곧장 해안으로 돌아간다!";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "샤를, 기억해라: 전대에서 가장 위험한 배는 맨오브워다! 먼저 저 배를 격침시키도록 해라. 우리도 요새 포대에 남은 걸로 저 배에 집중 사격하겠다.";
			link.l1 = "좋아, 형. 어쩌면 내가 그녀를 잡아야겠군.";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "상황을 보아하니, 내가 너한테 가르칠 입장은 아닌 것 같군. 이제 시간 낭비는 그만하자!";
			link.l1 = "...";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "영광이 승리했도다! 승리를 축하하네, 형제여! 정말 대단했어! 스페인 놈들은 완전히 박살났군!";
			link.l1 = "이제 프랑스 식민지를 공격하기 전에 두 번 생각하게 될 거라 믿소.";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "이제 말해 보게, 샤를: 자네의 지난 인생이... 지금의 이 삶에 비해 얼마나 가치가 있나?";
			link.l1 = "상기시키지 마...";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "여기서 처음 만났을 때 내가 뭐라고 했는지 기억하나? \n'이 삶을 사랑하게 될 거야,' 바로 그 말이었지! \n그래, 그리고 정말 고맙네, 형제여. 자네의 도움이 없었다면, 난 아마 그 지하 기지의 감옥에서 절대 빠져나오지 못했을 거야.";
			link.l1 = "별말을 다 하는구나, 미셸. 어쨌든 너는 내 형제니까, 도와야 할 의무가 있었지.";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "형, 너 좀 봐라, 정말 감탄스럽구나. 눈빛에 저런 힘, 몸짓에 저런 자신감, 자세에 저런 위엄까지... 그 한심한 화가이자 궁정 어릿광대는 다 어디로 간 거냐? 정말이지! 내 가장 대담한 기대조차 뛰어넘었구나. 사실, 네가 이렇게까지 변할 줄은 정말 몰랐지...\n심지어... 조금 두렵기까지 하다. 네 목표를 위해서라면 뭐든 멈추지 않을 테니. 넌 대단해, 너무 대단해서 문제야...";
			link.l1 = "왠지 또 당신 말을 잘 이해하지 못하겠군. 또 나한테 불만이라도 있는 건가?";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "아니! 무슨 소리를 하는 거야?... 전혀 아니야! 그냥 흥분을 주체하지 못했을 뿐이야.";
			link.l1 = "좋아. 그럼, 이제 어떻게 할 거냐, 형제여? 계속해서 협회에 봉사할 생각이냐? 아니면 우리의 가문으로 돌아갈 거냐? 아, 그리고 거의 잊을 뻔했네. 한 가지 이야기해 주기로 약속했잖아.";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "정확히 무엇에 대해서?";
			link.l1 = "드 푸앵시를 위해 일한 것에 대해, 그에게 가져다주기로 했던 인디언 금에 대해, 그리고 네가 감옥에 갇히게 된 모든 일에 대해 말이야. 네가 나한테 말하지 않은 게 너무 많아, 미셸. 그래서 나는 거의 아무것도 모르는 셈이지. 그러니...";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "형제여, 내가 무슨 말을 했는지 정확히 기억하고 있네. 모든 걸 말해주겠네. 하지만 불타는 도시 한가운데서는 아니지!\n우리 둘 다 지금 할 일이 많네. 자네는 함대를 정비하고, 수리해서 다시 출항 준비를 해야 하네. 총독과 나는 주민들을 정돈하고 진정시키겠네.\n내일 아침 좋은 프랑스 와인 한 잔 곁들여 모든 것을 이야기하세. 믿게나, 형제여, 내게는 큰 계획이 있네. 정말로 큰 계획이지. 하지만 지금은 아니야. 내일 아침 아홉 시에 베누아 아빠스를 찾아가게. 나는 그곳에서 밤을 보낼 걸세. 그는 내 오랜 친구라네.";
			link.l1 = "좋아, 미셸. 그럼 이렇게 정하자고. 내일 대화 기대하고 있겠네.";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "대화 28.";
			link.l1 = "좋아, 미셸. 그럼 이렇게 정하자. 내일 대화 기대하겠네.";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "작별 인사는 필요 없어, 샤를!";
			link.l1 = "...";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, Captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with the brave Captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("We are all forever indebted to you, Captain! You have saved our colony from devastation!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are a brave and astute naval officer. All those residing in Saint-Pierre are praying for you, know that!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are the pride and joy of our nation and the hero of Saint-Pierre. We will never forget that!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = "또 만나는군, "+pchar.name+"...내가 경고했음에도 불구하고, 너는 여전히 나를 찾아 헤맸고, 그 수색 끝에 아주, 아주 멀리까지 오게 되었구나...";
			link.l1 = "미셸?... 왠지 놀랍지도 않군. 미겔 디초소가 또 보물을 찾아 테야살로 돌아온 건가? 흐흐흐. 그래, 나는 너와 만날 기회를 기다리고 있었지, 사랑하는 동생아. 네 뻔뻔한 눈을 직접 보고 싶어서 죽을 지경이었다. 게다가 묘지 납골당에서 날 암살하려던 시도는 정말 압권이었지. 그런데 먼저, 어떻게 불러야 하겠나? 미셸 드 몽페르인가, 아니면 미겔 디초소인가?";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "이 이름들은 더 이상 중요하지 않네, "+pchar.name+". 이제 모두 과거일 뿐이오, 곧 역사 속에서도 사라질 것이오. 지금이야말로 진실의 순간이오. 내가 처음 상륙한 이래로 길고 긴 25년 동안 조금씩 다가왔던 바로 그 순간이오...";
			link.l1 = "뭐라고?!! 이럴 수가... 이건 말도 안 돼!!!";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "그래, "+pchar.name+". 네 얼굴을 보니 내가 누구인지 이제야 알겠구나. 하지만 믿기지 않는 모양이지. 지난 몇 달 동안 네가 만나고 싶어 했던 그 사람이 바로 나다. 산티아고에서 온 신의 대리인, 즉 종교재판관이 너에게 전투의 축복을 내린 바로 그 사람 말이다.";
			link.l1 = "쿠쿨칸?!";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "동의하오. "+pchar.name+", 믿기 어려울 정도로 말이오. 인생이란 어떤 동화보다도 더 복잡하고 더 놀라운 것이니까...";
			link.l1 = "나는 뭐든지 각오했는데... 내 형이었잖아!";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "형제? 아버지의 피만 같을 뿐이지. 어머니는 다르다네, "+pchar.name+"알아두어라. 내 어머니는 카넥의 딸 쇼치케잘이라 불렸지. 어머니는 어리석게도 타야살을 떠난 뒤, 악명 높은 니콜라 고티에가 이끄는 프랑스 사략선원들에게 납치되었다. 그들은 어머니를 노예로 삼기로 했지. 그들 중에는 세르주 브누아라는 자도 있었다. 그는 선장의 짓거리에 부끄러움을 느껴 그를 떠나 수도사가 되었고, 지금은 브누아 신부로 네가 알고 있지. 우리 아버지 앙리 드 몽페르는 그때 해군 장교였어. 그는 쇼치케잘을 사서 프랑스로 데려갔고, 거기서 내가 태어났다. 거의 같은 시기에 너도 태어났지. "+pchar.name+". 너의 어머니는 너를 낳다 돌아가셨고, 우리 아버지는 정실부인이 쌍둥이를 낳았다고 선언하셨지.\n내 어머니 쇼치케잘은 우리 둘의 유모가 되었어. 너는 이차족 인디언 여인의 젖을 먹고 자랐지, "+pchar.name+"! 나중에 외할머니께서 당신을 교육시키기로 하셨고, 그래서 어머니의 성인 드 모르를 물려받게 되었지.";
			link.l1 = "그걸 다 어떻게 알아냈지?!";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "형님, 내가 남들보다 더 많이 안다고 생각하지 않으시나? 그리고 아버지도 내게 많은 것을 말씀해 주셨고, 나도 여러 가지를 알고 있소... 흔히들 말하듯, 그냥 감으로 하는 거지.";
			link.l1 = "이제 모든 게 분명해졌군... 그런데 네 어머니께는 무슨 일이 있었지? 왜 나는 한 번도 뵌 적이 없나?";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "그녀는 내 목숨을 구하다 죽었어. 내가 태어난 지 1년쯤 지나 병으로 거의 죽을 뻔했지. 내 어머니는 이차 사제의 딸이었는데, 나를 위해 비밀스러운 마야 치유 의식을 치렀어. 나는 회복했지만, 그 의식에는 천둥, 번개, 열대 폭풍이라는... 파괴적인 부작용이 따랐지. 쇼치케잘은 고발당하고, 마법 혐의로 종교재판에 넘겨져 화형을 당했어...\n";
			link.l1 = "그리고 너는 나아졌지...";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "나를 치유해 준 것 외에도, 이 의식은 내게 다른 능력들도 부여했지. 신들의 세계와의 연결도 열어 주었고. 그리고 그 다음 이야기는 이미 알고 있겠지. 이미 알다시피, 나는 백인의 지식과 경험의 빛을 과거로 가져가 마야 사람들에게 전할 것이다. 역사는 다시 쓰일 것이고, 너희 백인들이 이 세상을 지배하지 못하게 될 거다. 내가 반드시 그렇게 만들겠다.";
			link.l1 = "그러니까 평생을 최고의 해군 학교에서 공부하고, 군대와 몰타 기사단에서 복무한 게 결국 전부 군사 경험을 쌓기 위한 거였단 말이오?";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "정확히 그렇소. 내가 충분히 알게 되었을 때, 카리브로 배치를 요청했지. 말재주를 부려 푸앵시 기사에게 마르티니크에 근거지를 세우게 했소. 그 다음엔 테야살로 가야 했지. 내게 그리 간단한 일은 아니었소, 이 육신은 여전히 필멸의 존재이고 카리브의 차원문들도 제대로 작동하지 않았으니까.";
			link.l1 = "그리고 너는 미겔 디초소가 되었지...";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = "형제여, 나는 유럽 전장에서 이 별명을 얻었네. 그곳에서 라몬 데 멘도사 이 리바도 만났지. 인생이 우연으로 이루어진다고 생각하나? 전혀 아니네; 모든 우연은 알 수 없는 규칙성일 뿐이야. 내가 타야살로 돌아가기 위해 많은 일들이 준비되었지. 나는 두 개의 삶을 살아야 했네: 미셸 드 몽페르와 미겔 디초소. 그리고 사람들이 이 둘을 서로 다른 인물로 믿게 만들어야 했지. 너처럼 나도 드 푸앵시를 위해 해적이 되어 그의 신뢰와 호의, 그리고 돈을 얻어야 했네. 탐험대를 위해 병사를 얻으려면 해적 두목 중 한 명인 블레이즈 샤프를 라몬 데 멘도사의 부탁으로 죽여야 했고, 타야살의 보물 이야기를 드 푸앵시와 데 멘도사 모두에게 미끼로 던져야 했지. 드 푸앵시의 금고에서 은화 75만 피스를 받았고, 스페인 군함 프리깃을 해적 닷슨에게 팔았네. 그리고 탐험대가 출발했지. 나는 타야살로 돌아왔으나, 결국 실패만을 맛보았네...";
			link.l1 = "이해하오... 네가 겨우 다섯 살 꼬마로 아버지 영지에서 나비나 쫓고 있을 때, 위대한 사제 카넥은 도 알론소 데 말도나도의 타야살 침공에 겁을 먹고, 과거로 가는 데 필수적인 쿠쿨칸의 가면을 안전하게 숨겼지... 실례, 네 가면을 말한 것이었소.";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "그래, 카넥은 거기서 스스로를 속였지. 그는 가장 어려운 의식을 치렀어. 고대인들조차 감히 시도하지 않았던 의식이었지. 그는 새로 생긴 무인도에 가면을 숨기고, 크소체아템—소위 '진실의 수호자'—의 열쇠를 잃어버리고 말았어.\n나는 머리를 써야 했지. 그 의식은 타이살의 보물창고에서 보호받는 물건을 실은 어떤 배도 카리브해를 벗어날 수 없게 만들었고, 그런 배들은 모두 크소체아템 해안에 표류하게 되었어. 나는 그 점을 이용하려 했지. 멘도사를 달래기에 충분한 보물을 챙겼고, 의식의 보호를 받는 특별한 물건도 함께 가져갔어.\n이 물건을 실은 배는 반드시 크소체아템, 곧 내 가면이 있는 곳으로 끌려가게 되어 있었지. 그래서 나는 바다로 나가 멘도사에게 내 존재를 알렸어.";
			link.l1 = " 그래서, 혼자서 Tayasal을 떠난 거야?";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "멘도사의 병사들 없이 말인가? 물론이지. 여기, 타야살에서 모든 스페인인들이 죽임을 당했다. 이차족이 보물을 해안까지 직접 옮겼고, 나는 멘도사에게 병사들이 미스키토족의 매복에 당했다고 말했다. 그는 내 말을 믿었지, 금에만 관심이 있었지 사람에게는 관심이 없었으니까. 나는 '그리퐁도르'의 대포 아래에서 보물이 실린 배를 준비할 생각이었지만, 일이 훨씬 더 잘 풀렸지. 남작이 내 감독 하에 보물을 스페인으로 보내기로 결정했으니까. 그게 최고의 결과였어. 나는 그저 배가 카리브해의 보이지 않는 경계를 넘을 때까지 기다리기만 하면 됐지. 하지만 알고 보니 선장은 다른 명령을 받았더군. 우리가 대서양에 도착하자마자 특수 상륙조가 반란을 일으켜 선원들과 모든 장교들을 죽이기로 되어 있었어. 그 후 선장은 인디언 금을 멘도사에게 돌려주라는 명령을 받았지. 백인종의 훌륭한 표본 아니겠나, 형제여? 나는 위험을 감수해야 했어. 반란이 언제 일어날지 알 수 없었으니까. 하지만 모든 게 계획대로 되었지. '산타 키테리아'가 트리니다드 토바고 섬의 동쪽에 도착하자마자 폭풍이 들이닥쳤고, 프리깃함은 카리브해로 다시 휩쓸려 크소체아템 쪽으로 떠밀렸어. 그때 내 인생 최대의 실패를 겪었지. 파도에 휩쓸려 배에서 떨어졌고, 며칠 뒤 마르티니크의 르 마랭 만에서 정신을 차렸어. 어부들이 나를 발견해 르 프랑수아로 데려갔지. 하지만 내가 세자르 크레이그의 집에서 겨우 살아나고 있을 때 드 푸앵시의 부하들이 나를 붙잡았어. '그리퐁도르'는 내가 지정한 곳에서 '산타 키테리아'를 찾지 못했지. 드 푸앵시 기사단장은 인디언 금이 사라지고 기사단 금고와 자기 저축까지 함께 사라졌다는 사실을 알자마자 분노했어. 그는 나를 체포했지. 하지만 날 죽일 수는 없었어—죽이고 싶지도 않았지. 그가 원한 건 금이었으니까. 금! 그게 네 족속이 원하는 유일한 것이고, 신경 쓰는 전부야! 그걸 얻기 위해서라면 무슨 짓이든 하지... 나는 끔찍한 처지에 놓였지. 가면도 없고, 주머니에 동전 한 닢 없이 썩어가는 감방에 남겨졌으니까. 그때 내가 너를 불렀지. 그래, 그래, 사랑하는 형제여, 네가 나를 풀어주고 내가 태어난 일을 하게 해줘야 했어. 그리고 넌 정말 대단한 일을 해냈지. 이차족 젖을 먹고 자란 게 도움이 된 모양이야.";
			link.l1 = "내가 궁금한 건, 그럼 생피에르에서 도망칠 때 뭘 믿고 있었던 거지? 무슨 계획이었나?";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "처음부터 내 계획은 바로 너였어, 형제여. 쿠쿨칸은 사람의 마음을 읽을 수 있지. 내가 아빠트에게 남긴 편지는 네가 움직이게 하려는 의도였어. 내 예상이 맞았지. 나는 네가 산티아고의 종교재판관을 처음 만났을 때부터 네 행보를 지켜보고 있었어. 넌 내게 모든 걸 해줬지. 너는 진리의 수호자를 만들었고, 경쟁자들을 제거했으며, 크소체아템을 찾아냈어.\n나는 그곳에 있었고, 널 따라다녔지. 네가 테야살에 들어갈 줄은 예상 못 했지만 말이야. 넌 내 모든 기대를 뛰어넘었어. 그리고 네 도움으로, 나는 내가 태어난 이유, 인간의 육신으로 태어난 그 이유를 이룰 것이다.";
			link.l1 = "네 이성에 딱 하나 작은 문제가 있지, 사랑하는 형제여. 너는 네 가면을 가지고 있지 않고, 그 없이는 아무것도 아니야. 그 가면은 내가 가지고 있지. 그리고 난 너한테 줄 마음이 전혀 없어. 차라리 네 손에 들어가느니 산산조각 내버리겠어.";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "운명에 의해 정해진 것은 바꿀 수 없다. 내 유물을 훼손하는 건 절대 용납하지 않겠다. 느껴진다... 그 유물, 네가 가지고 있군. 그리고 넌 지금 내 사원, 내 힘이 온전히 미치는 이곳에 있다! 이곳을 절대 떠나지 못할 것이다. 이제 마지막 시험의 시간이다, 사랑하는 동생아. 쿠쿨칸과의 전투에서 네가 어떤 존재인지 보여 보아라!";
			link.l1 = "네 필멸의 육신도 아직 피를 흘릴 수 있겠지!";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "하! 안됐다, 샤를. 정말 안타깝군. 하지만 신과 싸울 기회쯤은 받을 만하지. 아무 의미 없어도 말이야. 첫 막을 살아남으면, 그때 가서 알려주지.";
			link.l1 = "네 필멸의 육신도 아직 피를 흘릴 수 있겠지!";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "네 힘이 점점 사라지는구나, 위대한 쿠쿨칸... 아무리 강해도 네 육신은 결국 필멸일 뿐이야!";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "이 정도면 충분히 즐겼다고 생각하오. 그대는 진정한 검술의 달인이자 훌륭한 전사요. 감히 말하건대, 그 시대 최고의 무사라 할 수 있겠지. 하지만 이번 싸움에서는 패배했소. "+pchar.name+"...";
				link.l1 = "우리는 그냥...";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "이제 그만해라, 사랑하는 동생아. 쿠쿨칸이 자신의 유물을 손에 넣은 지금, 너는 그 힘을 감당할 수 없어! 내가 이렇게 오래 너를 살려둔 건 네가 진정 무엇을 이룰 수 있는지 보기 위해서였을 뿐이다.";
			link.l1 = "젠장... 방금 그 일격... 그런데 어떤 유물 말하는 거야? 가면? 그건 내가 가지고 있어!";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "가엾어라, 불쌍한 선장 "+GetFullName(pchar)+"... 여기까지 오다니, 온갖 위험을 견디고, 가장 강한 적들까지 쓰러뜨렸으면서 결국 패배하고 마는구나!.. 네가 '산타 키테리아'의 난파선 근처, 크소체아템에서 금속 상자 안에서 찾은 비취 가면은 가짜다! 그저 타이살의 보물창고에 있던 고대 가면일 뿐이다. 그것은 쿠쿨칸의 가면이 아니다!\n내가 직접 이곳에서, 실패한 원정 이후 가져간 것이다. 고대 의식에 의해 지켜지고 있지. 이 가면 때문에 폭풍이 산타 키테리아를 크소체아템으로 날려 보낸 것이다. 그리고 또 다른 목적도 있었다. 내 진짜 유물을 찾으러 오는 자들을 속이기 위한 미끼였지.";
			link.l1 = "하지만... 그렇다면 진짜 가면은 어디 있었던 거지?! 나는 크소체아템 전체를 다 뒤졌는데!..";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "아직 안 했군, "+pchar.name+". 내 유물은 'Santa Quiteria'의 반대편, 엄중히 경비되는 성소에 있었지. 그곳으로 가는 길은 지하 동굴을 지나야 하네. 찾기도 복잡하고, 필멸자의 둔한 눈에는 쉽게 보이지도 않지. 저기 있다! 잘 봐두게, 마지막으로 한 번 더...\n";
			link.l1 = "그럴 리가 없어!";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "너는 많은 전투에서 살아남아 승리했지, 형제여. 하지만 이번 전투에서는 패배했어, "+pchar.name+"...";
			link.l1 = "그래서 이제 어쩔 건데?";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "나는 곧장 10세기로, 7세기 전으로 갈 것이다.\n이 정도면 마야 문명이 백인 종족을 압도하는 군사적, 과학적 우위를 확고히 다질 수 있을 것이다.";
			link.l1 = "그럼 우리 세계는 어떻게 되는 거지? 사라지는 건가?";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "아니. 변할 것이다. 어쩌면 그곳에 네 자리가 있을지도 모르지만, 이 세계에서 일어난 일들은 아무것도 기억하지 못할 거다. 여기서 태어난 이들 중 몇몇은 그곳에서 결코 태어나지 않을 것이고, 그 반대도 마찬가지다. 죽은 자는 다시 살아나고, 살아 있는 자는 죽을 것이다. 어떻게든 모두가 다시 태어나게 된다. 수움 쿠이퀘, 각자 자기 몫이 있는 법이지. "+pchar.name+".  
두려워하지 마라, 어린 동생아. 무슨 일이 일어났는지 너는 결코 알지 못할 것이고, 자연스럽게 새로운 현실을 받아들이게 될 것이다. 오직 나, 쿠쿨칸만이 이 모든 기억을 간직하리라... 하지만 이제 그만! 카넥이 이미 의식을 위한 모든 준비를 마쳤다.  
나를 따라오너라, "+GetFullName(pchar)+", 그리고 그토록 지키고 싶어 했던 이 현실의 마지막 순간을 목격하게 될 것이오.";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "시간의 문이 열렸다! 기뻐하라, 나의 자식들아, 너희는 위대함에 아주 가까이 서 있도다! 우리는 새로운 세상을 만들 것이다, 창백한 침입자들이 설 자리가 없는 세상을!\n작별을 고하노라, "+pchar.name+", 그리고 어떤 운명이든 받아들일 준비를 하시오. 각자에게 그의 몫을!";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "이 전투는 아직 끝나지 않았다, 인간아. 네가 지쳐 있는 게 분명하고, 내 지원군이 곧 도착한다! 내 유물을 넘겨라. 그렇지 않으면 네 시체에서 직접 가져가겠다 – 내겐 아무런 차이도 없으니...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "우라칸! 당장 이 자를 죽이라고 명한다!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "우라칸! 내 말 못 들었나? 다시 말한다: 너와 네 전사들에게 이 자를 잡아 죽이라고 명령한다!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "우라칸! 이게 뭐야? 카넥! 네 그 빌어먹을 아들놈한테 내 명령 다시 전해!!!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "너는 네 민족을 배신하는구나, 우라칸! 이렇게 중대한 변화 앞에서 겁을 먹다니! 전사들이여, 내 명령을 듣거라. 내 형제라 칭하는 이 자뿐만 아니라, 배신자 우라칸도 사로잡아 처형하라!";
			link.l1 = "전사들이여, 카빌과 우라칸의 이름으로 명하노니, 목숨이 아깝거든 그 자리에 멈춰라! 너희 중 누구도 카빌과 싸워 살아남지 못할 것이다! 누가 이 땅에서 가장 강한지, 신들 스스로가 결정하게 하라!";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "오늘은 점점 더 흥미로워지는군. 이런 결과가 나올 줄은 몰랐겠지, 형? 신들 스스로 누가 진정으로 강한지 결정해야 할 거야. 그리고 모두가 마땅한 대가를 받게 될 거다, 미셸. 수움 쿠이쿠에! 각자 자기 몫을 받는 거지...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
