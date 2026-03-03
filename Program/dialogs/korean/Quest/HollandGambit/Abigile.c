// Абигайль Шнеур
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "안녕하십니까, 나리. 우리 집에 무슨 일로 오셨습니까?";
					link.l1 = "안녕하세요, 아비가일. 내 이름은 "+GetFullName(pchar)+". 나는 공화국과 네덜란드 서인도 회사의 이익을 위해 일하는 선장이오.";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "맙소사, 아버지의 돈을 찾았나요? 정말인가요? 아, 정말 기뻐요! 어서 아버지께 가세요, 당신과 이야기하고 싶어 하세요. 어서 가서 뵈세요!";
					link.l1 = "가고 있습니다, 부인.";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "우리를 완전히 절망에서 구해주셨습니다, 선장님! 정말 감사드립니다! 이제 슈네우르 가문의 명예를 되찾을 수 있겠군요!";
					link.l1 = "신사로서 당연히 해야 할 일을 했을 뿐이오, 부인. 이제 그대가 내 후원자와 혼인하는 데 아무런 걸림돌도 없기를 바라오.";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "무슨 일 있으십니까, 선장님?";
				link.l1 = "지금은 아니오, 부인.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "만세, 거룩한 여왕이시여, 우리의 생명, 우리의 달콤함, 우리의 희망이시여. 우리는 당신께 부르짖나이다, 가련한 이브의 추방된 자식들. 우리는 당신께 한숨을 올리나이다, 이 눈물의 골짜기에서 슬퍼하며 울며... 아, 나리, 깜짝 놀랐습니다! 무슨 일로 여기 오셨습니까?";
					link.l1 = "실례합니다, 아비가일 맞으시죠? 리처드 플리트우드가 저를 보냈습니다...";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "무엇을 원하십니까, 선장님?";
				link.l1 = "지금은 안 됩니다, 부인.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "여기서 무슨 일이야? 이 소음은 뭐지? 아버지, 이 이상한 남자는 누구예요?";
					link.l1 = "안녕하십니까, 마담. 아비가일 슈뇌르, 맞으시죠? 이렇게 뵙게 되어 기쁩니다. 무례를 용서해 주십시오만, 이 급한 편지가 당신 앞으로 와 있습니다... 음, 누가 보냈는지 말씀드리고 싶으나, 당신의 아버님께서 저를 집 안에 들이지도 않으시고, 이 편지를 전하는 것조차 허락하지 않으셨습니다.";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "아, 여기 있었군, 샤를. 어디든 당신을 따라갈 준비가 되어 있어!";
					link.l1 = "그럼 가자.";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "우리 벌써 세인트 존에 도착한 거야, 샤를? 곧 리처드를 볼 수 있을까?";
					link.l1 = "네, 부인, 우리는 세인트 존스에 있습니다. 안타깝게도 리처드는 지금 도시에 없습니다; 이틀 전에 바베이도스 근처를 순찰하라는 명령을 받았습니다. 걱정 마십시오, 일주일 안에 돌아올 것입니다.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "샤를! 이렇게 다시 보게 되어 정말 기뻐! 리처드 소식은 있나?";
					link.l1 = "안타깝게도, 친애하는 마담. 리처드는 비밀스럽고 중요한 임무 때문에 브리지타운에 잠시 머물러야 했소; 네덜란드와 관련된 일이지요. 리처드가 무슨 일을 하는지 이미 들으셨겠지요?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "샤를! 너구나! 드디어 돌아왔구나!";
					link.l1 = "안녕하십니까, 부인. 다시 뵙게 되어 기쁩니다.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "아, 드디어 집에 돌아왔구나! 아버지를 다시 뵙게 되어 정말 기뻐! 샤를, 나를 위해 해준 모든 일에 감사해!";
					link.l1 = "부인, 그런 말씀은 마시지요. 곤경에 처한 숙녀를 위해 신사로서 마땅히 할 일을 했을 뿐입니다.";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "아버지, 혹시 기억나는 게 있으면 꼭 말씀해 주세요! 샤를은... 믿을 수 있는 사람이에요. 감히 말씀드리건대, 우리를 도울 수 있는 유일한 사람이에요!";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "밤낮으로 당신을 위해 기도하겠어요! 말해 줘요... 꼭 그렇게 하겠다고 말해 줘요! 그 섬을 반드시 찾겠다고!";
					link.l1 = "할 수 있는 만큼 해보겠습니다, 마님.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "아, 샤를! 돌아왔구나! 어서 말해 보게, 섬을 찾았나? 더는 기다릴 수가 없네!";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "그래, 아비. 섬도 찾았고 네 아버지의 돈도 찾았어. 이제 그걸 네게 돌려주러 왔다.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "유감입니다, 부인. 켈러 선장도, 당신의 섬도 찾지 못했습니다. 할 수 있는 건 다 했지만...";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "아, 찰스, 자네였군! 무슨 일 있나? 커피라도 한 잔 줄까?";
				link.l1 = "아니오, 아무것도 아닙니다. 부디 신경 쓰지 마십시오.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "안녕하시오, 나리. 무슨 일이오?";
			link.l1 = "아무것도 아닙니다, 부인. 실례를 범했군요. 안녕히 계십시오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "영광입니다, 선장님 "+GetFullName(pchar)+". 마을의 다른 숙녀들에게서 당신에 대한 온갖 이야기를 들었어요. 해적 유령선을 생포해서 윌렘스타드에 전리품으로 끌고 온 사람이 바로 당신이라지요. 말씀해 주세요, 선장님... 그 배가 정말... 리처드 플리트우드의 지휘 아래 있었던 게 사실인가요?";
			link.l1 = "들으신 모든 것이 사실입니다, 마담. 저 역시 진실을 알게 되어 누구 못지않게 충격을 받았습니다. 정말 스캔들이지요! 영국 연방의 해군 장교가 평범한 해적처럼 자기 나라 상인들을 약탈하다니! 그 악당은 네덜란드 서인도 회사의 지원을 받는 변절자 '유령선'인 척하며 자신의 비열한 짓을 숨기려 했습니다. 이 위장을 이용해 회사에 죄를 뒤집어씌우고 네덜란드 선박까지 공격했지요.";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "머리가 어지럽군요... 이런 끔찍한 이야기를 듣기 힘듭니다, 선장님. 저는 리처드 플리트우드를 직접 알았는데, 그가 그런 일을 할 거라고는 전혀 생각하지 못했어요...";
			link.l1 = "마담, 저는 후원자인 루카스 로덴부르크에게서 당신이 헤시피에서 퀴라소로 항해했다는 소식을 들었습니다. 이제 모든 것이 분명해졌군요. 플리트우드가 당신의 배를 침몰시키고, 그 후에 당신과 아버지를 그 외딴 섬에 표류한 상태에서 '구해낸' 셈이었군요. 저도 해적의 일지를 직접 읽어봤습니다; 그는 모든 세부 사항을 자신의 항해일지에 기록해 두었더군요.";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "악몽이 따로 없군요... 결국 아버지 말씀이 옳았던 것 같아요. 아버지는 계속 리처드가 우리 집안의 모든 불행 뒤에 있는 해적이라고 하셨죠. 진실이 드러나서 기뻐해야 할 텐데... 아, 죄송합니다, 선장님. 제 가엾은 머리로는 감당하기 힘든 일이라서요... 저 같은 평범한 여자에게 선장님처럼 중요한 분이 대체 무슨 볼일이 있으신가요?\n";
			link.l1 = "아비게일, 나는 아주 복잡하고 민감한 일 때문에 여기 왔소. 내 말 좀 들어주겠소?";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "물론이지, 나리. 잘 듣고 있네.";
			link.l1 = "내가 이미 말했듯이, 나는 컴퍼니를 섬기고 있소. 루카스 로덴부르크는 내 군사 지휘관일 뿐만 아니라 좋은 친구이기도 하오. 그가 당신께 전할 메시지가 있어 나를 보냈소. 당신이 그의 청혼을 받아들인다면, 그것이 그에게 가장 큰 기쁨이 될 것이오. 나는 내 후원자를 대신해 당신께 청혼하러 왔소. 그는 당신의 행복을 위해 세상 무엇이든 할 준비가 되어 있소.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "오, 선장님! 이제야 로덴부르크 나리가 왜 직접 하려 하지 않았는지 알겠군요... 우리 아버지는 무척 기뻐하실 테지만, 나는...";
			link.l1 = "마담, 무언가 걱정이 있으신 것 같군요. 로덴부르크 나리의 진심을 의심하십니까? 제가 다시 생각해보실 수 있도록 도와드릴까요?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "아니에요, 선장님, 저는 로덴부르흐 나리의 진심을 조금도 의심하지 않아요. 루카스가 저와 아버지에게 베푼 은혜가 얼마나 큰데, 그분이 아니었다면 저희가 어떻게 됐을지 상상도 못 하겠어요. 하지만 제 처지도 좀 이해해 주세요!\n저희 집안이 로스차일드 가문은 아니지만, 결코 가난하게 살아온 적은 없어요. 슈네우르 가문은 유럽의 은행가들 사이에서 재력으로 유명했죠... 그런데 이 끔찍한 해적 때문에 모든 게 망가졌어요! 더는 사람들이 우리 등 뒤에서 수군대는 험담을 참을 수가 없어요. 이 마을의 수다스러운 주부며 하녀들까지 모두 제가 로덴부르흐 나리의 돈만 노린다고 생각한다니까요. '유대 여자답다'고들 하죠. 정말 잔인한 인간들이에요! 아버지만 그 섬의 위치를 기억해주셨다면! 그분이 우리 가족의 남은 재산을 그 섬에 숨겨놨거든요, 제 언니들과 오빠를 죽인 그 사악한 해적들 손에서 지키려고요!\n하지만 불쌍한 우리 아버지는 뱃사람이 아니라서, 그 섬과 돈이 어디 있는지 도저히 기억을 못 하세요! 제발 아버지와 얘기해 주세요, 선장님! 혹시 선장님의 노련한 감각에 도움이 될 만한 걸 떠올리실지도 몰라요. 꼭 그 섬과 우리 재산을 찾아 주세요! 그러면 저 같은 불쌍한 처녀가 수치와 오명에서 벗어날 수 있을 거예요!";
			link.l1 = "좋아, 아비게일. 네 아버지와 이야기해 보겠다. 믿으렴, 아가씨, 내가 할 수 있는 건 다 해보마.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "감사합니다, 나리. 밤낮으로 당신을 위해 기도하겠습니다. 우리 조상의 신께서 당신과 함께하시길!";
			link.l1 = "잘 있어, 아비게일. 반드시 좋은 소식을 가지고 돌아올게, 맹세해.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "오, 그래요! 로덴부르흐 나리는 명예롭고 친절한 분이오. 나는 주저 없이 그분께 승낙하겠소, 그리고 그분을 내 남편이라 부를 수 있다면 기쁘겠소.";
			link.l1 = "그럼 내 임무는 끝난 셈이오. 이제 로덴부르흐 나리께 가서 이 좋은 소식을 전해야 하오. 진심으로 행복을 기원하오, 부인.";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "리처드가 보냈다고?! 성모 마리아여, 감사합니다! 아, 나리! 불쌍한 리처드가 다쳐서 거의 죽을 뻔했다는 소문을 들었소. 사실이오? 말해 주시오, 그가 살아 있소?! 무사하오?!";
			link.l1 = "리처드는 살아 있고... 대체로 건강해. 나쁜 소식부터 말하자면, 좀 지쳐 있고 일시적으로 앞을 못 보게 됐지만, 회복 중이야. 이제 좋은 소식이야: 리처드는 너와 함께 영국으로 떠나 결혼하길 원한대. 카리브에서의 그의 시간은 끝났고, 네 대답을 기다리고 있어.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "아, 나의 사랑스러운 전령이여, 리처드에게 전해 주시오. 우리의 행복을 위해서라면 그가 원하는 어디든 함께 갈 준비가 되어 있다고. 하지만 우리의 도피가 불쌍한 아버지를 죽게 만들까 두렵소... 나리, 저는 절망스럽고 무엇을 해야 할지 모르겠습니다. 리처드가 저주받은 그 섬과 우리 집안의 금이 든 상자를 찾을 수 있다면 좋겠어요... 어쩌면 제가 없는 동안 그것이 아버지께 위로가 될지도 모르니까요.";
			link.l1 = "알겠소... 내 임무는 자네를 앤티과까지 데려다 주는 것이었는데, 이 일로 사정이 좀 복잡해졌군. 내가 섬과 상자를 찾아서 자네에게 가져다주면, 그때는 나와 함께 세인트 존스와 리처드에게 갈 생각이오?";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "아, 네 나리, 우리 가족 기도에 꼭 당신을 기억하겠습니다! 첫 아들이 태어나면 당신의 이름을 따서 짓겠어요! 정말 감사합니다, 선장님! 당신을 위해 기도하겠습니다! 가십시오, 그리스도와 성모 마리아께서 함께하시길!";
			link.l1 = "너무 오래 기다리게 하지 않겠소, 부인. 곧 돌아오겠소.";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "오... 그 사람에게서 편지를 가져왔나요? 아, 아버지, 손님에게 너무 심하게 굴지 마세요! 괜한 망상으로 저를 곤란하게 하시잖아요! 나리, 이쪽으로 오십시오, 드릴 말씀이 있습니다.";
			link.l1 = "고맙소, 아가씨. 이 집에서 제대로 말하는 사람을 보니 반갑군.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "우리 아버지를 용서해 주십시오, 나리. 정말로 선하고 인자한 분이지만, 우리의... 불운이 그분을 망가뜨렸습니다.";
			link.l1 = "괜찮습니다, 아씨, 이해합니다. 제 소개를 하자면, 저는 찰리... 크니펠입니다. 리처드 플리트우드의 명령을 받고 왔습니다. 그분이 저더러 당신을 데려오라고 했습니다. 여기요, 이 편지를 읽어보십시오.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "오, 리처드...(읽으며). 오, 맙소사! 그가 결심했어... 아버지께서 잃으신 돈을 모두 돌려주기로! 이런 관대함이란! 사랑스럽고 다정한 리처드! 나리, 당신은 마치 가브리엘처럼 좋은 소식을 전해주시는군요! 리처드는 어디 있지? 쿠라사오에 있나?";
			link.l1 = "아니요, 아가씨. 암살 시도가 있었고 그는 중상을 입었습니다. 지금은 앤티과에 있습니다... 편지를 다 읽지 않으셨군요.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "성모 마리아님, 원죄 없이 잉태되신 분이시여, 저희를 위하여 빌어주소서! \n말해 주시오, 그는 무사합니까? 상처가 심합니까?";
			link.l1 = "그렇게 걱정하지 마시오, 아가씨! 리처드는 그렇게 아무 놈에게나 죽임을 당할 사람이 아니오. 지금은 쉬면서 회복 중이오. 나에게 당신을 그에게 데려오라고 했소. 그러면 두 분이 함께 런던으로 항해할 거요... 부디, 편지를 마저 쓰시오, 아가씨, 너무 앞서가고 있소.";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "아, 네... 미안하오(책을 읽으며). 크니펠 나리, 나는 당신과 함께 항해할 준비가 되었소. 짐을 싸고 아버지와 이야기할 하루가 필요하오. 내일 다시 오면 함께 가겠소.";
			link.l1 = "좋소, 아가씨. 내일 여기 있을게. 걱정 마시오, 내 선원들과 내가 항해 중 어떤 위험에서도 당신을 지켜줄 테니.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "아, 참 안타깝군. 하지만 예전에도 기다렸으니, 이번에도 일주일쯤 더 기다릴 수 있겠지...";
			link.l1 = "잘 말했소, 아가씨. 기다림이 덜 지루하도록 내 친구의 집으로 자리를 옮기는 게 어떻겠소? 이 딱딱한 선실보다 훨씬 나을 거요. 부드러운 침대와 훌륭한 음식이 준비될 것이오.";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "정말 친절하군, Charlie. 고마워. 땅을 밟을 수 있다니 참 좋겠어... 파도에 이리저리 흔들리다 보니 속이 꽤 메스꺼워.";
			link.l1 = "따라오시지요, 아가씨.";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "만나서 반갑소, John. 친절하게 환대해 주셔서 감사합니다, 여러분!";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "오, 찰리, 나는 리처드를 몇 번밖에 본 적 없고, 그가 무슨 일을 하는지 별로 말해준 적도 없어.";
			link.l1 = "그가 사랑하는 여인에게 그런 큰 비밀을 숨길 줄은 정말 몰랐소... 아가씨, 리처드는 평범한 선장이 아니오. 그는 영국 추밀원의 특수 요원이기도 하오. 직접 호국경께서 명령하신 민감한 임무를 수행하는 아주 중요한 인물이오. 지금 그의 임무는 카리브 해에서 네덜란드 서인도 회사의 무역력을 파괴하는 것이오.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "나리, 무슨 말씀을 하시는 겁니까?";
			link.l1 = "네, 아가씨. 당신이 사랑하는 리처드, 내 친구는 아주 중요한 사람이오. 나는 항상 그의 친구인 것이 자랑스러웠지만, 요즘 그는 나에게조차 매우 비밀스러워졌소. 분명히 무슨 비밀 임무를 수행 중인 것이 분명하오. 그 임무 때문에 당신을 만날 수 없다는 것이 정말 유감이오.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "찰리, 너 때문에 무서워진다. 그 사람 정말 괜찮은 거 맞아?";
			link.l1 = "그건 확신하오. 다만... 지금 그분이 자네를 대하는 방식은 마음에 들지 않소. 그분 임무가 얼마나 중요한지, 그리고 자네를 위해서라도 의무를 저버릴 수 없다는 것도 이해하오.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "오, 내 사랑하는 찰리... 필요하다면 리처드를 예수 재림 때까지라도 기다릴 거야. 혹시 선술집 위층에 머물 수 있을까... 존의 호의를 이렇게 오래 계속 누릴 수는 없으니까.";
			link.l1 = "헛소리 그만하시지요, 아가씨! 당신이 계셔서 우리가 영광이오. 내가 내 소중한 친구 리처드 플리트우드의 약혼녀를 집에서 내쫓는다면 내 이름이 찰리 크니펠이 아니지!";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "찰리... 네가 나를 생각해주는 그 마음에 정말 감동했어. 나는 그냥 평범한 여자일 뿐이고, 게다가 유대인인데...";
			link.l1 = "아가씨! 그런 무모한 말은 안 돼요, 당신은 훌륭한 기독교 아가씨잖아요! 그리고 선술집 같은 데는 생각도 하지 마세요! 내가 리처드를 위해 당신을 제대로 돌보지 못한다면 평생 용서하지 못할 거예요!";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "고맙네, Charlie. 자네가 이렇게... 좋은 사람이라니 기쁘군.";
			link.l1 = "제 의무일 뿐입니다, 아가씨. 이제 미안하지만, 저는 가봐야겠군요. 이제 마을을 자유롭게 돌아다니셔도 됩니다. 이 집에만 갇혀 있으니 꽤 외로우셨겠지요, 맞습니까?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "음... 존은 정말 흥미로운 사람이야. 화약이나 혼합물, 그리고 온갖... 질병에 대해 몇 시간이고 떠들 수 있지. 게다가 예의 바르고 친절한 사람이기도 해. 그리고 나는 정기적으로 교회에 가는데, 그곳 신부님도 꽤 친절하시지... 하지만, 물론, 리처드가 정말 그리워.";
			link.l1 = "곧 돌아올 거라고 생각해. 혹시 뭐 필요하면 찰리 크니펠이 네 시중을 들 테니.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "리처드에 대한 소문을 들었어... 사라졌다고 하던데. 혹시 그 일에 대해 아는 거 있어, 찰리?";
			link.l1 = "나도 그래, 아비게일. 미안해... 리처드 플리트우드는 영국으로 떠났고 다시 돌아오지 않을 거야. 승진이든 전출이든, 뭐 그런 거지... 아무튼, 네게 그런 짓을 한 사람이라면 더 이상 알고 싶지도 않아.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "아, 이렇게 끝날 줄 알았지....(흑흑) 왜 아버지 말씀을 듣지 않았을까! 적어도 루카스 로덴부르크와 결혼했다면 아버지는 기뻐하셨을 텐데.";
			link.l1 = "다시 한 번 용서해 주시오, 아가씨...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "무슨 소리야, 찰리? 너는 전혀 잘못한 게 없어. 나한테 친절하게만 해줬잖아!";
			link.l1 = "더 나쁜 소식을 전하게 되었군. 나는 막 퀴라소에서 돌아왔네; 루카스 로덴부르크가 공화국에 대한 선동과 반역죄로 체포됐어. 그는 재판을 받기 위해 쇠사슬에 묶여 암스테르담으로 송환되고 있지. 그자는 회사의 이사인 피터 스타이브센트를 살해하려 했고, 그뿐 아니라 빌렘스타트의 총독을 전복하려 시도했으며, 최소 한 명 이상의 살인 혐의까지 받고 있어. 그러니 스타트홀더가 가벼운 처벌로 끝낼 것 같진 않군.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "오, 맙소사! 이게 무슨 악몽이야! 나 기절할 것 같아! 샤를, 정말이야? 아니, 제발 아니라고 말해 줘!";
			link.l1 = "미안하오, 아가씨, 더 나쁜 소식이 있소. 로덴부르크의 행적을 조사하는 과정에서, 당신의 플루이트를 침몰시킨 해적이 루카스 로덴부르크의 명령을 받고 움직였다는 사실이 드러났소. 그는 영국 선박을 상대로 사적인 전쟁을 벌이고 있었소. 정말 미안하오, 아비게일. 이 카리브 해에서 당신이 마주한 모든 남자들은 거짓말쟁이, 도둑, 살인자들이었소.";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "오... 난 망했어. 샤를... 제발... 나를 윌렘스타트 집으로 데려가 줘. 아빠가 필요해...";
			link.l1 = "물론이지, 아가씨. 유감스럽게도 여기 세인트 존스에는 당신을 위한 게 아무것도 없소. 가서 짐을 싸고, 존에게 작별 인사를 하시오. 우리는 곧바로 출항할 것이오.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "아니, Charlie, 내가 오히려 고마워해야지. 너랑 John이 아니었으면 내게 무슨 일이 닥쳤을지 나도 모르겠어. 군도에서 내가 만난 사람들 중에 너희 둘만이 유일하게 정직한 사내들이야.";
			link.l1 = "흠... 아비게일, 너 때문에 얼굴이 빨개지잖아. 도와줄 수 있어서 기뻤어. 그리고 이 모든 소동에 정말 미안해.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "있잖아, Charlie, 우리가 퀴라소로 항해하는 동안 많은 생각을 했어. 이제 모든 게 분명해졌지 - 리처드 플리트우드, 마인헤르 로덴부르크, 이 모든 게 결국 끝난 끔찍한 악몽 같아. 난 다시 아버지와 함께 있고, 이제 평범한 삶으로 돌아갈 수 있어\n하지만 쉽진 않을 거야 - 우리에겐 돈이 하나도 없으니까. 그래도 잘 헤쳐나갈 거야, 모든 게 괜찮아질 거야. 성모님께서 우리를 돌봐주실 거야, 그분은 자녀들을 잊지 않으시지, 심지어 그분의 아들을 부정하는 내 고집 센 늙은 아버지까지도.";
			link.l1 = "아비게일 양, 내가 도와드리겠소.";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "우릴 도와준다고? 그런데 어떻게, Charlie?";
			link.l1 = "리처드가 네 조난과 구조 이야기를 내게 해줬어. 그리고 네 아버지가 자기 소지품을 미지의 섬에 숨겼다는 것도 알고 있지. 내가 그걸 찾아서 네 돈을 되찾아올 거야.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "오, 찰리... 그 불운한 섬이 어디 있는지 나도 아버지도 말해줄 수 없어... 우리는 뱃사람이 아니거든. 게다가 습격당할 때 목숨이 위태로워서 너무 무서웠어; 피와 죽음의 냄새 말고는 아무것도 기억나지 않아.";
			link.l1 = "아비게일, 기억해 보려고 해봐. 제발, 아주 작은 것이라도 어떤 정보든 내게 도움이 될 수 있어. 습격 전에 무슨 일이 있었니? 이 섬은 어떻게 생겼지?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "섬... 섬처럼 보였던가? 만, 정글. 특별히 눈에 띄는 건 없었어. 아, 생각났다! 이게 도움이 될지도 모르지. 해적이 습격하기 얼마 전, 우리는 한 플라이트선을 만나 그 선장의 배를 불러 세웠어. 그 선장은 우리 배에 초대되어 우리 선장과 저녁을 먹었지. 우리도 그 자리에 있었어. 아마 그가 이 섬에 대해 뭔가 알고 있을지도 몰라.";
			link.l1 = "이거 대단한데! 그 플루트와 선장의 이름이 뭐였지?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "기억이 안 나, Charlie. 정말로...";
			link.l1 = "기억해 봐, 아비!";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "우리는 당신을 기다릴 거요.\n도와줘, 찰리 크니펠. 너만이 우리의 유일한 희망이야... 내가 널 위해 기도할게!\n신의 가호가 있기를!";
			link.l1 = "가는 중이야. 잘 있어, 아비. 잘 있어, 솔로몬.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "아이고, 이런... 참 안타깝군. 우리도 기대했었는데... 그래도 아무도 나서지 않을 때 도와주려고 애써줘서 고맙다, Charlie. 결국 이게 신께서 내게 정해주신 운명인 것 같구나.";
			link.l1 = "잘 가요, 아비게일. 무사하시길 바랍니다.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "정말... 정말인가요? 우리 잃어버린 돈을 정말로 되찾아오셨나요? 아, 찰리!";
			link.l1 = "그래, 사실이야. 내가 가지고 있어. 자, 가져가. 전부 네 거야.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "어떻게 감사드려야 할지 모르겠소?! 어떻게 해야 하오?!";
			link.l1 = "고맙다는 말은 필요 없어, 아비. 너에게 이 정도는 해줄 수 있지. 이제 로덴부르크든, 플리트우드든, 다른 수상한 남자들이 널 이용하려 드는 일 없이 새로운 삶을 시작할 수 있을 거야. 네 아버지도 이 돈을 불릴 방법을 분명히 찾으실 거야... 유전인 것 같네.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "찰리, 그렇게 건방지게 굴지 마! 너는 나를 위해, 그리고 불쌍한 우리 아버지를 위해 정말 많은 걸 해줬어. 이제는 네가 내 인생에 있는 게 너무 익숙해져 버렸어. 나는 매일 너를 위해, 그리고 네 선원들을 위해 성모님께 지치지 않고 기도하고 있어. 앞으로도 계속 기도할 거야! 너는 우리 가족의 수호천사야. 믿기 힘들겠지만, 주님께서 너를 우리 가족에게 보내주신 거야\n떠나기 전에 꼭 알아줬으면 해. 우리 집의 문은 언제든지 너를 위해 열려 있을 거야. 그리고... 제발, 내 사랑하는 찰리, 한 번만 입 맞추게 해줘...";
			link.l1 = "음... 그래, 알겠어, 아비... 네가 그렇게 말한다면.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "신의 가호가 있기를, 샤를. 우리에게는 아무것도 변한 게 없어... 나는 여전히 교회 밖에서 남은 음식을 구걸하고 있네.";
			link.l1 = "기운 내시오, 아가씨. 신의 가호가 함께하길.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "샤를, 너구나! 이렇게 다시 보게 되어 정말 기뻐! 어서 앉아! 내가 커피를 끓일게!";
			link.l1 = "나도 너를 다시 보게 되어 기쁘다, 아비. 그리고 네가 잘 지내고 있다니 다행이구나.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "아, 그래서 그런 거였나?! 내가 널 손님으로 맞이했더니 날 털 생각이었군?! 경비병들아!!!";
			link.l1 = "입 다물어, 멍청한 계집애야.";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
