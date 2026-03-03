// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
void ProcessDialogEvent()
{
	ref sld, NPChar;
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
			dialog.text = "명백한 버그다. 개발자들에게 알려라.";
			link.l1 = "그래, 그렇게 할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "오, 안녕하세요 나리! 토르투가에 오신 걸 환영합니다! "+GetSexPhrase("나리 같은","나리 같은")+" 고귀한 선장은 여기서 드문 손님이지요...";
			link.l1 = "안녕하십니까, 마드모아젤. 따뜻하게 맞아주셔서 감사합니다. 하지만 어찌 된 일입니까? 저는 이렇게 중요한 항구라면 저보다 훨씬 고귀한 신사 해적들이 항상 관심을 가지는 곳인 줄 알았는데요.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "아, 나리... 당신은 분명 신참이군, 맞지? 곧 직접 알게 될 거야. 총독 저택 무도회에서 춤출 만한 괜찮은 남자를 찾는 게 얼마나 힘든지 모를 거야. 혹시 나와 함께 가줄 생각은 없나...?";
			link.l1 = "이렇게 아름다운 여성분께 어떻게 도와드릴 수 있을까요?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "어머나, 이런 용감함이라니! (킥킥) 오늘 밤 여섯 시에 우리를 찾아올 수 있겠어요? 우리 총독 부인께서 궁전 하인 숙소에서 비공식 파티를 자주 여시거든요. 그런 자리에서 흥미로운 손님을 만나는 건 정말 드문 기회랍니다. 우리를 찾아올 건가요? 꼭 오세요, 정말 기뻐할 거예요.";
			link.l1 = "영광이오, 아가씨. 오늘 밤에 찾아가겠소.";
			link.l1.go = "girl_3";
			link.l2 = "용서하십시오, 아가씨, 하지만 급한 일이 있어 처리해야 합니다. 다음에 뵙지요?";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "안됐군. 나랑 내 여자친구들... 같이 놀아줄 다른 사람을 찾아야겠네. 잘 가.";
			link.l1 = "안녕히 가시오.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "감사합니다! 약속하지, 이 밤은 절대 잊지 못할 거요, 나리! 오 르부아!";
			link.l1 = "또 보자...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "이봐, 선원! 오늘은 무슨 행운의 바람을 타고 여기까지 온 거냐? 토르투가에서 이렇게 멋진 사내는 좀처럼 보기 힘든데.";
			link.l1 = "안녕하시오, 아가씨. 그 칭찬에 내가 다 얼굴이 붉어지겠구려. 나는 내 배의 선장이자 바쁜 사내이지만, 이 섬이라면 나 같은 방랑자가 즐길 거리가 충분히 있을 것이라 확신하오.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(킥킥) 아, 그래요 나리, 그 문제라면 우리가 도와드릴 수 있을 거예요! 토르투가는 항상 뭔가를 내놓죠. 저도 마찬가지고요... 왜냐면, 저는 좋은 바다 이야기를 들으면 거의 *무엇이든* 할 수 있을 것 같거든요. 그런 이야기 정말 좋아해요! 예전에 어떤 선장님이 외딴 섬에 버려졌다가 바다거북으로 뗏목을 만들어 탈출한 얘기를 해줬어요. 정말 용감하지 않나요! 혹시 그런 거 할 수 있으세요?";
			link.l1 = "내가 뭘 할 수 있다고?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(킥킥) 바다거북으로 뗏목을 만들 수 있을까?";
			link.l1 = "더 대단한 얘기도 있지. 한 번은 도망친 견습생 신분으로, 도끼 하나만 들고 영국 해군에서 가장 빠른 배를 빼앗았거든. 그리고 나는 숨도 열 분 동안 참을 수 있어. 보고 싶어?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "나중에 하자. 나는 우리 총독 궁전에서 하인으로 일하고 있어. 오늘 밤 여섯 시까지 그리로 와서, 정자에서 나랑 내 친구를 찾아. 그때 네 모험 이야기를 다 들려줘...";
			link.l1 = "거절할 수 없는 구경거리 초대 같군. 오늘 밤 여섯 시에 보자.";
			link.l1.go = "girl_9";
			link.l2 = "총독 관저에 몰래 들어간다고? 내 주제엔 너무 과분한 일이지. 난 사양할게, 자기야. 진짜 사내의 동무가 필요하면 선술집에서 날 찾아. 요호호!";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "푸-흥. 됐어, 너보다 더 크고 멋진 남자 금방 찾을 거야. 네 그곳은 너무 작아 보이거든. 잘 가라, 속이 시원하네.";
			link.l1 = "네가 지키는 윈드워드 해협을 지나가면 전함조차도 작아 보이겠군.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "기대하고 있어!";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "아, 거기 있었군! 선장 "+GetFullName(pchar)+"! 이렇게 고귀하고 위엄 있는 분이 찾아오신 건 정말 오랜만이라, 만나 뵙게 되어 참으로 기쁩니다!";
			link.l1 = "이렇게 귀하와 함께할 수 있어 큰 영광이자 기쁨입니다, 마담. 하지만 다른 손님들은 어떻습니까? 제가 너무 일찍 온 건가요?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "오, 그 사람들은 몸이 안 좋아서 올 수 없어요. 하지만 신경 쓰지 말고, 우리 와인 마시며 이야기해요... 아, 당신이 여기서 내가 얼마나 지루하고 외로운지 알기만 한다면! 토르투가는 쓰레기, 악당, 해적들로 가득 찬 더러운 소굴이에요! 해적들! 그런데 마침내 내 집에 걸맞은 신사분이 오셨네요! 내 남편도 당신처럼 품격과 재능을 갖춘 분들과 더 많은 거래를 했으면 좋겠어요! 하지만 아니에요, 온통 해적뿐이죠, 어디를 봐도 해적! 파리에서, 폐하의 왕실 궁정에서 새롭게 유행하는 패션에 대해 들어보셨나요? 그걸 어떻게 생각하세요?\n";
			link.l1 = "미안한데, 내 의견이 뭐에 대한 건가? 해적? 아니면 유행?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "오, 나리, 정말 저를 잘 이해해 주시는군요! 믿기지도 않아요. 제 남편은 해적질로 수백만을 벌면서 저한테는 동전 몇 푼만 쥐여줘요, 상상이나 해보세요! 해적들이라니! 저는 이 더러운 구멍 같은 곳에 드레스를 주문해야 하고, 도착할 때쯤이면 이미 6개월이나 지난 유행이에요! 제 신분에 이런 누더기를 어떻게 입겠어요? 아, 정말 파리의 최신 유행을 직접 보고 입어보고 싶어요! 제가 그런 옷을 입으면 예쁠 것 같지 않으세요?";
			link.l1 = "마담, 정말 아름다우십니다. 그런 건 파리에서 온 유행이 아니어도, 이 아름다운 섬의 모든 남자들이 이미 다 알고 있지요.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "저에게 너무 친절하시군요... 선장님, 사실 고백할 게 있습니다. 저는 큰 곤경에 처했어요. 하지만 가엾은 여자를 도와주실 거죠, 그렇죠?";
			link.l1 = "물론입니다, 마담. 원하시는 대로 하겠습니다.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "조심하세요, 선장 나리, 그러다간 제 정신이 나가버릴지도 몰라요! (요염하게 웃으며) 남편이 요즘 한 푼도 안 주는 거 있죠. 그 못된 인간이 천한 창녀들을 집에 데려오고 저한텐 신경도 안 써요!\n저 그이가 훔쳐 모은 돈을 어디에 숨겼는지 알아요, 집무실에 있는 상자에 있답니다. 이건 아내이자 여자인 제 권리로 당연히 받아야 할 돈이에요. 그 인간에게서 받아낼 수 있게 도와주면 보답할게요... 금화도, 그리고... 더 달콤한 것도.";
			link.l1 = "흥미로운 제안이군요. 좋아요, 부인, 도와드리겠습니다. 그 상자는 어디에 있고, 어떻게 열 수 있습니까?";
			link.l1.go = "wife_5";
			link.l2 = "좋소, 마님, 상자 안에 든 것을 가져다 드리겠소. 우리가 돈을 챙기고 나서 아주 유쾌한 '대화'도 나누게 될 것이오. 이런 제안을 거절할 남자가 어디 있겠소? 그 상자는 어디에 있고, 어떻게 열면 되오?";
			link.l2.go = "wife_6";
			link.l3 = "마담, 당신은 저를 유혹하려 하시는군요. 유감이지만, 제 명예가 당신의 제안을 거절하라고 요구합니다. 안타깝게 생각합니다. 당신은 더 나은 대우를 받아야 마땅하지만, 당신의 연극에는 다른 배우를 찾아야 할 것입니다.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "유감이군. 그럼 더 이상 할 말이 없소, 나리. 나가시오, 그리고 기억하시오: 이 일에 대해 내 남편에게 한마디라도 하면, 반드시 후회하게 될 거요!";
			link.l1 = "안녕히 가시오.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "너한테 이런 일이 있을 줄은 몰랐는데... 상자는... 그건 나중에 두고, 먼저 더러운 해적이 훔쳐 간 예비 열쇠부터 찾아야 해. 그놈은 지금 근처 소굴에서 돼지처럼 술을 퍼마시며 흥청거리고 있어. 서둘러서 예비 열쇠를 내게 가져오도록 해. 나는 여기서 기다리고 있겠다.";
			link.l1 = "그럼 시간 낭비할 틈이 없군!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "이 결정, 후회하지 않을 거요, 선장. 먼저, 더러운 해적이 훔쳐간 예비 열쇠를 찾아야 하오. 그 자는 지금 근처 소굴에서 술에 취해 돼지처럼 마시고 있지. 서둘러서 예비 열쇠를 내게 가져오시오. 여기서 기다리고 있겠소.";
			link.l1 = "그럼 시간 낭비할 틈 없지!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"! 이런, 이런! 내 개인 방에 이런 사내가 들어오다니! 놀랐어? 오늘 밤 여긴 네가 유일한 손님이야. (낄낄)";
			link.l1 = "놀랍군요, 부인. 하지만 전혀 상관없소. 이게 사업 때문이오, 아니면 즐거움을 위한 거요?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "참 직설적이군! 난 너 같은 사내가 마음에 들어. 선장, 너에게 사업 제안을 하지. 성공만 한다면 네 수고에 걸맞은 보상을 해주지.";
			link.l1 = "계속해.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "아... 내 남편은 돈과 보석이 가득 든 궤짝을 가지고 있어. 난 그 인간이 싫고, 내 고생에 걸맞은 더 많은 용돈을 받고 싶어.";
			link.l1 = "마담, 정말 아름다우십니다. 파리에서 온 보석이나 최신 유행 옷이 더 필요하지 않아요, 이미 이스파니올라의 모든 남자들이 다 알 수 있을 만큼 뚜렷하니까요.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "저한테 너무 친절하시군요... 선장님, 고백하자면, 저는 큰 곤경에 처해 있습니다. 곤란한 여자를 도와주실 수 있겠습니까?";
			link.l1 = "물론이지요, 마담. 명예가 그것을 요구하오. 원하시는 것은 뭐든 말씀하십시오.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "조심하세요, 선장 나리, 안 그러면 제 정신이 나가버릴지도 몰라요! (요염하게 웃으며) 남편이 요즘 한 푼도 안 줘요. 그 짐승 같은 인간은 집에 천한 창녀들을 데려오고 저한테는 신경도 안 써요!\n그 인간이 훔친 보물 중 일부가 어디 있는지 알아요, 집무실에 있는 상자에 숨겨놨어요. 이건 아내이자 여자로서 당연히 제 돈이에요. 그 인간이 제게 빚진 걸 찾는 걸 도와주면, 보상해 드릴게요... 금도 있고... 다른 달콤한 것도 있답니다.";
			link.l1 = "좋아. 내가 하지. 그 상자는 어디에 있고, 어떻게 열면 되지?";
			link.l1.go = "wife_13";
			link.l2 = "하! 그건 묻지 않아도 돼, 너 같은 여자를 위해서라면 내가 해줄 수 있지. 후회하지 않을 거야, 내 사랑. 돈도 챙기고, 우리 둘이 아주 즐거운 시간도 보낼 테니까. 그 상자는 어디에 있는데, 어떻게 여는 거지?";
			link.l2.go = "wife_14";
			link.l3 = "나는 아니오, 마님. 나는 한밤에 남의 아내를 뺏고 그 남자를 털어먹을 만큼 점잖은 신사는 아니오. 적어도 이런 식으론 말이오. 이 연극에 어울릴 다른 배우를 찾으시오.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "오... 점점 더 마음에 드는군... 먼저, 더러운 해적놈이 훔쳐간 예비 열쇠를 되찾아야 해. 그 자식은 근처 술집에서 돼지처럼 술을 퍼마시며 놀고 있지. 서둘러서 예비 열쇠를 나에게 가져와라. 내가 기다리고 있겠다.";
			link.l1 = "그럼 시간 낭비할 틈 없지!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "진정하시지요, 나리, 그럴 시간은 나중에 충분히 있을 테니. (낄낄) 먼저, 더러운 해적놈이 훔쳐간 복제 열쇠를 되찾아야 하오. 그자는 근처 소굴에서 돼지처럼 술을 퍼마시며 흥청거리고 있소. 서둘러 복제 열쇠를 가져오시오. 나는 여기서 기다리겠소. 그 정도는 할 수 있겠소?";
			link.l1 = "나를 의심하지 마라, 이미 가는 중이다.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "새침한 자식 같으니! 내 눈앞에서 꺼져! 그리고 내 남편한테 이 일 일러바칠 생각도 하지 마, 아니면 크게 후회하게 될 거야!";
			link.l1 = "잘 가, 자기야.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "선장님! 열쇠 구하셨습니까?";
			link.l1 = "그래, 가지고 있어. 상자는 어디 있지?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "오! 내 그 비열한 남편이 마침내 벌을 받게 되는 건가? 정말 대단한 분이시군요, 선장님! 당신 앞날이 아주 창창할 거란 거, 알고 계세요? 보물상자는 잊으세요. 내가 직접 처리할 테니까. 내일 보상 받으러 오세요. 절대 후회하지 않을 거예요, 선장님...\n";
			link.l1 = "좋아. 네 뜻대로 해. 내일 보기를 기대하고 있네.";
			link.l1.go = "wife_17";
			link.l2 = "아니, 나는 바쁜 사람이니 기다리며 시간 낭비하고 싶지 않아. 왜 기다려야 하지? 할 일을 말해 줘, 내가 하겠어. 이렇게 아름다운 여인이 자그마한 손을 자물쇠와 열쇠로 망치게 둘 수는 없지.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "여섯 시까지 나를 찾아오시오, 용감한 나리 기사...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "확실한가? 너한테 위험할 수도 있어. 왜 목숨을 걸려고 하지, 선장?";
			link.l1 = "좋아. 네 마음대로 해. 내일 보기를 기대할게.";
			link.l1.go = "wife_17";
			link.l2 = "나는 이미 결정을 내렸어. 정확히 뭘 해야 하지?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "사자심장이구나!... 내 남편의 집무실로 가. 거기서 상자를 찾을 수 있을 거야. 복제 열쇠를 사용해. 이런 밤중에는 위층에 아무도 없으니 천천히 해도 돼. 그 상자 안에는... 다이아몬드가 들어 있어. 아주 많아. 전부 가져와서 내게 돌아와. 나는 기다리고 있을게. 내 신뢰를 저버리지 마... 제발.";
			link.l1 = "곧 돌아올게.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "오, 선장님! 나... 당신이... 끝난 건가? 오, 그런데 이게 누구지?! 아-악!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "이런! 선장님, 저를 구해주셨군요! 당신은... 당신은 제 영웅이에요! 그건 제 남편의 깡패였어요, 당신을 죽이려고 했죠! 제발 그러지 말라고 애원했어요! 다치신 건 아니죠? 다이아몬드는 가져오셨나요?";
			link.l1 = "하. 정말이야? 네 남편은 질투가 심한 놈이군... 뭐 어때. 그런 놈은 지옥에나 가라지, 난 배짱 있으니까.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "오, 선장님! 나... 당신이... 끝난 건가?";
			link.l1 = "작은 문제가 있었지만 이제 해결됐소. 왜 이렇게 창백하시오, 마담? 괜찮으시오? 보석은 내가 가지고 있소, 그걸 보면 기분이 좀 나아지지 않겠소?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "신이시여, 감사합니다! 복수를 이뤘군요! 내 기사님! 다이아몬드는 몇 개였지?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "그대의 기사님이 모험을 마치고 전리품 자루를 가득 들고 돌아왔소. 그 중 절반은 부인께 남겨두고 가니, 파리에서 가장 좋은 옷을 사시게 될 것이오. 나는 그대와의 약속을 지켰소.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "오, 다이아몬드는 넉넉히 있었지. 하지만 넌 아무것도 못 가져. 날 죽이려고 암살자를 고용했잖아, 이 썩을 년아! 이런 짓을 다 해놓고 내가 너랑 나눌 거라 믿었어? 입 한번 뗐다간 네 남편이 네 도둑질이랑 바람피운 계획을 알게 될 거다. 그러니까 입 다물고 있어.";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "이 악당놈! 개자식! 이대로 넘어갈 줄 알지 마!";
			link.l1 = "그래, 그 얘긴 예전에 들어봤지.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "너는... 다른 놈들이랑은 달라. 원하는 건 다 가지잖아. 앞날이 밝아 보여. 바쁜 사람인 거 알지만... 잠깐만 나랑 같이 있어줄래? 아무도 우리를 방해하지 않을 거야, 약속해.";
			link.l1 = "아름다운 여인인 당신을 위해선 언제든 시간이 있지. 남편 분의 와인 한 병 따 드릴까?";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "나는 그 사람들 없이도 잘 살 수 있을 것 같아요. 여기서는 돈 쓸 데가 정말 많으니까요. 토르투가에는 잘생기고 멋진 남자들도 아주 많고요... 모든 것에 감사해요, 선장님. 참고로 말씀드리자면, 이 일에 대해선 아무 말도 하지 마세요. 제 남편이 당신을 교수대에 매달아버릴 거예요. 그 사람, 좋은 사람 아니거든요. 안녕히 계세요.";
			link.l1 = "그냥 이렇게 끝나는 건가? 정말 교훈이 되는 경험이었어. 안녕히 계시오, 부인. 이것도 조용히 넘어가시길 권하오. 나도 좋은 사람은 아니니까. 하지만 이미 알고 계시겠지, 그렇지?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "너 누구야, 여기서 뭐 하는 거지?";
			link.l1 = "뭘 꾸미는 거야? 우리 약속했잖아...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "무슨 거래요, 나리? 저는 유부녀예요, 다른 남자와는 거래하지 않아요! 지금 당장 제 방에서 나가요, 아니면 남편과 경비들을 부를 거예요!";
			link.l1 = "그냥 그렇게, 그렇지? 좋아, 그렇다면 네 착한 남편에게 내가 좀 가르쳐 주도록 하지!";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "지금 당장 나가라, 이 건방진 놈! 아니면 내 부하들이 너를 라 로슈 요새의 지하 감옥에 쳐넣을 것이다! 네 협박 따위 신경 안 쓴다! 썩 꺼져라!";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "너 누구냐? 아, 뭐 어때. 여자들은 믿지 마라, 친구. 성경에도 나오잖아... 가장 멍청한 창녀라도 그 농간으로 널 지옥 끝까지 끌고 갈 수 있다고. 앉아라, 이 친구, 한잔해!\n";
			link.l1 = "기꺼이!";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "뭘 쳐다봐? 따라 올려!!";
			link.l1 = "자, 너를 위해!.. 이봐 친구, 여기서 시간 낭비할 생각 없어. 네가 가진 그 여분 열쇠가 필요해, 무슨 말인지 알지? 그거 내놓으면 우리는 각자 갈 길 가는 거야: 넌 계속 술 마시고, 나는 계속 곤경에 처한 아가씨들을 도울 테니까.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "에이, 이봐! 내가 방금 한 말 하나도 안 들었냐! 겉보기엔 똑똑해 보여도 실제로는 아니구만... 그 창녀 밑에서 일하다니. 그녀 남편이 누군지 알아? 얼마 전에 레바쇠르 총독이 충직한 흑인 캄파초를 시켜서 현지에서 명망 높은 상인한테 '이야기 좀 하라'고 보냈지. 그 흑인이 그 불쌍한 놈을 자기 가게에서 때려 죽였어! 그 상인이 무도회인가 뭔가에서 총독 부인한테 약간의 무례를 보였다고 하더군. 그리고 그년이 바로 나한테도 자기 외모랑 남편의 두블론으로 유혹했지\n중복 열쇠가 있어. 나 프랑스에 있을 때는 괜찮은 금고털이였으니, 애들 장난이었지. 리옹 사령관 딸만 아니었어도... 절대 해적질 같은 건 안 했을 거야. 에잇! 다 집어쳐!";
			link.l1 = "이거 참 안타깝군, 하지만 이제 본론으로 들어가자. 열쇠는 어디 있지?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "듣고 있냐? 난 이제 빠질 거야, 친구! 무슨 일이 벌어질지 미리 알아챘거든! 내 배만 출항 준비 끝나면 이곳을 영영 떠날 거다. 열쇠가 필요하면 돈 내고 가져가. 욕심부리지 마라, 이제 돈 쓸 일도 얼마 안 남았을 테니까.";
			link.l1 = "있잖아, 네 말이 맞아. 나는 여자 장난감이 되고 싶지 않아. 조언 고맙고, 바다에서 몸조심해!";
			link.l1.go = "pirate_4";
			link.l2 = "값을 내라고? 너한테? 넌 한심한 도둑에다 겁쟁이야. 그 구린 곳에 그냥 남아 있었어야지, Lyons. 누가 알겠냐, 아마 그 동네 사령관이 불쌍해서 타락한 도둑을 사위로 받아줬을지도. 하지만 나는 절대 너한테 동정 안 해. 열쇠를 쉽게 줄지, 아니면 힘들게 줄지, 선택은 네가 해.";
			link.l2.go = "pirate_5";
			link.l3 = "(한숨) 얼마야?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "영리한 녀석이군, 그게 옳은 결정이야, 친구. 행운을 빌어. 언젠가 진짜로 널 사랑해줄 여자를 만나길 바란다. 가능하면 빨간 머리나 금발이면 더 좋겠지, 안 그래?";
			link.l1 = "잘 가라, 친구...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "나를 모욕하다니! 칼을 뽑아라, 이 자식아!";
			link.l1 = "팔 없이 금고를 얼마나 잘 털 수 있는지 한번 보자!";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "자네, 장사꾼 기질은 있군. 인정하지. 정말 성공할지도 모르겠어. 50두블론. 여기 테이블 위에.";
			link.l1 = "금화 쉰 닢이라고? 이깟 깡통에? 젠장할. 열쇠는 테이블 위에 놔. 지금.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "가격이 꽤 세군... 좋아. 가져가.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "값이 꽤나 비싸군... 좋아. 곧 가져오지. 여기서 기다려.";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "금화 50닢 가져왔나?";
			link.l1 = "있잖아, 그거 없이도 살 수 있을 것 같아. 열쇠 말이야. 탁자 위에 있어.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "그래. 가져가.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "아직도 받고 있어.";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "춤이나 출까?";
			link.l1 = "내가 앞장설게.";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("You have given 50 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "좋아. 머리 좀 굴리면 목숨이랑 에잇 동전 몇 개쯤은 챙겨 나갈 수 있을 거다. 열쇠 가져가고 내 조언도 들어. 공짜니까. 르바쇠르의 여자는 물고기만큼 멍청한데, 지가 영리하다고 착각하지. 믿지 마라. 바지 지퍼 잘 잠그고, 주머니도 조심해. 별로 대단한 상대는 아니지만, 조심해서 남편까지 끌어들이지만 않으면 돼. 마지막으로 한 가지 더 - 그 여자의 방에 장신구를 넣어두는 궤짝이 있는데, 따기 쉽다. 거기에 자기 몫을 넣을 거야. 내 말 들었지? 바다에서 몸조심해라, 형제여. 기억해, 여자보다 형제가 먼저다.";
			link.l1 = "행운을 빌어, 친구...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "젠장! 이런 일은 예상 못 했는데... 그 여자, 다 집어치워! 내 주인께서 저런 부류는 피하라고 하셨지. 하지만 일은 일이니까. 결국엔 널 잡고 말 거다.";
			link.l1 = "그래 그래, 이봐... 보아하니 그 여자는 우리 둘 다 속이려고 했던 것 같군, 놀랍지도 않지. 우리가 계속 싸울 이유가 뭐 있겠어? 일자리 필요해? 나한테 하나 있지. 너처럼 실력 있는 놈이 내 선원에 필요하거든. 밥, 침상, 정기적인 임금, 럼주, 그리고 약탈한 것의 공정한 몫까지. 맹세문도 써주지. 어때, 할래?";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("Iron Will", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("Skill Check Passed", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Skill Check Passed", SKILL_FORTUNE);
			dialog.text = "입담이 아주 대단하군, 명성도 자자하고. 그건 인정하지, 선장. 좋아, 나도 끼겠어. 네 배 이름이 뭐지?";
			link.l1 = "'"+pchar.ship.name+"'. 보선한테 가 봐, 침상 하나 마련해 줄 거야. 배에 탄 걸 환영한다!";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "하! 나도 이제 출세하는군. 그 계집애한테 내 대신 한 방 먹여 줘.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification("Perk check failed", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("Skill Check Failed (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Skill Check Failed (21)", SKILL_FORTUNE);
			dialog.text = "말은 곱게 하네. 하지만 진짜 프로들이 네 밑에 붙으려면 그 정도로는 어림없지. 앞으로 명심해 둬. 앞으로가 있다면 말이지.";
			link.l1 = "한번 해 봐. 빨리 해, 나 숙녀와 약속이 있거든.";
			link.l1.go = "mercen_5";
			link.l2 = "오늘은 두 번째 기회 없어. 나는 바쁜 사람이니까, 카펫 더럽히지 말자고. 너 따위가 그 하찮은 계집애 때문에 죽기엔 돈도 제대로 못 받았잖아. 아니, 돈이나 제대로 받았는지도 의문이군.";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "맞아. 아직 아무도 나한테 돈을 안 줬지... 지금 바로 해결하지. 하고 싶은 대로 해...";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
