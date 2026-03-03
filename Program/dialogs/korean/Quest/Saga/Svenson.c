// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "아, 샤를. 와줘서 고맙네. 그냥 헬렌이랑 시간을 보내줘서 고맙다고 말하고 싶었어. 그 아이도 상처를 치유할 시간이 필요했지, 자네도 즐거운 시간 보냈다고 들었네, 하하! 젠장, 나까지 질투가 날 지경이야!";
					link.l1 = "화나지 않았어? 그 통이랑... 다른 모든 일에 대해서?";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "아, 샤를. 와줘서 고맙네. 헬렌과 시간을 보내줘서 감사 인사를 하고 싶었어. 그 아이도 상처를 치유할 시간이 필요했지, 자네도 즐거운 시간을 보냈다고 들었네, 하하! 카르타헤나에서 행운을 빌겠네!";
					link.l1 = "네, 나도 어제 모든 일이 잘 풀려서 기쁩니다. 또 만납시다, 얀.";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "오, 내 친구여 "+pchar.name+"! 만나서 반갑소! 무엇을 도와드릴까요?";
					link.l1 = "그냥 어떻게 지내는지 들르러 왔어.";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "얀, 나 철목을 사고 싶어.";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "무엇을 도와드릴까요, 나리?";
					link.l1 = "도움을 청하고 싶소, 포레스트 데빌.";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "아하, 내 친구 "+pchar.name+"! 소식이 뭐지?";
					link.l1 = "나는 교수형 집행인에게서 흥미로운 것들을 많이 알아냈어.";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "그러면, "+pchar.name+", 글래디스와 이야기했나?";
					link.l1 = "그래, 내가 그랬지. 얀, 여기 좀 봐... 이 양피지 조각에 대해 뭔가 아는 게 있나?";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "아직 새로 말할 게 없어. "+pchar.name+". 하지만 우리 문제의 해결책을 찾고 있어. 나중에 다시 와.";
					link.l1 = "알겠어, 얀. 나중에 보자.";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+", 너는 나를 완전히 실망시켰다. 나는 네가 진중한 사람일 줄 알았는데, 결국 너는 그냥 어리석은 소년에 불과하구나. 그동안 도대체 어디서 뭘 하고 있었느냐, 응? 네가 어디서 뭘 했는지도 모르는 사이에 영국 놈들이 이슬라 테소로를 차지해 버렸다!\n내 모든 계획이 망가졌어! 솔직히 말해, 나는 네 존재조차 거의 잊고 있었고 앞으로도 기억하고 싶지 않다. 꺼져라!";
						link.l1 = "믿을 수가 없군!";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "여기 있었군, "+pchar.name+". 우리 처지를 좀 곱씹어 봤어. 딱히 계획이라고 할 순 없지만...";
						link.l1 = "듣고 있네, 얀.";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "일은 잘 되어가고 있소? 내가 도울 일이라도 있소?";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "나는 블랙 파스터와 이야기를 나눴어. 안타깝게도 그 대화의 결과 때문에 바로 다시 조언을 구하려고 당신에게 왔네, 정말 막막하군.";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "나는 디오스를 찾아서 즐겁게 대화를 나눴어. 그가 흥미로운 이야기를 많이 해줬지만, 아쉽게도 본론까지는 들어가지 못했지.";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "오, 얀. 너에게 할 말이 너무 많아서 밤새도록 이야기해도 모자라겠지만, 간단히 말할게.";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "나는 저스티스 섬에서 네이선리얼 호크를 데려왔어. 지금 내 배에 타고 있어.";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "나는 네이선리얼 호크를 미스키토 마을에 내려주었어. 그곳의 샤먼 스네이크 아이가 치료해 준다고 했지. 그는 네이선의 건강을 회복시켜주겠다고 약속했어.";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "지금은 딱히 드릴 말씀이 없소. 그냥 안부나 살피러 들렀소.";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "무슨 소식이오, "+pchar.name+"? 무슨 일 있나?";
					link.l1 = "아, 이보다 더 나쁠 수는 없겠구나. 내가 얼마나 고생했는데... 잭맨을 찾아냈고, 칼집도 내던졌지. 그리고 그 녀석을 완전한 바보처럼 물에 빠뜨렸어. 그의 선실 안에 있었을지도 모를 모든 것과 함께 말이야. 이제 샤크의 누명을 벗기거나 바르바종에게 죄를 뒤집어씌울 만한 아무 증거도 없어. 이젠 가망이 없는 것 같아, 얀.";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "자네의 영웅적인 활약에 대해 들었네! 대니가 간단하게 얘기해줬지. 그런데 우리 이제 친구야. 그리고 네이선도 완전히 달라졌어! 자기 '센추리온'을 보자마자 우울증이 싹 사라졌거든.\n하지만 자네에게 나쁜 소식이 있네, "+pchar.name+". 우리가 너무 많은 시간을 허비해서 샤프의 유언장에 대한 상속권은 이미 오래전에 사라졌고, 이슬라 테소로는 영국 군사 기지가 되어버렸소. 이제 내가 르바쇠르와 관련해서 도와줄 수 있는 일은 더 이상 없소.";
						link.l1 ="정말 할 말을 잃었어... 이렇게 많은 고생을 했는데 다 헛수고라니. 정말 우리가 할 수 있는 게 아무것도 없는 거야?";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "자네의 무용담은 다 들었네! 대니가 내게 전부 설명해줬지. 참고로 우리 이제 화해했어. 네이선은 자네가 알아보지도 못할 거야. 자기 '센추리온'을 보자마자, 투덜거림은 나쁜 꿈처럼 싹 잊어버리더군...\n";
						link.l1 = "네이선이 다시 건강해졌다고? 그 소식 들으니 기쁘군!";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "여기 있소, "+pchar.name+"! 이제 할 말이 있어.";
					link.l1 = "안녕, 얀. 정말 기쁘구나! 무슨 소식이 있나? 좋은 소식이길 바라네?";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "여기 있소, "+pchar.name+"! 좀 쉬었나? 이제 다시 위대한 모험을 떠날 준비가 된 거로 봐도 되겠지?";
					link.l1 = "안녕, 얀. 그래, 준비됐어.";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "무슨 소식이오, "+pchar.name+"? 어떻게 지내?";
					link.l1 = "오. 상황이 정말 끔찍해. 죽을 힘을 다해 싸웠지만 결국 졌어. 기억하겠지만, 샤프의 유언장에는 기한이 있었지. 그 시간이 다 지나버렸고, 이제 이슬라 테소로는 영국군 기지가 되어버렸어. 이젠 끝장이야, 얀.";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "안녕하시오, "+pchar.name+"! 좋은 소식이오: 평의회가 열렸고, 코스트의 형제단이 새로운 수장을 뽑았소.";
					link.l1 = "안녕하시오, 얀. 기쁘구려.";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "음, "+pchar.name+"? 뮬리건을 따라잡았나?";
					link.l1 = "내가 그랬어. 네 철목을 훔친 건 바로 그 놈이야.";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "늘 제시간에 오는군, "+pchar.name+". 네가 가져온 철목을 팔았어.";
					link.l1 = "훌륭하군. 돈은 얼마나 벌었나?";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "음, "+pchar.name+"? 몰리건을 따라잡았나?";
					link.l1 = "내가 그랬지. 네 철목을 훔친 놈이 바로 그 사람이야. 우연히 그 물건을 산 사람도 만났어. 네덜란드 군 지휘관이더군. 내가 그에게 그 물건을 팔았지.";
					link.l1.go = "saga_59";
					link.l2 = "내가 그랬어. 걔한테 화물창 보여 달라고 억지로 시키려다가... 몸싸움이 벌어졌고... 이제 몰리건은 없어. 그런데 화물창 안에는 흑단이랑 마호가니밖에 볼 게 없어.";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". 무슨 소식이 있나?";
					link.l1 = "얀, 너와 얘기하고 싶은 게 있어. 내가 헬렌의 어머니인 베아트리스의 과거를 조사하다가 네가 아주 잘 아는 사람을 우연히 알게 됐어. 내가 들은 바로는...\n";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". 일은 잘 되어 가오? 표정을 보니, 축하를 드려도 되겠소? ";
					link.l1 = "그래. 드디어 이 난장판을 정리했어. 헬렌이 이슬라 테소로의 모든 권리를 받았지. 이제 다시는 누구도 해적단의 성역을 침범하지 못할 거야!";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "Oh, my friend "+pchar.name+"! Pleased to see you! What brings you here?";
				else sTemp = "Anything else, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "아니, 얀. 지금은 아무것도 없어.";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "얀, 네가 가진 철목 좀 사고 싶어.";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "헬렌, 안녕, 내 사랑. 무슨 소식이 있지? 혹시 원하는 게 있었나?";
					link.l1 = "안녕, 얀! 그냥 너 보러 잠깐 들렀어, 그게 다야.";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "무엇을 도와드릴까요?";
				link.l1 = "아니, 괜찮아.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "젠장, 너를 알아보겠어! 네가 바로 룸바를 구하고 영국 코르벳의 대포를 정면으로 맞선 그 용감한 선장이잖아! 이렇게 다시 보게 되어 정말 기쁘군! 헬렌은 내 딸이나 다름없지. 오늘부터 나는 너에게 평생 신세를 졌다. 그냥 야안이나 스벤손이라고 불러도 돼. 내가 뭘 도와주면 되겠나?";
			link.l1 = "나는 토르투가의 총독 레바쇠르를 제거해야 해. 그의 섬까지 가서 접근하는 게 쉽지 않을 거란 걸 알기에, 조언을 구하려고 너에게 온 거야.";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "이런, 자네가 몇 년 전에 어디 있었는지! 나도 똑같은 일을 꾸미고 있었지. 그 자가 프랑스놈들과의 모든 판을 망쳐놨어. 하지만 그땐 모든 게 달랐지. 블레이즈는 살아 있었고, 샤크는 위세가 있었으며, 네이선이 마룬 타운에서 모든 걸 좌지우지했지... 지금은 모든 게 변했고, 하느님만 아시겠지만, 결코 좋은 쪽으로는 아니야. 우리에 대해, 형제단에 대해 아는 게 있나?";
			link.l1 = "여기에 막 도착해서 아는 게 거의 없어. 네가 잭맨이랑 함께 평의회 일원이라는 것 말고는 말이야.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "아, 그 잭맨 정말 못 참겠어! 저 자가 온 뒤로 우리 문제는 시작됐지. 네 부탁은 생각해 보마. 지금은 딱히 떠오르는 게 없어.";
			link.l1 = "잭맨에 대해 흥미로운 소식이 있어.";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "흠. 저게 뭐지?";
			link.l1 = "잭맨은 글래디스 챈들러와 그녀의 딸을 찾고 있다. 히긴스와 얘기해 본 뒤로, 그는 룸바를 찾고 있는 것 같다는 생각이 들기 시작했다. 글래디스는 헬렌의 친어머니가 아니며, 션 맥아더와 결혼하기 전에는 챈들러라는 성을 썼던 것 같다.";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "젠장! 안 좋은 소식이군. 이제 잭맨은 그 어느 때보다 강해졌어. 게다가, 혼자 움직이는 게 아닌 것 같아 불길한 기운이 느껴져. 그의 뒤에 뭔가 섬뜩한 그림자가 있어. 만약 그자가 정말로 헬렌을 필요로 한다면, 그 아가씨는 반드시 누군가의 보호가 필요해. 내가 직접 나서기엔 이제 너무 늙었지...\n";
			link.l1 = "그게 전부가 아니야. 잭맨은 '넵튠'의 전 보선장이자 부처 선장의 선원인 헨리 더 행맨이라는 자도 찾고 있어.";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "카람바! 내 최악의 의심이 현실이 되었군! 그 도살자와 그의 '넵튠'은 예전에 군도 전체를 공포에 몰아넣었지. 그땐 해적단도 없었고, 모두가 각자도생이었어. 그 자는 많은 악행을 저질렀고, 내게 소중한 사람도 그 때문에 죽었지.\n나는 그를 직접 만날 기회가 없었어. '넵튠'은 영국 프리깃에 의해 침몰당했고, 도살자는 세인트 존스에서 처형당했다네. 잘 됐지 뭐! 그래도 그의 행운과 무모한 용기를 동경한 이들도 많았지.\n잭맨이 바로 그 도살자의 오른팔이자 '넵튠'의 일등항해사였어. 놀랐나? 전과자들이 이제는 국가의 영웅이 되었으니, 이게 다 크롬웰 덕분이지! 옛 영국은 다 어디로 간 걸까?\n잭맨의 부하들보다 우리가 먼저 헨리 교수형집행인을 찾아야 해. 그가 아직 살아 있다면, 이 미스터리의 열쇠를 쥐고 있을지도 몰라.";
			link.l1 = "건초 더미에서 바늘을 찾는 게 더 쉬울 것 같은데. 그래도 단서라도 좀 있나?";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "나는 헨리를 어릴 때부터 알았지. 카르타헤나 출신 창녀의 아들이었고, 반은 스페인 놈이었지만 그 사실을 늘 숨기고 다녔어. 그의 어머니는 불같은 여자였지! 예쁘다고는 못 하겠지만, 그녀만큼 플라멩코를 추는 여자는 드물었어. 창녀촌 전체가 벌거벗은 치카 곤살레스와 그녀의 캐스터넷 공연을 구경하곤 했지. 불쌍한 여자야. 끔찍한 병에 걸려 촛불처럼 서서히 사라졌거든. 그때 내가 헨리에게 프로비던스로 가라고 설득했지. 거기서 그는 금세 이름을 날렸고, 니콜라스 샤프의 절친 토마스 벨트로프의 선원으로 들어갔어. 그 둘은 엘리자베스 여왕의 마지막 개들이었고, 항상 함께 일했지. 좋은 시절이었어! 파트너가 죽자 토마스는 영국으로 돌아갔지. 선원들도 데리고 갔지만, 헨리는 카리브에 남았어. 여러 선장 밑에서 항해하다가 도살자가 나타났지. 참고로, 그 별명은 항상 곁에 두던 커틀라스 때문에 붙은 거야.";
			link.l1 = "그래서 이 정보가 우리에게 무엇을 말해 주는 것이오?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "교수형 집행인이 해적들에게서 숨기로 마음먹었다면, 그에게 가장 좋은 곳은 스페인 도시일 거야. 특히 친구들과 친척들이 있는 카르타헤나의 자기 집이겠지. 헨리는 꽤 신앙심이 깊은 사람이었으니, 다른 성인의 교회로 갈 가능성은 적어. 아마 어릴 때부터 써온 이름, 엔리케를 여전히 쓰고 있을 거야.";
			link.l1 = "그래... 별로 건질 건 없지만, 없는 것보단 낫지.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "찾아보게, 샤를! 헨리의 스페인 혈통을 아는 자는 드물어, 우리가 여기서 약간의 우위를 점하고 있네. 룸바를 자네 선원으로 들이게 설득하는 방법을 생각해 보겠네. 그 아가씨는 배짱이 대단하지, 아버지 외에는 누구의 지휘도 받아본 적이 없으니 말일세.\n하지만 그녀는 배도 없고 선원도 없어, 살아가기 위해 뭔가 해야 하네. 물론 나는 늘 그랬듯이 글래디스를 계속 도울 것이지만, 헬렌을 블루웰드에 오래 붙잡아 둘 수는 없을 걸세. 그리고 자네에게는 그런 장교가 무척 쓸모 있을 걸세. 션이 자기 아는 모든 것을 그녀에게 가르쳤고, 마치 아들을 키우듯 키웠지.\n그녀가 자네 같은 선장의 지휘 아래 있다면 내 마음이 한결 놓일 것 같네.";
			link.l1 = "룸바는 정말 쓸모 있는 인물임을 증명했지. 내 선원 중에 그녀 같은 사람이 더 필요해. 그러니 네가 그녀를 설득할 수 있다면, 내가 그녀를 장교로 삼겠네. 하지만 먼저, 나는 그녀가 진짜 누구인지, 그리고 왜 잭맨이 그녀를 필요로 하는지 알고 싶어. 두려운 건, 도노반과 달리 잭맨은 그녀의 매력에는 관심이 없다는 점이지. 그래서 행맨을 찾아보려고 하네만, 아무것도 장담할 수는 없어.";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "좋아, 훌륭하군. 여기 네덜란드 서인도 회사에서 발급한 3개월짜리 허가증이 있다네. 여기에 이름을 적게. 자네가 수색을 할 때 분명 쓸모가 있을 걸세. 그동안 나는 자네가 말한 르바쇠르와 토르투가에 대해 생각해 보겠네.";
			link.l1 = "정말 고마워! 이 문서는 나한테 큰 도움이 될 거야. 그렇다면, 난 이제 카르타헤나로 떠난다.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "헨리가 죽었다고? 잠깐, 네가 그를 죽인 거야?";
			link.l1 = "그렇게 눈을 크게 뜨고 나를 보지 마! 나는 아무 상관도 없어. 그는 자기 양심의 썩어가는 죄책감과 잭맨에 대한 두려움 때문에 스스로 죽음을 택했지. 그 늙은 해적은 심장에 문제가 있었고 오래 살 사람도 아니었어. 내가 알아낸 건 이거야...\n";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "제발, 말해 줘!";
			link.l1 = "20년 전, 헨리는 부처 선장을 대신해 자신의 친딸의 양어머니에게 금 상자를 전달하기로 되어 있었소. 이 양어머니가 맥아더 부인이라는 점에는 전혀 의심의 여지가 없소. 그때 그녀는 챈들러라는 성을 쓰며 벨리즈에 살고 있었지. 하지만 사정이 생겨 행맨은 세인트 존스에 한 달이나 더 머물러야 했고, 마침내 벨리즈에 도착했을 때는 이미 스페인군의 습격으로 폐허가 되어 있었으며, 글래디스 이모와 션은 이미 당신의 보호 아래 떠난 뒤였소.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "그들은 헬렌을 친딸인 것처럼 속여서 자기 자식으로 키웠지. 헨리는 그들을 놓쳐버리고, 잭맨의 복수를 의식해서 지난 이십 년 동안 숨어 지내며 두려움에 떨었어. 알고 보니 잭맨이 자기 선장의 딸을 찾고 있더군. 하지만 왜인지는 나도 모르겠어.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "어쩌면 누군가의 명령을 수행하고 있는 걸지도...";
			link.l1 = "의심스럽군. 누가 그에게 명령을 내릴 수 있겠어? 부처는 죽었어. 그의 죽음은 공식 문서로 확인됐지. 수십, 아니 수백 명이 그의 죽음을 목격했어.";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "어쩌면 이건 헬렌의 아버지가 누구냐가 아니라, 그녀의 친어머니에 관한 일일지도 몰라. 그녀가 누구였는지 이미 짐작은 가지만, 인정하기가 두려워. 하지만 글래디스! 어떻게 그녀는 남편에게조차 이 사실을 수년 동안 숨길 수 있었던 거지! 션 맥아더라면 분명 나에게 말했을 거야. 우리는 서로 숨기는 비밀 따윈 없었으니까.";
			link.l1 = "글래디스와 진솔하게 대화 좀 나눌 생각이야. 그녀의 입을 열 방법이 생긴 것 같거든. 다음에 보자, 얀!";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "그거 어디서 났어!?";
			link.l1 = "글래디스가 나에게 줬어. '헬렌 어머니의 유산'이라고 하더군. 이름은 모른대. 왠지 이게 그냥 평범한 종이쪼가리는 아닌 것 같아.";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "내가 예전에 헬렌의 진짜 어머니가 누군지 감이 온다고 했던 거 기억나? 이제 확신이 생겼어. 그녀의 이름은 비트리스 샤프였어. 그녀는 내 스승이자 친구였던 니콜라스 샤프의 친딸이고, 우리 형제단을 세운 블레이즈 샤프의 공인된 자매였으며, 이슬라 테소로의 공동 소유자였지. 잭맨이 노리는 게 바로 이 지도 조각이야.";
			link.l1 = "이런, 그거 참! 그런데 그가 왜 섬 지도 반쪽만 필요로 하는 거지?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "이 섬은 니콜라스 샤프가 발견했다. 그는 이 섬에 이슬라 테소로라는 이름을 붙이고, 지도를 만들었으며, 자신이 좋은 인맥을 가지고 있던 프로비던스 아일랜드 컴퍼니를 통해 소유권을 주장했다.\n니콜라스는 자신의 증언에서, 섬의 상속권은 지도 두 조각을 모두 가진 자만이 가질 수 있다고 적었다. 그는 분쟁을 피하기 위해 이렇게 했다. 니콜라스는 비애트리스와 의붓아들 블레이즈에게 그 조각들을 나누어 주었고, 이후 스페인인들에게 비극적으로 살해당했다.";
			link.l1 = "이런, 젠장! 참 이상하군.";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "맞아. 그게 최선의 생각은 아니었지. 그리고 교활한 공증인이 상속인들이 죽은 후 1년 안에 누구도 지도 양쪽을 모두 내놓지 않으면 그 섬은 영국 왕실 소유가 된다고 덧붙였지.\n그땐 아무도 이런 일이 일어날 줄 몰랐어. 그리고 이제 우리는 우리의 어리석음에 대한 대가를 치르고 있지. 베아트리스는 20년 전에 죽었어. 그 오랜 세월이 지났지만 우리는 아직도 그녀의 무덤, 그리고 그녀가 가진 지도 조각이 어디 있는지 전혀 몰라. 블레이즈 샤프도 얼마 전에 살해당했어. 그의 조각도 사라졌지.\n만약 1년 안에 누군가가 이슬라 테소로의 전체 지도를 당국에 제출하지 않으면, 샤프타운은 영국이 차지하게 돼. 그들은 총독과 주둔군을 보낼 거고, 우리 형제단은 끝장나게 될 거야.";
			link.l1 = "우리가 어떻게 하면 좋겠소?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "이런 일이 일어나게 둘 수는 없어. 나는 네가 필요해, 샤를, 네가 이런 사태를 막아야 해. 그리고 우리가 이슬라 테소로를 장악하고 샤크 도드슨을 브레드런의 새 수장으로 선출한 뒤에야만 레바쇠르를 제거하는 데 널 도울 수 있어. 그는 우리 중 가장 자격이 있는 인물이야. 나는 너에게 동맹을 제안하지.\n그리고 참고로, 헬렌과 이야기했어. 그녀가 네 선원으로 합류하기로 동의했어.";
			link.l1 = "나에게 선택의 여지가 없군, 얀. 나는 가문의 명예를 회복하지 않고서는 프랑스로 돌아갈 수 없어. 그러기 위해서는 네 도움이 있든 없든 레바쇠르를 반드시 제거해야 해. 불필요한 희생은 원치 않으니, 피를 많이 흘리지 않고 토르투가를 차지할 방법을 네가 잘 생각해주길 바란다. 그리고 솔직히 말하자면, 샤프의 유산을 둘러싼 그 흐릿한 과거의 진실도 내가 직접 밝혀보고 싶군.";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "이제야 말 좀 통하는군! 토르투가를 제대로 점령할 방법을 우리가 찾아낼 거야. 그건 내가 약속하지. 자, 가볼까?";
			link.l1 = "가자! 내가 조금 있다가 다시 들르겠네. 그동안 어디서부터 문제를 해결할지 생각해 보게.";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "이삼일 후에 다시 들르시오. 그때쯤이면 내 계획이 결실을 맺을 것 같소. 그리고 헬렌을 꼭 배에 태워 가는 것 잊지 마시오. 그 불쌍한 아가씨는 바다 없이 시들어가고 있소. 충직한 조수가 되어 줄 테니, 믿고 맡겨도 두 번 생각할 필요 없을 것이오.";
			link.l1 = "알겠소, 얀. 지금 바로 그녀를 데려오겠소.";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "첫째로, 상어를 찾아야 하네. 그 자가 직접 르바쇠르를 제거하려 했고, 분명 기발한 생각도 가지고 있지. 물론, 마르쿠스를 설득해서 지도자가 되게 할 수도 있지. 어쨌든 그는 코덱스의 관리인이니까. 하지만 그가 도움이 될 것 같진 않네; 그는 일부러 르바쇠르와 토르투가와의 접촉을 피하고 있거든. 원칙을 중시하는 사람이야. \n스티븐과 그의 부하들이 어디 숨어 있는지는 전혀 모르겠지만, 그의 프리깃 '포춘'이 푸에르토 프린시페에서 목격됐지. 어쩌면 검은 목사로도 알려진 자카리 말로가 상어를 어디서 찾아야 할지 알려줄 수 있을 거야. 둘째, 우리는 도드슨을 선출하기 위해 다른 남작들의 지지를 얻어야 해. 그러려면 그들의 인디언 파편, 즉 표를 모아야 하지. 새 지도자는 다섯 개 모두를 가져야 해. 이전 지도자가 죽었을 때는 그렇게 하라고 코드에 나와 있지. \n말도 안 돼! 이제 법을 바꿔야 할 때지만, 그건 새 지도자만이 할 수 있지. 내 표는 이미 확보됐어. 검은 목사는 샤프타운에 누가 앉든 신경도 안 쓸 거라 생각해. 잭맨이 먼저 그와 얘기하지 않았길 바랄 뿐이야. 또 티렉스와 자크 바르바종, 서로 증오하는 두 사람도 설득해야 해. 하지만 상어에게 무슨 일이 일어났는지 알아내기 전까진 이 모든 게 아무 소용없지. 셋째, 언젠가 우리는 잭맨을 죽이고 다른 사람으로 교체해야 해. 그는 우리와 협상하지 않을 거야. \n호크가 죽어서 정말 아쉽군! 사람들은 그를 신뢰했고, 그의 말이 필요했지. 마룬 타운을 위해 그보다 나은 남작은 찾을 수 없을 거야. 잭맨이 블레이즈 살인에 연루됐을 가능성도 있으니, 그가 바로 두 번째 지도 조각을 찾는 실마리이기도 해. 제이콥은 누구도 믿지 않고, 아마도 지도 조각을 '센튜리온' 선실에 보관하고 있을 거야. \n호크의 가족이 원래 그 프리깃을 소유했지만, 잭맨이 호크의 남작령처럼 그 배도 차지해버렸지. 만약 잭맨이 두 번째 지도 조각을 가지고 있다면, 스티븐을 지도자로 선출하는 데 큰 명분이 될 거야. 특히 코드의 관리인 마르쿠스 티렉스와 그의 지나친 명예 집착에 말이지. 우리가 지도 두 조각을 모두 손에 넣으면, 헬렌에게 이슬라 테소로의 권리를 돌려줄 거야. \n하지만 조심해야 해; 잭맨이 가만히 앉아서 네가 수색하는 걸 지켜보고만 있진 않을 테니.";
			link.l1 = "음... 이제 곧 블랙 파스터를 만나러 갈 참이야. 그에 대해 말해 봐.";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "그 자가 무슨 생각을 하는지 나도 전혀 모르겠어. 가끔 보면 완전 미친놈처럼 보이지만, 사실은 교묘한 연기일 뿐이라고 생각해. 게다가, 그의 부하들은 사랑하는 목사님을 위해서라면 악마랑도 싸울 각오가 되어 있지.\n쿠바에서 스페인 종교재판소 근처에다가 무슨 신교도 집단을 세웠다더군. 그러니 거기서는 신학 얘기 같은 건 꺼내지도 마라; 절대 곱게 안 볼 테니까.";
			link.l1 = "그 점을 고려하겠소...";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "그리고, "+pchar.name+": 단 1분도 허비하지 마. 진심이야. 유언장에 상속인들이 1년 안에 섬을 청구하지 않으면, 이슬라 테소로가 영국 왕실에 넘어간다는 조항 기억하지? 지금은 시간이 우리 편이 아니야. 너랑 내가 마지막으로 만났을 때, 기한이 끝날 때까지 남은 시간이 대략 11개월밖에 안 남았었지.";
			link.l1 = "기억하고 있어, 얀. 네 말이 맞아, 시간은 돈이지. 내가 바로 할게!";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "흠... 자카리가 뭐라고 했지?";
			link.l1 = "그가 사라지기 전에, 샤크가 그를 찾아와서 자신의 프리깃함을 자카리에게 식량이 실린 브리그와 맞바꾼 담보로 맡기고, 북서쪽 쿠바를 향해 어딘가로 떠나갔어.";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "정말 수상하군. 계속 말해봐.";
			link.l1 = "한 달이 지나도 도드슨은 돌아오지 않았고, 목사는 약속대로 프리깃함을 자기 것으로 삼아 패터슨이라는 자에게 좋은 값에 팔아넘겼소. 우리 일과 관련해서는, 자커리가 샤크가 전설의 저스티스 아일랜드로 떠났을지도 모른다고 했는데, 그 섬은 쿠바 북서쪽 어딘가에 있다고 하오.";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "나는 저스티스 섬에 대해 들었네. 백인과 흑인이 평등하게 평화롭게 산다는 섬이 있다더군. 꿈꾸는 자들이 퍼뜨리는 헛소리지. 하지만 북서쪽 어딘가에 밀수업자들의 기지가 있을 가능성은 있네. 십 년 전만 해도 그들의 바크선이 공해상에서 자주 목격됐었지.\n그들은 식량과 맞바꾸며 쿠바로 온갖 물건을 들여왔네.";
			link.l1 = "음식을 위해 보물을 준다고? 목사님도 소고기를 실어 나르는 버커니어들 이야기를 해줬지. 정말 앞뒤가 안 맞는 일이지.";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "이런 소문에는 반드시 근원이 있기 마련이오. 밀수업자나 부카니어들의 바크선이 그 지역으로 항해한 데는 무슨 이유가 있었을 것이오. 상어가 젊었을 적 얘기를 내게 해준 게 기억나는데—그는 바다 한가운데 난파선으로 지어진 이상한 구조물에서 노예 생활을 했다고 하더군. \n어쩌면 그곳이 우리가 찾는 장소일지도 모르지? 알 수 없소. 아무튼, 목사 말이 일리 있소—저 바다 어딘가에 뭔가가 있소, 비밀 기지든 상어가 갔을지도 모를 섬이든. 들어보시오, 산토도밍고로 가서 호세 디오스라는 과학자를 찾으시오. \n그는 스페인 출신 지도 제작자요. 내가 예전에 그를 더러운 악당들로부터 구해준 적이 있소; 나는 배운 사람을 존중하오. 내 이름만 대면 그가 도와줄 것이오. 히스파니올라로 가서 디오스를 찾아 그와 이야기하시오. \n그는 우리 지역의 지리를 완벽하게 알고 있소, 만약 그가 도와주지 못한다면—누구도 못할 것이오.";
			link.l1 = "알겠어, 얀. 좋은 생각이야. 다녀올게!";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "안타깝군. 호세가 우리를 도와줄 줄 알았는데.";
			link.l1 = "나도 그걸 기대했었지, 하지만 어쩔 수 없군. 자, 자기연민에 빠지지 말자고. 이 일에 대해 좀 더 생각해보겠네. 그래, 얀, 말해보게, 호크는 어떻게 죽었나?";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "아무도 그의 죽음을 목격하지 못했어, 그의 시신을 본 사람도 없고. 몇 달 전에 그냥 사라졌지. 그 이후로는 샤크 때와 마찬가지야, 흔적조차 없어. 하지만 스티븐과 달리 네이선은 숨어야 할 이유가 없었어. 그래서 모두들 그가 셀바에서 죽었다고 생각한 거지. 그렇지 않았다면 잭맨을 대신 뽑는 데 동의하지 않았을 거야.";
			link.l1 = "호크가 정글에서 대체 뭘 하고 있었던 거야?";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "내 잘못이오, 나는 늙은 바보요! 내가 그에게 새로 온 악당들과 거래하라고 부추겼소. 그들이 누구인지, 두목이 누군지 전혀 모르오. 평소 같았으면 신경도 안 썼겠지만, 그놈들이 우호적인 미스키토족을 납치하기 시작했소. 그들의 전쟁 추장 쿰바나가 전쟁을 선포하겠다고 위협하며 내게 도움을 요청했지. 어쩔 수 없이 개입할 수밖에 없었소.\n호크는 소규모 부대를 이끌고 모스키토 해안에 상륙했으나, 기가 막히게 조직된 매복에 걸려 패배했소. 그와 그의 부하들이 거기에 상륙할 줄 이미 알고 있었던 것 같았소. 정글에서 발견된 시신들 중에 호크의 시신은 없었소.";
			link.l1 = "당신 코앞에서 온갖 말썽이 벌어지고 있잖아! 호크의 부하들 중에 산적들을 처리해보려 한 놈은 없었어?";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "잭맨이 모두를 앞질렀지. 형제단 평의회에서 문제를 해결하겠다고 자원했고, 결정을 내렸어. 미스키토족이 더 이상 실종되지 않았지만, 산적들은 그곳에 남아 조용히 지내고 있었지.\n잭맨은 그들이 공격자 중 누구도 인질로 잡고 있지 않으니, 형제단이 그들에게 전쟁을 선포할 이유가 없다고 했어. 호크가 먼저 공격했으니, 우리 법에 따르면 산적들도 스스로를 지킬 권리가 있었지. 모두가 동의했어. 모두, 단 한 명만 빼고...";
			link.l1 = "누구 빼고 모두라는 거지?";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "네이선에게는 아내가 있었지. 이름은 다니엘 호크였고, 정말 강인한 여자였어! 선장을 잃은 슬픔을 극복했을지 의문이야, 게다가 처음부터 뭔가를 의심하고 호크를 말리려 했으니 말이야. 그 일로 크게 다툰 것도 기억나는데, 사실 그들에겐 그런 일이 흔한 일이었지.";
			link.l1 = "그리고 지금 다니엘은 어디에 있지?";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "누가 알겠어! 잭맨이 그녀를 마룬 타운에서 내보낸 건 확실하지. 그녀는 나를 찾아오지도 않아. 우린 원래 서로 안 좋아했는데, 세월이 흐르면서 그녀는 더 심술궂어졌고, 이제는 나를 정말 미워할 거야. 아마 자기 불행이 다 내 탓이라고 생각할 테니까. 어쩌면 혼자서 호크를 찾으러 다니는지도 모르지. 하지만 바지 입고 군도 찬 여자 하나가 뭘 할 수 있겠어! 그런데 말인데, 그녀는 군도 실력이 대단해. 혹시 마주치면 시험해볼 생각은 하지 마. 그리고 산적들과 말 섞는 것도 소용없어. 거긴 아주 대단한 야영지를 차려놨고, 무장도 엄청나게 했거든. 전직 군인들 같고, 일도 아주 잘 알아서 해. 자기네 구역엔 아무도 못 들어오게 해. 예전엔 스페인 놈들이 거기서 금을 캤다더라. 하지만 금이 다 떨어지니까 광산을 버리고 떠났지. 저 놈들이 거기서 뭘 하는지는 나도 전혀 모르겠다.";
			link.l1 = "음, 아무도 호크의 시신을 본 사람이 없으니, 그가 살아 있을지도 모른다는 희망은 남아 있지. 신만이 아시겠지만, 어쩌면 그를 다시 남작 자리로 돌려보낼 수도 있겠군.";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "그래, 그렇지. 자, 이 편지를 받아. 스티브 도드슨을 만나면 바로 전해 줘. 이 편지 내용이 네 안전을 보장해 줄 거야. 뭐, 만일을 위해서지.";
			link.l1 = "고마워, 얀. 꼭 그렇게 할게!";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "왜 그렇게 시무룩해? 피곤해? 럼 한 잔 할래?";
			link.l1 = "나도 상관없지...";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "여기, 한 잔 받아. 이제 말해.";
			link.l1 = "(술 마시며) 아, 이제야 좀 낫군... 자, 얀, 너랑 블랙 파스터 둘 다 맞았어. 저스티스 아일랜드는 정말 존재해. 나 거기 다녀왔어.";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "저기 밀수 기지가 있다고 내가 말했잖아!";
			link.l1 = "실제로는 어떤 기지도 없어. 그리고 카리브 해에 떠도는 소문이 거짓이 아니었지. 거기서는 흑인과 백인이 정말 함께 살고 있더라고, 꼭 평화롭게는 아니고, 고양이와 개처럼 으르렁거리면서 말이야. 그리고 그 섬 자체도 셀 수 없이 많은 난파선들로 이루어져 있어.";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "믿을 수가 없군! 호세 디오스가 네 이야기에 아주 관심을 가질 거야, 분명히. 그 사람한테 언젠가 한번 들러 봐, 참고로 말이지.";
			link.l1 = "나중에 그를 찾아가겠소. 지금은 그럴 때가 아니오. 당장 처리해야 할 더 중요한 일이 있소. 나는 섬에서 네이선리얼 호크를 찾았소.";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "네이선을 찾았다고? 정말 대단하군! 그 사람은 어때?";
			link.l1 = "음... 그는 아프고, 늘 술에 취해 있으며, 깊은 우울에 빠져 있소.";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "젠장, 정말 낙담스럽군. 어디 있지? 네 배에 있나?";
			link.l1 = "아니, 그는 자기 배에 있어. 그 섬에.";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "뭐야, 그를 여기로 데려오지 않았어? 왜?";
			link.l1 = "그를 상대할 만한 게 없었으니까. 나는 배 없이 섬까지 왔지.";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "젠장, "+pchar.name+", 겨우 럼 한 잔 마셨으면서 헛소리를 해대는군, 마치 뻗을 때까지 퍼마신 것처럼. 뭐야, 카리브 해를 헤엄쳐서 건너왔나? 아니면 발에 거북이라도 묶고 온 거야?";
			link.l1 = "아니, 수영해서 온 거 아니야. 얀, 나 정글에서 바로 이 섬으로 왔어, 네이선처럼, 마법의 인디언 우상 덕분에. 이 얘기 너무 많이 해서 이제 미친 사람 아니라는 걸 증명하는 것도 지쳤으니, 그냥 믿어 줘, 알겠지!?";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "인디언 우상?";
			link.l1 = "카리브 해에는 최소 세 개의 쿠쿨칸 우상, 즉 쿠쿨칸 조각상이 알려져 있다네. 하나는 웨스트 메인 미스키토 마을 근처에, 또 하나는 저스티스 섬 얕은 바닷속에, 마지막 하나는 도미니카 카리브 마을에 있지. 이 우상들은 인디언의 마법을 빌려 인간을 시간과 공간을 초월해 즉시 이동시킬 수 있다네.";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "나는 세 개의 동상을 모두 원을 그리며 지나갔고, 결국 미스키토 마을에서 여정을 시작했던 바로 그 자리로 돌아왔어. 믿지 않겠다면 다니엘을 불러올 수도 있어. 그녀가 직접 두 눈으로 다 봤으니까!";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "다니엘? 호크의 아내 말인가? 그녀가 너와 같이 있었어?";
			link.l1 = "부분적으로는 맞아. 그녀가 직접 블루웰드에서 날 찾아내서 미스키토 마을로 데려갔고, 거기서 주술사를 만나 마법상으로 이끌렸지. 지금은 내 장교 중 한 명으로 일하고 있어, 물론 임시로 말이야.";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "나는 정말 어이가 없군, "+pchar.name+"! 영국 놈들 말대로네. 넌 태어날 때부터 금수저 물고 태어난 놈이야. 정말 운 좋은 자식이지! 좋아, 믿어주지, 믿기 힘들긴 해도. 하지만 네이선 문제는 여전해, 그 녀석은 도움이 필요해.";
			link.l1 = "그렇게 할 생각이오. 지금 정의의 섬으로 원정 준비 중이오. 이제 필요한 건 다 갖췄소: 섬의 좌표와 항로 안내까지.";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "환상적이군. 내가 도울 일이라도 있을까?";
			link.l1 = "아니요, 괜찮습니다. 그런데 한 가지 작은 사실을 빼먹었군요. 네이선 말고도 섬에서 샤크 도드슨도 발견했습니다.";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "그래, 정말 거기로 간 거였군! 자, "+pchar.name+", 훌륭하게 해냈군. 거기서 도드슨은 잘 지내고 있나? 물론 그와 이야기해봤겠지, 안 그런가?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "나는 그와 이야기만 한 게 아니라, 이제 친구가 되기도 했어. 내가 섬으로 돌아가는 데 필요한 항해 지침도 그가 준 거야. 스티븐은 자기 군함의 선실을 샤프타운의 저택과 바꾸기로 동의했어.";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "우리는 대화를 나눴지, 그래. 하지만 결국 아무 소용도 없었어. 내가 그 섬에 머무는 동안 스티븐은 그의 보선, 채드 캐퍼가 꾸민 음모가 실행되면서 죽임을 당했거든.";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "하! 그런데 상어 녀석이 어떻게 전함의 선장이 된 거지?";
			link.l1 = "그 배는 반세기가 넘도록 끝없는 '정적' 속에 있었어. 그는 선원들과 함께 그 섬에 갇혀 있지. 그래서 그렇게 오랫동안 카리브 해에 모습을 드러내지 않은 거야. 아무튼, 곧 그를 여기로 데려올 테니 직접 그의 모험담을 들을 수 있을 거야.";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "나 그거 정말 기다릴 수 없어! 이제야 상황이 나아지기 시작했어. 우리 방금 더 강해졌잖아, "+pchar.name+". 언제 섬으로 돌아갈 계획이오?";
			link.l1 = "지금 바로 말이야. 난 잠깐 소식 전하러 들어온 거고, 다니엘은 원정 준비 중이야. 걔, 네이선을 너무 보고 싶어 하더라. 그리고 있잖아, 얀, 걔 그렇게 못된 년 아니더라.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "그래? 뭐, 내가 그녀에 대해 완전히 맞았던 건 아닐지도 모르지. 좋아, "+pchar.name+", 더 이상 붙잡지 않겠소. 가시오, 행운이 함께하길! 돌아오기를 기다리겠소.";
			link.l1 = "잘 있어, 얀.";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "채드 카퍼? 젠장, 그 녀석 알지. 스티븐을 죽였다고? 그 망할 놈...";
			link.l1 = "카퍼는 죽었어. 하지만 스티븐을 되살릴 수는 없으니, 앞으로 우리 정치 조직을 어떻게 이어갈지 생각해야 해.";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "하! 그거 참 안됐군... 뭘 고민할 게 있나? 그냥 타이렉스를 설득해서 브라더후드를 이끌게 하면 되지. 게다가 블레이즈 다음으로, 타이렉스는 규약을 지키는 자로서 우리 중 가장 존경받는 인물이야. 하지만 먼저 호크를 데려와야 최소한 비장의 패 한 장은 쥐게 되지. 언제 섬으로 떠날 생각이야?\n";
			link.l1 = "지금 바로 말이야. 나는 잠깐 여기 들어와서 소식 전해주려고 온 거야, 다니엘이 원정 준비하는 동안에. 걔는 네이선을 너무 보고 싶어 하거든. 그리고 있잖아, 얀, 걔 그렇게 나쁜 년 아니야.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "그는 어떻소? 몸이 안 좋다고 했잖소.";
			link.l1 = "그래, 바로 그거야. 나는 그를 데리고 뱀눈이라는 주술사가 있는 미스키토 마을로 치료받으러 갈 거야.";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "그럼 지체할 시간 없어! 서둘러, "+pchar.name+"! 네가 네이선을 주술사에게 데려다주자마자 바로 나에게 돌아와라.";
			link.l1 = "알겠어, 얀. 괜찮은 계획이군.";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "좋소. 스티븐이 이미 나를 찾아왔네. 이제야 비로소 우리의 계획에 대해 계속 논의할 수 있겠군.";
					link.l1 = "난 잘 듣고 있어, 얀.";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "그거야 좋지만, 도드슨은 왜 아직 나를 보러 오지 않은 거지? 뭐야, 그를 섬에 두고 온 거야?";
					link.l1 = "흠... 네이선을 스네이크 아이에게 데려가려고 서두르고 있었지...";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "알겠네. 샤크를 생각하면 마음이 아프지만, 그게 인생이지. 이제 타이렉스가 그 자리를 대신할 거야. 자, 이제야 우리 계획에 대해 계속 이야기할 수 있겠군.";
				link.l1 = "무슨 말이든 들어줄게, 얀.";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "... 그리고 샤크를 데려오는 것도 잊었단 말이야? 믿을 수가 없군."+pchar.name+"! 지금 당장 스티븐을 블루웰드로 데려가! 듣고 있나? 어서 가!";
			link.l1 = "진정해, 얀. 내가 다 알아서 할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "스티븐이 나를 보러 들렀어. 이제야 우리 계획에 대해 계속 이야기할 수 있겠군.";
				link.l1 = "잘 듣고 있네, 얀.";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "오, "+pchar.name+"... 내 생각엔 요즘 럼주를 너무 많이 마신 것 같군. 그게 결코 좋은 끝을 가져오지 않지. 처음엔 손이 떨리기 시작하고, 그다음엔 기억을 잃기 시작하다가, 결국엔 검은 점까지 받게 되지...";
				link.l1 = "알겠어, 얀. 바로 스티븐 데려올게!";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "검은 목사님은 아주 분명하게 말씀하셨소, 그분은 오직 그 신학 서적에만 관심이 있소. 내가 부하들을 보내 그 책을 찾게 했으니, 어쩌면 누군가 발견할지도 모르지. 마커스 타이렉스는 문제가 아니니, 설득하는 데 어려움은 없을 것이오. 잭맨은 자네가 찾아간 직후 마룬 타운을 떠났소. 그는 '센츄리온', 즉 호크스의 프리깃을 타고 어딘가로 떠났지.\n이제 바르바존만 남았소 - 그는 자크 더 카인드맨으로도 알려져 있지. 우리가 그를 협력하게 만들 방법을 찾아야 하오. 아직 어떻게 해야 할지 모르겠소. 하지만 한 가지는 분명하오 - 자네가 직접 그를 찾아가야 하오.";
			link.l1 = "바르바종에 대해 말해 줘."; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "비밀스러운 놈이지. 가난한 척하지만, 사실 카리브에서 제일 부자인 자일 거야. 동부의 모든 밀수 작전을 쥐고 있지. 마르쿠스가 그를 막지 않았다면, 윈드워드 제도의 밀수는 전부 그의 손아귀에 들어갔을 거다. 티렉스는 그의 목에 걸린 가시 같은 존재야.\n평의회에서 늘 말다툼만 하지만, 바르바종은 대놓고 전쟁을 선포할 배짱이 없어. 그가 주장하듯 정말로 한때는 덩케르크의 해적이었을지도 모르지만, 지금은 고리대금업자 같다는 생각만 들어.";
			link.l1 = "도대체 저 자식이 어떻게 남작으로 뽑힌 거야?";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "금이란, 친구야, 모든 것과 모든 곳을 지배하지. 금을 가진 자가 규칙을 만드는 법이야. 게다가 바르바종은 온갖 이익이 되는 불법 사업을 꾸며내는 데 아주 능하지. 직접 참여하진 않지만, 항상 몫은 챙기지. 그래서 늘 용감하지만 머리가 약한 깡패들이 그를 둘러싸고 있지. 그 자가 없으면 다들 굶어 죽거나 교수대에 오르게 될 거야.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "그 사람을 보니 마르쿠스가 생각나는군... 얀, 사실은... 바르바종에게 어떻게 접근해야 할지 전혀 모르겠어. 네가 모르는 문제가 하나 있어.";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "바르바종에는 어떻게 가나요?";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "그냥 통통한 일거리를 얻으려면 귀띔이 필요한 멍청이들 중 하나인 척해라. 그의 몫을 속여 빼앗을 생각은 꿈도 꾸지 마라. 자비로운 바르바종은 용서하지 않는다.";
			link.l1 = "그건 두말할 필요도 없지. 내 이익을 위해 그 자와 엮이는 건 아니야. 아무튼, 이제 그를 찾아갈 때가 됐군.";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "정말이야? 해 봐.";
			link.l1 = "찰리 프린스에 대해 들어본 적 있어?"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "그래, 소문 들었지. 이 자, 얼마 전까지만 해도 마르쿠스 타이렉스 밑에서 일했대. 아주 짧은 시간에 많은 일을 해냈고, 카르타헤나를 약탈해서 이름을 날렸지. 그래서?";
			link.l1 = "이 녀석이 나야. 나는 찰리 프린스였지. 이제 알겠어?"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "젠장! 네가 샤를리 프랭스냐? 이런 반전이 다 있나! "+pchar.name+", 감탄했소! 이제야 그대의 힘이 어디서 나오는지 알겠군... 그런데 바르바종이 이 일과 무슨 관련이 있소?";
			link.l1 = "왕자님이 바르바존을 한 번 찾아가 보는 건 어때, 얀?.."; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "흠... 알겠소. 전에 그 자와 엮인 적이 있소?";
			link.l1 = "정확히는 아니야. 바르바종의 직접 명령으로 이그나시오 마르코라는 놈이 나를 해치려 들었지. 그들끼리 벌이는 작은 전쟁의 일부였어."; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "그가 네 얼굴을 봤어? 네가 직접 자기소개했어?";
			link.l1 = "아니."; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "여기서는 아무 문제가 없어 보이네. 나도 코르세어 찰리 프린스에 대해 들었지만, 네가 그 사람이라는 건 네가 말해주기 전엔 몰랐어.";
			link.l1 = "바르바종이 내가 속이려는 걸 모를 것 같아?"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "그가 네 얼굴을 본 적도 없는데 어떻게 그러겠어? 그가 한 일이라곤 마르쿠스의 부하 하나를 처리하라고 명령한 것뿐이야.";
			link.l1 = "흠... 네 말이 맞을지도 모르겠군."; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "바르바종 없이는 이 상황을 절대 헤쳐나갈 수 없어. 그를 만나러 가 봐, 하지만 조심해. 네 얼굴을 알아보면 바로 도망쳐; 그런 경우엔 우리가 다른 방법을 생각해 볼 테니.";
			link.l1 = "좋아. 이제 가봐야겠군. 그 망할 놈을 만나는 걸 기다려 왔지."; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "모르는 척하지 말고 자크를 건드릴 생각도 하지 마라. 그 자식은 절대 용서 안 해. 쉬운 돈 벌려고 안달 난 바보처럼 굴어.";
			link.l1 = "내가 제일 좋아하는 역할인 것 같군... 잘 있어라, 얀!"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "그래. 인디언 주술사가 할 수 있는 건 다 했어, 호크는 이제 완전히 회복됐지. 지금쯤이면 이미 대니와 함께 마룬 타운에 있을 거야. 원한다면 가서 인사라도 해. 너를 보면 분명히 무척 기뻐할 거야.";
			link.l1 = "반드시 들러서 그들이 어떻게 지내는지 보고 올게... 얀, 내가 샤프의 지도 두 번째 조각을 찾아냈어! 잭맨 선장의 선실에 있었지. 이제 헬렌이 이슬라 테소로의 정당한 상속인임을 증명하는 데 아무 문제 없을 거야.";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "좋아, 그걸 보여줘.\n우리가 맞았어, 제이콥이 블레이즈를 죽인 놈이었어. 이제 샤크의 이름에 남은 오명은 반드시 완전히 지워져야 해. 증거 문제는 좀 더 신중히 다뤄야 할 일이야. 충분히 깊이 생각한 뒤에야 접근해야 해.";
			link.l1 = "그리고 한 가지 더 있어, 얀. 이 쪽지를 좀 봐. 이것도 잭맨의 물건들 사이에 있었어.";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "자, 한번 보자... 하, 그래서 산적들이 잭맨 말을 듣고 미스키토족 납치를 멈췄던 거군! 달리 될 리가 없었지! 저 악당이 모든 걸 계획했고, 몇 수 앞서 있었던 거야.";
			link.l1 = "그래, 그리고 왜 호크의 부하들이 몰살당했는지도 알겠어. 하지만 두 가지가 이해가 안 돼. 첫째, 잭맨의 동료들이 광산에서 뭘 하고 있는 거지? 둘째, 이 모든 난장판이 네 구역에서 벌어지고 있는데도 왜 이렇게 태연하게 굴고 있는 거야?\n";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "부끄럽군... 네 말이 맞아. 잭맨이 정말 도를 넘었지. 그리고 그 졸개들은 내 구역에서 설치면 안 돼. 이제 카리브 해에 누가 주인인지 다시 상기시켜 줄 때가 온 것 같군.";
			link.l1 = "무슨 생각이야, 얀?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "과거를 되살리는군... 나는 징벌 원정을 조직해 광산에 있는 모든 도적들을 소탕할 생각이오. 이제 그들이 잭맨의 부하들이라는 증거도 있으니, 내 영지에서 이런 쓰레기들을 반드시 쓸어내야 하오.\n"+pchar.name+", 훌륭히 해냈군. 이제 나는 움직여야겠어. 너는 당분간 쉬어. 호크스에게 가 봐. 열흘 뒤에 돌아오도록!";
			link.l1 = "좋아, 얀. 알겠어. 네가 말한 그 시간 안에 꼭 돌아올게!";
			link.l1.go = "saga_31";
			link.l2 = "하! 나도 이 원정에 참여하고 싶은데. 왜 나만 쉬라고 하는 거지?";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "용서해 줘, 친구. 이제 내가 좀 일하고 너는 좀 쉴 때가 됐다고 생각했거든. 하지만 그게 네 바람이라면, 난 더없이 기쁘지! 함께 폭풍을 헤쳐 나가자고! 그리고 광산에서 찾는 모든 것은 해적 형제단의 법에 따라 우리 선원들끼리 똑같이 나누자.";
			link.l1 = "좋아, 얀! 언제 출항하지?";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "사흘 뒤에 네 사람들을 데리고 모스키토 해안으로 와라. 그때쯤이면 내 부하들을 모아두고 이미 너를 기다리고 있을 거다. 늦지 마라!";
			link.l1 = "좋아, 숲의 악마. 너랑 등 맞대고 싸우러 가고 싶어서 몸이 근질근질하군! 곧 보자!";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "훌륭해. 나는 그 광산의 수수께끼 같은 소유주, 로렌스 벨트로프에 대해 뭔가를 밝혀냈어.";
			link.l1 = "그래서, 이 새는 누구지?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "잭맨의 졸개들에게 광산에서 두들겨서 알아냈지. 녀석들 만만치 않더군, 하지만 우리 부하들도 호락호락하지 않아. 게다가 네가 찾아낸 쪽지에 적힌 암호를 말해줬더니 경계심이 좀 풀리더라고. 결국 광산에 쳐들어가서 제대로 한방 먹여줬지.";
			link.l1 = "광산을 차지했어? 대단하군!";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "이게 바로 숲의 악마가 녹슬었다고 생각하는 놈들에게 주는 교훈이다. 지난 몇 년 동안 내가 너무 빈둥거렸더니, 이런 꼴을 당했지 않나? 잭맨이 내 코앞에서 악랄한 계략을 펼치고 있었단 말이다!";
			link.l1 = "그 광산에서 무엇을 봤지? 말해 봐!";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "광산은 스페인 사람들이 정말로 버리고 갔지만, 포트 로열의 로렌스 벨트로프가 헐값에 사들여 몰래 채굴을 계속했네. 우리가 직접 금을 발견하진 못했지만, 최근까지도 그곳에 금이 있었다고 주장하는 노예 몇 명을 발견한 걸 보면, 스페인 놈들이 너무 일찍 갱도를 포기한 모양이야.";
			link.l1 = "로렌스 벨트로프? 처음 듣는 이름인데. 누구지?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "그는 이곳 토박이로, 토머스 벨트로프의 아들이네. 토머스는 한때 니콜라스 샤프의 맹우였고 프로비던스 아일랜드 컴퍼니의 사략선장이었지. 나도 토머스를 아주 잘 알았네. 1년 전, 로렌스가 다시 카리브 해에 나타났어. 알고 보니 잭맨이 그의 밑에서 일하고 있더군. 명심하고, 항상 경계하게!";
			link.l1 = "그러니까 잭맨의 편지에 언급된 그 수수께끼의 '보스'가 로렌스 벨트로프였군... 좋아, 그 이름 기억해 두지.";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "한 가지 더 있어. 이상한 게 기억나네. 블레이즈가 예전에 버려진 스페인 금광 얘기를 하면서, 그 금을 샤프타운에 투자할 거라고 했었지. 그런데 그의 여동생이 부처 선장과 함께 도망친 뒤로 금광의 지도가 사라졌어. 혹시 우리 광산 얘기였던 걸까?\n뭐, 너무 오래전 일이라 별 의미는 없지... 자네와 나는 이제 평의회 문제를 해결해야 해. 파편 다섯 개는 모두 모았나?";
			link.l1 = "그래. 이 네 명이야: 네이선리얼, 타이렉스, 말로우, 그리고 바르바존. 모두 동의했어.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "좋아. 선출하는 데 아무 문제 없을 거라 확신해 "+sTemp+" 카리브 해적단의 수장으로서, 즉시 평의회 소집을 준비하겠소.";
			link.l1 = "그러면 얀, 이제 모든 문제가 통제되고 있다고 봐도 되겠나? 네이선리얼은 마룬 타운에 있고, 잭맨은 죽었으며, 형제단도 새 우두머리를 얻었지... 어쩌면 이제 우리가 처음 시작했던 곳, 그러니까 토르투가를 다시 차지할 때가 온 것 아닌가?";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "기억나. "+pchar.name+", 하지만 우리는 조금 더 때를 기다려야 해. 게다가 샤프의 유산 정리 기한도 얼마 남지 않았으니, 그 문제는 알다시피 정말로 처리해야 할 일이야.";
			link.l1 = "상속에 뭐가 문제야? 지도 두 조각 다 가지고 있잖아. 그냥 그걸 내보이면 끝나는 거 아냐...";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+", 요즘은 섬을 아무에게나 내주는 법이 없다는 걸 장담하오. 유언장의 모든 조항을 충족한 정당한 상속인에게조차도 말이오. 영국 당국이 이 섬을 얼마나 탐내는지 나도 잘 알고 있소.\n도일 대령이 이미 자기네 영국 땅이라고 여기는 이 섬을 우리가 빼앗아가는 걸 가만히 보고만 있진 않을 거요. 그리고 우리 둘 다 당분간은 그림자 속에 머무르는 게 좋겠소.";
			link.l1 = "그래서 어쩌자는 거지?";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "포트 로얄로 가서 알버트 록슬리라는 남자를 찾아라. 그자는 카리브 해 전체에서 가장 뛰어난 변호사다. 온갖 수상한 일에 능숙해져서, 터무니없는 보수만 주면 무슨 일이든 맡을 거다. 식욕도 왕성하지만, 그만한 값어치는 한다.";
			link.l1 = "샤프의 유언장에 어떤 함정이라도 있을 거라 생각해?";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "나는 그렇게 생각하는 게 아니라 확신하고 있네. 관료들과 거래를 해본 적 있나? 그들이 뭔가를 원하면, 영혼까지 쥐어짜고, 잘못 찍힌 쉼표 하나까지 꼬집어내며, 모든 걸 자기들 입맛대로 해석해서 결국 널 눈먼 새끼 고양이처럼 벌거벗겨 놓을 걸세.\n그래서 변호사라는 직업이 생긴 거야. 그들은 관료들의 무기, 즉 말장난과 잉크, 꼬투리 잡기로 맞서 싸우지. 그러니 자네는 록슬리에게 가서 우리 이익을 지켜줄 수 있도록 그를 고용하게. 나는 선거 문제를 처리하고 올 테니.";
			link.l1 = "좋아. 이제 포트 로얄로 간다. 평의회가 모여서 선거를 치르려면 얼마나 걸릴까?";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "열흘이다. 그러니 나를 블루웰드에서 그보다 일찍 찾으려고 애쓰지 마라.";
			link.l1 = "알겠어. 그럼, 얀, 이따가 보자!";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+" 따뜻한 안부를 전합니다. 언제든 이슬라 테소로의 저택에서 당신을 반갑게 맞이할 것이라 하셨습니다. 기회가 된다면 꼭 찾아가 보시기 바랍니다.";
			link.l1 = "확실히 하기 위해 "+sTemp+" 새 거처를 떠나지 않을 테니, 우리 둘에겐 할 일이 좀 남았군, 얀.";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "이미 록슬리를 다녀온 모양이군...";
			link.l1 = "그래, 만났어. 우리 사건을 맡아주긴 했지만, 보수로 금을 한 더미나 요구하더군. "+sTemp+" 선불로 두블룬을 줘야 해. 선불이야! 그리고 헬렌의 권리 증명 결과에 따라 더 많이 지불해야 할 거야. 그 자가 말하길, 금액이 두 배, 세 배로 뛸 수도 있다더군.";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "하! 뭐, 그 늙은 여우가 그 정도는 할 줄 알았지. 하이에나처럼 멀리서도 먹잇감 냄새는 귀신같이 맡으니까. 물론, 우리가 말하는 건 섬 전체야. 알베르가 몇 백 정도는 달라고 안 할 리가 없지. 그러니 총액은 아마 천오백 골드쯤 될 거야...\n";
			link.l1 = "얀, 그건 엄청난 돈이야!";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "무슨 말을 하려는지 알겠어. 네가 멍청한 놈처럼 그 모든 돈을 네 주머니에서 내는 게 아니라는 것도 동의하지. 하지만 유감스럽게도, 지금은 그만한 금화를 쌓아둔 게 없어. 이런 지출을 예상하긴 했지만, 한 악당의 개입 때문에 모든 게 망가졌지.";
			link.l1 = "무슨 소리를 하는 거야?";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "들어봐. 아마 이미 알고 있겠지만, 우리 정착지는 반쯤만 합법적이야. 영국군이 여기 주둔하고 있고, 우리는 그들에게 마호가니를 좋은 값에 공급하지. 그런데 아주 무겁고 단단한 목재가 있어. 바로 리그넘 바이테, 너도 철목이라고 들어봤을 거야.\n이건 드물고, 경화강으로도 가공하기 힘들지. 옛날 마야-이차 사람들이 그 끔찍한 곤봉을 이 나무로 만들었다고들 해. 철목은 공개 시장에서는 살 수 없고, 밀수품은 은값만큼 비싸.\n도일의 부하들이 가끔 와서 우리가 가공한 걸 전부 헐값에 사가. 그래도 나는 항상 내 필요를 위해 조금씩 남겨두지.";
			link.l1 = "이 나무에 대해 들은 적이 있소. 머스킷 총알도 그 기름진 나무에 타르처럼 박혀버린다 하더군! 그 튼튼함은 강철 기계의 기어를 만들어도 될 만큼이라오.";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "기어에 대해서는 좀 뻥을 치고 있지만, 나머지는 딱 맞아. 그래서 비용을 예상해서 철목을 잔뜩 준비해뒀는데, 며칠 전에 어떤 놈이 내 창고를 싹 비워버렸지. 우리 중 한 놈이야, 그건 확실해. 누군지 짐작은 가지만, 확실히 말할 수는 없어.";
			link.l1 = "쥐들은 짓밟아야지! 누구를 의심하는 거냐?";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "폴 몰리건. 그의 동인도 '오이스터'호는 어제 바베이도스로 떠났어. 나는 그 배의 화물창을 확인할 기회가 없었지. 하지만 그는 어차피 브리지타운에 철목을 가져오진 않을 거야. 윌러비 경이 그곳에 엄격한 세관원들을 두고 있고, 철목은 영국 해군에게 전략적으로 중요한 원자재니까.\n정말로 내 철목을 가지고 있다면, 브리지타운에 도착하기 전에 팔아치울 거야. 네가 몰리건을 가로채서 화물창을 조사할 수만 있다면 좋을 텐데!..";
			link.l1 = "그가 어제 브리지타운으로 떠났다고 했나? 아직 모든 게 끝난 건 아니야. 내가 그를 따라잡아 보겠어.";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "몰리건이 쥐새끼라면 어떻게 해야 할지 알겠지. 하지만 먼저 그의 의뢰인의 이름을 알아내도록 해. 그러고 나서 네가 직접 그 의뢰인에게 화물을 넘기든, 아니면 내게 다시 가져오든 상관없다.\n‘오이스터’도 블루웰드로 가져와라. 아주 좋은 배니까 내가 직접 쓰려고 개조할 생각이다. 너도 원하는 건 전리품으로 챙겨도 된다... 그리고 만약 몰리건이 범인이 아니라면... 아니, 분명히 내 철목을 훔친 쥐새끼는 몰리건일 거라 확신한다.";
			link.l1 = "시간을 잘 활용하겠어!";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "네가 철목을 직접 팔면, 록슬리 몫으로 금화 1,500두블룬을 따로 떼어 두고 나머지는 반으로 나누자. 이 정도는 믿어도 되겠지?";
			link.l1 = "물론이지. 나는 쥐가 아니야.";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "의심하지 않소. 행운을 빌겠소, "+pchar.name+"! 이번에는 그대에게 미소를 짓길 바라오.";
			link.l1 = "감사합니다. 나중에 봐요!";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "알고 있었지. 그의 선창에 얼마나 있었나?";
			link.l1 = "찾았어 "+FindRussianQtyString(sti(npchar.quest.bakaut))+" 'Oyster'호에서.";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "이런! 내 창고에 그렇게 많은 걸 가져본 적은 없었지. 누가 자기 손으로 재산을 움켜쥐었나 좀 보라고. 고맙네, "+pchar.name+", 너는 절대 나를 실망시키지 않는구나. 물건은 바로 팔겠어, 이미 사겠다는 사람이 있어. 내일 돈을 준비해두마.";
				link.l1 = "알겠소. 더 이상 방해하지 않겠소. 내일 보세.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "그래, 이제 정말 지긋지긋하군. 이 쥐새끼! 고맙다, "+pchar.name+", 넌 절대 나를 실망시키지 않는구나. 바로 물건을 팔겠네, 이미 사겠다는 사람이 있어. 내일 돈을 준비해두겠네.";
				link.l1 = "좋아. 더 이상 방해하지 않을게. 내일 보자.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "아마 이미 누군가에게 화물 일부를 팔아넘겼을 거야, 원래 더 많았어야 했거든. 하지만 큰 문제는 아니야, 대부분은 되찾았으니까. 고마워, "+pchar.name+", 바로 물건을 팔겠소, 이미 사는 사람이 있거든. 내일 돈을 드리겠소.";
				link.l1 = "알겠소. 더 이상 방해하지 않겠소. 내일 보세.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "젠장, 그 자식이 벌써 화물 중 괜찮은 몫을 팔아치웠군... 아, 아쉽네. 뭐, 어쩔 수 없지. 내가 가진 건 내가 팔 거야, 이미 사겠다는 사람이 있어. 내일이면 돈 받을 거다.";
				link.l1 = "알겠소. 더 이상 방해하지 않겠소. 내일 보세.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "젠장, 이거 참 한심하군! 그 자식이 벌써 화물의 절반 이상을 팔아치웠다니... 아, 정말 아깝네. 뭐, 어쩔 수 없지. 내가 가진 건 내가 팔지, 이미 사겠다는 사람도 찾았으니까. 내일이면 돈 받을 거야.";
				link.l1 = "알겠소. 더 이상 방해하지 않겠소. 내일 보세.";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "이런, 난 정말 운이 없네. 그가 거의 모든 걸 팔아버렸어... 자, 이 철목은 네가 가져. "+pchar.name+", 네 마음대로 해. 이제 내 돈벌이 희망은 너 하나뿐이야.";
			link.l1 = "알겠어. 좋아, 내가 직접 찾아볼게. 이번이 처음도 아니니까... 잘 있어, 얀.";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "잠깐! '오이스터'를 잡았어?";
			if (iUst == 1)
			{
				link.l1 = "네. 그녀는 지금 항구에 있어요. 당신이 부탁한 대로 내가 정박시켜 놨어요.";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "아니. 전투 중에 배가 너무 심하게 손상되어서 내가 침몰시켜야 했어.";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "안타깝군. 하지만 어쩔 수 없지. 나중에 보자, "+pchar.name+"!";
			link.l1 = "잘 가, 얀.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "대단하군! 이 멋진 배를 제대로 장비해 주겠어. 그리고 나중에 약속한 대로 얼마든지 잠깐 빌려 타도 돼. 두 달쯤 지나면 준비가 끝날 것 같아.";
			link.l1 = "좋아. 이런 배는 가끔 정말 쓸모가 있겠군... 나중에 보자, 얀!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "받았소 "+iTemp+" 그 돈으로 동전이네. 변호사 몫으로 천오백, 거기에 네가 받을 두블룽 몫이 더 있지 - "+idlt+". 자, 여기 있소.";
				link.l1 = "칭찬할 만하군! 이제 나는 쉽게 록슬리로 떠날 수 있겠어.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "그걸로 1,500두블룬을 받았어. 변호사 비용으로 딱 맞는 금액이지. 자, 여기 있다.";
				link.l1 = "환상적이군. 이제 록슬리로 갈 수 있겠어.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "받았소 "+iTemp+" 그걸 위해 더블룬을 주지. 여기 있다. 나머지는 네가 직접 파내야 할 거야.";
			link.l1 = "그래, 혼자라면 혼자서라도 가지. 좋아, 이제 록슬리를 만나러 간다.";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "어때? 흥미로운데. 그리고 그 네덜란드 녀석은 그걸 위해 얼마를 내겠다고 하던가?";
			link.l1 = "한 사람당 40두블론이다.";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "이런! 내 거래처들은 더 적게 주는데...";
			link.l1 = "전체적으로, 록슬리에게서 금화 이천 닢을 받았고\n "+sti(npchar.quest.bakaut_sum)*2+" 그 위에 두블론까지.";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "좋소. 그럼 반반씩 나누도록 하세.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // дублоны в кармане
				link.l1 = "여기 있어. 내가 가져왔어 "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "두블룬을 배에 두고 왔어. 금방 다녀올 테니 잠깐만 기다려.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "좋아. 얼마나 가져왔지?";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // дублоны в кармане
				link.l1 = "여기 있어. 내가 가져왔어 "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "내 기억이 왜 이러지! 이제 이 럼 장난도 그만해야겠군. 또다시 내 상자에 두블룬을 두고 왔잖아. 금방 다녀와서 가져올게.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.bakaut_pay));
			Log_Info("You have given "+sti(npchar.quest.bakaut_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "수고했네, "+pchar.name+"! 다시 한 번, 너와 엮이길 잘했다는 생각이 드는군.";
				link.l1 = "노력하고 있어, 얀...";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "좋아. 나머지도 가져올 거야? "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+" 나중에 두블룬 줄 거야?";
				link.l1 = "그래. 그렇게 많은 금덩이를 한 번에 다 옮길 수는 없었지.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "그래서, "+pchar.name+", 내 두블론은 잘 있나?";
			link.l1 = "내가 금화를 좀 더 줄 용의가 있소.";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "제안이 하나 있소. 자네가 이익이 되는 구매자를 찾았으니, 내가 철목을 좀 팔 수 있겠군. 예전에는 한 통에 삼십 두블론씩 받았지. 원한다면 그 가격에 자네에게 팔겠소. 다른 놈들보다는 자네에게 파는 게 낫겠군.";
			link.l1 = "철목을 얼마나 팔 수 있지?";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "나는 한 번에 많이 쌓아두는 걸 피하지. 몰리건네는 예외였어. 당국이 지역 암시장 소식을 좋아할 리 없으니까. 그래서 이렇게 하자고: 매달 14일과 24일에 너를 위해 철목 25개씩 따로 챙겨둘게.\n사고 싶으면 750두블룬을 가져와서 전부 가져가. 그날 안 오면 다른 손님한테 팔 거야. 이렇게 하면 한 달에 50개씩 받을 수 있지. 어때, 거래할래?";
			link.l1 = "거래 성사됐군, 얀! 해보자고. 이제 난 슬슬 가봐야겠어...";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "아, 그럼 그 사람이 아니었거나 이미 철목을 팔아버린 모양이군... 안타깝네. 뭐, 이제 변호사 비용을 마련할 수 있는 희망은 너뿐이야.";
			link.l1 = "내가 그 책임을 질 용의가 있소. 이런 일, 이번이 처음이 아니오.";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "그런가? 흥미롭군. 자, 물어봐. 누구에 대해 이야기하고 싶나?";
			link.l1 = "한 여자에 대하여. 그녀의 이름은... 제시카 로즈였소.";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "흠. 우리 해적단의 새 우두머리가 그녀에 대해 말해줬나?";
			link.l1 = "그도 그랬지. 하지만 나는 그녀에 대해 세인트 존스의 늙은 형리 베이커에게서 들었어. 그 자가 바로 버처 선장을 처형한 사람이야.";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "좋아. 흠. 그래, 내가 제시카를 마지막으로 본 지 벌써 이십 년이 넘었지. 그녀에 대해 뭘 알고 있나?";
			link.l1 = "음, 그녀가 어떻게 부처 선장과 함께하게 되었고 둘이 해적질을 했는지는 알고 있지. 그가 비트리스 때문에 그녀를 떠난 것도 알고 있어. 나중에 그녀는 조슈아 리드비터, 일명 마스크라는 자의 도움을 받아 그 일에 대해 복수했지...";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "나 또한 자네가, 얀, 솔직히 말해도 된다면, 제시카에게 관심이 있었던 걸 알고 있네. 바로 그 이유로 내가 자네를 찾아온 것이지. 제시카는 내 수색에서 중요한 인물이야. 내가 알기로는, 바로 그녀가 질투심에 베아트리스 샤프를 살해했네.";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "그래, 너 참 많이도 아는구나. 맞아, 나 정말로 제스에게 구애했었지. 하지만 놀랄 일도 아니었어. 그때 이슬라 테소로의 해적들은 두 부류로 나뉘었거든. 베아트리스를 범하고 싶어 하는 놈들이랑 제시카를 원했던 놈들로 말이야.\n그녀가 아직도 기억나... 정말 아름다웠지, 아주 아름다웠어!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "그 여자는 특별했지... 그리고 제스가 비트리스를 죽였을 가능성도 꽤 높아. 도살자가 '넵튠'에서 그녀를 쫓아낸 뒤로, 제스는 아마 그와 비트리스에게 복수할 생각밖에 없었을 거야. 그런데, 도살자가 제시카를 어떻게 처리했는지 알고 있나?";
			link.l1 = "아니. 그가 그냥 그녀를 바베이도스에 내려주었거나, 아니면 몸값을 요구하려고 잡아둔 거겠지.";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "두 번째야. 그는 그녀를 믿을 수 없을 만큼 모욕했지. 그냥 그녀를 선실에 가둬두고 바베이도스로 데려가서는, 그녀의 아버지 올리버 로즈와 흥정을 시작했어. 그리고 결국 그녀가 그를 위해 해준 모든 일에도 불구하고, 한 뭉치의 두블룬에 그녀를 팔아넘겼지...";
			link.l1 = "흠. 해적들이 조슈아 리드비터의 '네프튠'을 빼앗았을 때, 나는 부처가 그녀의 명예를 지켰다고 생각했는데...";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "그것도 사실이지. 하지만 그녀는 그에게 후한 보상도 주었어. 제시카는 그 건달이 방탕과 다혈질로 스스로 만든 위기에서 여러 번 구해줬지, 그 비참한 목숨을 살려준 셈이야. 사실, 그가 번영하는 해적으로서 영광을 누릴 수 있었던 것도 전적으로 그녀 덕분이었어.";
			link.l1 = "그래, 그래, 그 녀석의 '붉은 부적' 말이지. 나도 들었어. 도살자가 제스에서 죽자마자, 녀석 운도 같이 끝장났다고들 하더군...";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "물론이지. 제시카가 없으니 그는 그냥 또 하나의 평범한 해적일 뿐이었어, 아무리 무모하게 용감하다고 해도 말이야. 하지만 제시카는 그의 곁에 없었지. 위험한 작전을 모두 계획해준 것도, 언제나 그의 곁에서 칼을 빼들어준 것도 제시카였으니까.\n물론, 베아트리스도 착한 아가씨는 아니었지만, 제스와는 비교가 안 됐어. 베아의 매력은 완전히 달랐지... 그녀는 도살자와 엮이는 실수를 저질렀어.";
			link.l1 = "그 얘기 어디선가 전에 들은 적이 있는데...";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "모든 해적들이 그렇게 생각했지, 그녀의 오빠 블레이즈 샤프도 마찬가지였어. 그는 도살자를 도저히 참을 수 없었지... 하지만 다시 제시카 이야기로 돌아가자. 그녀가 '넵튠'에 있을 때는 감히 그녀를 생각조차 못 했어. 그녀는 절대 사랑하는 선장을 떠나지 않았을 테니까. 그런데 도살자가 그렇게 비열하게 그녀를 내쫓았을 때...\n나는 바베이도스에 도착해서 그녀와 친구가 되었어. 그녀에게 쉽지 않은 일이었지. 그녀는 바다와 위험한 모험을 사랑했으니까. 그 지루한 식민지 생활은 그녀를 죽이고 있었어. 게다가 '넵튠'에서 일할 때 카리브 해에서 악명이 높아졌고, 브리지타운 사람들은 그녀를 도살자의 공범으로 여길 만한 이유가 있었지...";
			link.l1 = "하지만 그놈들은 아무것도 증명하지 못했지...";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "아니. 하지만 아무도 그녀와 엮이고 싶어하지 않았지. 브리지타운에서의 신분에도 불구하고, 그녀는 저주받은 존재로 여겨졌거든. 아마 그곳에서 제시카와 반 시간 넘게 함께한 남자는 나뿐이었을 거야.\n나는 그녀에게 웨스트 메인으로 함께 가서 새로운 삶을 시작하자고 제안했어. 그녀가 늘 꿈꿔온 삶, 바다와 배, 항해와 모험 말이야. 그때 나는 이미 블루웰드에 큰 사업을 차려놨고, 그 불한당 부처보다 백 배는 더 나은 걸 제시카에게 줄 수 있었지. 하지만 제스는 크게 상처받았어. 부처의 배신과 그 후의 냉대, 그걸 용서하지 못했지. 그리고 그때도 아직 부처를 향한 감정이 남아 있었던 것 같아... 내가 아무리 애써도 그녀는 과거를 잊지 못했어. 복수에 사로잡혀 있었지.";
			link.l1 = "그래, 나도 그녀가 부럽지 않아. 불쌍한 아가씨야...";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "나도 그녀에 대해 같은 감정을 느꼈다. 나중에 그녀는 고대 인디언의 종교와 의식에 관심을 갖게 되었다. 이 일은 유카탄 정글 깊은 곳에서 인디언 마법사가 붙잡혀 현지 플랜테이션으로 끌려온 뒤에 일어났다. 제시카는 그를 사들여 자신의 영지에 집을 마련해주었다.  
그녀는 마법사와 많은 시간을 보냈고, 모두 마법적인 인디언 의식에 대한 역사적 관심 때문이라고 말했다. 브리지타운 사람들은 걱정하기 시작했고, 특히 현지 목사가 그랬다. 사실 그는 제시카에게 친절했던 몇 안 되는 이들 중 하나였다.  
목사는 자주 그녀와 대화하며 마법사를 내보내라고 설득했고, 위험과 종교재판을 경고했지만, 제시카를 겁주려는 시도는 헛수고였다. 어느 날 밤, 낯선 이들이 마법사의 집에 침입해 그를 살해했다.  
그날 밤, 두 남자가 제시카의 침실로 쳐들어왔지만, 그들에게는 좋지 않은 일이 벌어졌다—브리지타운 사람들 중 아무도 제스가 불꽃칼을 얼마나 잘 다루는지 몰랐다. 그녀는 dos자 그대로 그들을 산산조각 냈다.";
			link.l1 = "그래, 물론이지... 그 무모한 여자 녀석!";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "그 일 이후로 마을 전체가 그녀를 두려워하게 되었지. \n그리고 그때 가면이 나타났어. 둘은 꽤 빨리 서로를 찾았지.";
			link.l1 = "기록에 따르면, 마스크는 '네프튠'의 전 선장이었던 조슈아 리드비터라고 하네...";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "나는 그 사실을 훨씬 나중에야 알게 되었지. 가면이 도착한 지 일주일 뒤, 제스는 짐을 챙기고 나에게 작별 인사를 한 뒤 군함을 타고 미지의 바다로 떠나버렸어. 그녀는 다시 돌아오지 않았지... 비트리스가 이슬라 테소로로 돌아오지 않은 것처럼 말이야.\n그 후 얼마 지나지 않아 부처가 세인트 존스에서 교수형을 당했어. 그를 거기로 데려간 건 바로 가면이었지. 하지만 그는 부처보다 하루 더 살았을 뿐이야.";
			link.l1 = "그래... 우리 스티븐 도드슨이 품격을 보여줬지...";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "그래, 나도 그렇게 들었어. 그는 베아트리스를 위해 복수했지... 그리고 그게 제시카의 이야기의 끝이야; 그녀는 무인도 어딘가에서 부처의 해적들과의 충돌 끝에 세상을 떠났어. 그곳이 어디인지는 아무도 몰라. 부처도 죽었고, 잭맨과 행맨도 마찬가지야.";
			link.l1 = "그건 네가 잘못 알고 있는 거야, 얀. 부처는 살아 있어.";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = " 뭐!? 그럴 리가! 그는 교수형당했잖아!";
			link.l1 = "레이먼드 베이커의 증언을 읽어 봐. 어떤 이야기보다 더 흥미로우니까.";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "보여 줘...(읽으며) 흠. 믿을 수가 없군! 처형이 연극이었다니!";
			link.l1 = "교활하지? 하지만 그게 다가 아니야. 너 도살자를 알지. 다만 지금 그가 누군지는 모르는 거야.";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "그래? 그런데 그게 누구야?";
			link.l1 = "포트 로열에서 온 로렌스 벨트로프. 잭맨 뒤에 서 있는 바로 그 수수께끼의 그림자, 광산의 주인이지. 나는 베이커를 통해 알게 되었고, 베이커는 마스크에게서 알아냈어.";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "세상에 이런 젠장! 결국 그 자식이 모든 걸 꾸민 거였어? 좋아... 우리도 Butcher로 가자. 저 골칫덩어리를 어떻게 끌어내릴지 고민해 보지. 쉽진 않겠지만, 영국 당국의 보호를 항상 받고 있으니까.";
			link.l1 = "그 자의 때도 올 거야, 얀. 곧 그놈도 자기 보스운이랑 쿼터마스터를 만나게 되겠지. 좋아, 이야기 고마워. 이제 난 가봐야겠다.";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "지금 어디로 가는 중이야?";
			link.l1 = "어딘가의 섬으로. 제스와 비트리스가 죽고, 마스크가 부처-벨트로프를 덮쳤던 그곳과 같은 장소라고 생각해. 헬렌이 샤프 가문의 사람이라는 증거가 필요하고, 그걸 그곳에서 찾을 수 있길 바라고 있어.";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "좋아. 그러니까, "+pchar.name+" , 행운을 빌어. 돌아오면 전부 이야기해 줘.";
			link.l1 = "알겠어. 나중에 보자, 얀!";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "잘했어, "+pchar.name+". 그대는 불가능을 해냈소. 우리 해안의 형제단의 모든 남작들이 그대에게 빚을 졌소.";
			link.l1 = "그래, 승리로 가는 길은 좁았지. 미리 이렇게까지 견뎌야 할 줄 알았다면...";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "엘렌은 어때? 무슨 계획을 세우고 있지?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "그녀는 내 배에서 나와 함께 지내고 있어. 이제는 평범한 장교가 아니야. 섬의 통제권은 해적 연맹의 우두머리에게 넘어가고, 그녀가 받는 건 임대료뿐이지. 그건 헬렌이 스스로 결정한 일이야.";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "그녀는 자신이 직접 남작령을 차지하려고 이슬라 테소로로 떠났다.";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "그래, "+pchar.name+"... 축하하오! 많은 이들이 그대처럼 되고 싶어 꿈꿔왔지. 헬렌이 자신에게 어울리는 사내를 선택했다니 나도 기쁘오. 그녀의 평생 동반자가 될 더 나은 후보는 그대밖에 없을 것이오.";
			link.l1 = "고마워, 얀! 이제 토르투가와 르바쇠르에 대한 대화를 다시 이어가고 싶어.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "고마워, 얀!";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "훌륭하군. 그녀라면 이 자격이 충분하지. 이제 새로운 해적단 수장이 그녀가 일 처리하는 데 도움을 줄 거라 생각하네. 그녀는 재능 있고 똑똑한 아가씨라 뭐든 금방 익히고 배울 수 있지. 고맙네, "+pchar.name+"! 헬렌은 내게 딸과도 같은 아이야, 그리고 이렇게 멋진 미래가 그녀 앞에 펼쳐졌다는 사실에 정말 기쁘구나.";
			link.l1 = "천만에, 얀... 아무튼, 토르투가와 르바쇠르에 대한 이야기로 돌아가고 싶네.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "천만에, Jan.";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "네가 없는 동안, "+sTemp+" 그리고 나는 이미 그 문제에 대해 논의했고, 르바쇠르를 처리하는 데 있어 공통된 의견에 도달했네. 이슬라 테소로로 가서 우리 새로운 수장과 이야기하게. 그가 우리 계획의 세부 사항을 알려줄 것이고, 줄 수 있는 모든 도움을 제공해 줄 걸세.";
			link.l1 = "드디어 화약 냄새를 맡을 수 있겠군! 시간 낭비할 틈 없어, 바로 이슬라 테소로로 간다!";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+", 잠깐만. 헬렌과 브레서런 일에 도움을 준 대가로 선물을 몇 가지 준비했네. 첫 번째는 극동에서 온 사라센의 마법 부적이야. 이 부적의 힘은 배에서의 규율을 강화해 주지. 내가 직접 확인했으니 믿어도 돼. 자, 받아.";
			link.l1 = "감사합니다!";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("You've received the 'Janissary' amulet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "두 번째 것은 그저 지난 모험의 기념품일 뿐이오. 내가 평의회를 설득해서 저 돌 조각을 바람에 던지는 어리석은 전통을 버리게 했소. 이제 더 이상 필요 없지. 자네에게 주겠소. 어쩌면 자네가 쓸 데가 있을지도 모르지.";
			link.l1 = "조각들의 용도? 흠. 잘 모르겠네... 하지만 기념품으로는 정말 고맙지!";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("You've received five ornamental pattern fragments");
			dialog.text = "그래도 네 친구를 잊지 마라, "+pchar.name+". 블루웰드에 닻을 내리거든 내 집에 들르시오. 같이 앉아 럼주 한잔 합시다. 당신을 언제나 반갑게 맞이하오.";
			link.l1 = "확실히 그렇지, 얀. 이제 우리도 추억할 만한 일이 생겼구나, 안 그래? 하하! 아무튼, 난 이만 가봐야겠다.";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "행운을 빌어요, "+pchar.name+"!";
			link.l1 = "또 보자...";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "그래... 정말 우리 계획이 완전히 무너진 것 같군. 이제 우리가 원하던 사람을 해적단의 수장 자리에 앉힐 수 없게 됐어. 잭맨이 죽은 건 잘된 일이지만, 아쉽게도 내 계획은 이제 물거품이야. 해적단의 수장은 평소처럼 선출해야겠지, 그리고 신만이 앞으로 어떤 일이 벌어질지 아실 테니...\n";
			link.l1 = "안타깝군. 정말 유감이야. 그리고 이대로라면 헬렌은 유산도 못 받게 생겼네.";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "그래, "+pchar.name+". 그리고 나도 정말 토르투가를 차지하는 데 도와주고 싶어, 정말이야. 하지만 지금은 어떻게 해야 할지조차 모르겠어. 아마 내가 도울 수 있는 일은 아무것도 없을 거야. 이제 네 힘과 싸우는 능력만 믿고 가야 할 것 같아.";
			link.l1 = "다른 선택지는 없는 것 같군... 좋아, 얀, 가서 다음에 뭘 할지 생각해 보겠네. 이따 보세...";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "들러라, "+pchar.name+". 나는 항상 당신을 보게 되어 기쁩니다.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "하지만 유감스럽게도 이제 와서 할 수 있는 일은 없네. 이슬라 테소로는 공식적으로 영국 왕실의 관할로 넘어갔어. 지금은 그곳에 주둔군까지 배치되어 있지. 이것은 형제단에게 큰 타격이야, 두고 보건대 우리는 이 충격에서 회복하지 못할 것 같네.";
			link.l1 = "정말 끔찍하군... 아, 내가 좀 더 빨리 행동했어야 했는데. 그랬다면 모든 게 잘 풀렸을 거야. 알겠어, 얀, 다음에 뭘 해야 할지 생각해볼게. 나중에 보자...";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "들러라, "+pchar.name+". 당신을 다시 보게 되어 언제나 반갑소.";
			link.l1 = "...";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "그래... 우리 정말로 참혹한 패배를 당했지. 그리고 가장 억울한 건, 우리가 정말로 승리까지 한 걸음 남았다는 거야. 이런 젠장! 어떻게 이런 일이 벌어진 거냐, 응,\n "+pchar.name+"? 그렇게 애썼는데, 그렇게 많은 걸 했는데, 결국... 운이 이렇게 나쁘다니!";
			link.l1 = "이 모든 게 내 잘못이야. 내가 더 빨랐어야 했는데. 내 탓에 헬렌은 상속을 잃게 생겼어. 그리고 토르투가 계획도 절대 이루어지지 않을 거야.";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "좋아, 상관없어. 내 창고에 125개가 있어. 가격은 기억하다시피 한 개당 3,150이야.";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "좋아, 거래하자. 자, 여기 있다. 3150두블룬이네.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "운도 참 없군. 내 돈을 배에 두고 왔어. 금방 가지고 올게.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "좋아, 상관없어. 내 창고에 25개가 있지. 가격은 기억하다시피 한 개당 30두블룬이야.";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "좋아, 거래지. 자, 여기 있다. 여기 750두블룬이야.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "운도 참 없군. 내 돈을 배에 두고 왔어. 금방 가지고 올게.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "얀, 철목 선적량을 늘릴 수 있을까?";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "얀, 내가 금화 삼천 닢을 모아왔어. 자, 이걸 우리 기생충들에게 선물로 줘도 되겠군. 오늘은 녀석들 신나는 하루가 되겠지.";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("You have given 750 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "칭찬할 만하군. 내 부하들에게 철목을 네 배로 옮기라고 명령하겠다.";
			link.l1 = "감사합니다!";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "더 사고 싶으면 2주 후에 다시 오시오. 그때쯤이면 새로 한 번 더 만들어 놓겠소.";
			link.l1 = "알겠어, 얀. 다음에 또 보자!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "철목을 마음에 들어 하니 기쁘군, "+sStr+". 선적을 늘리는 건 문제없지만, 아시다시피 함정이 있소. 물량이 많아지면 자취가 남아 원치 않는 관심, 특히 영국 당국의 눈길을 끌 수 있지. 하지만 믿을 만한 인원, 신뢰할 귀, 그리고 관저 안에서 우리를 그림자 속에 숨겨줄 사람들만 더한다면, 모든 게 해결될 수 있소. 물론 값싸진 않소 – 시 재무관과 영국의 요구를 피해가려면 삼천 두블룬이 필요하오. 그러면 다섯 배나 더 공급해 줄 수 있소. 어찌하시겠소?";
				link.l1 = "삼천 두블론이라고? 얀, 이건 대낮에 강도질이잖아! 비용을 좀 더 줄일 수는 없겠어? 이렇게 터무니없는 돈을 들이지 않고도 해결할 방법이 있지 않을까?";
				link.l1.go = "UpgradeBakaut_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "좋은 생각이오. 하지만 이런 대량 거래를 하려면 좀 더 경험과 실력이 필요하오. 서두르면 이익보다 위험이 더 크지. 이렇게 합시다. 경험을 좀 더 쌓고, 대량 거래를 할 준비가 되면 다시 오시오. 그때 제대로 이야기해 보세.";
				link.l1 = "흠... 알겠네. 이 이야기는 나중에 다시 하세.";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "아아, "+pchar.name+", 요즘 평화의 대가는 이런 것이지 - 가발과 제복을 입은 양반들의 욕심은 날이 갈수록 커져만 가네. 그들에게는 상자 속에서 딸랑거리는 두블론만큼 유혹적인 것도 없지. 위로가 될지 모르겠지만, 앞으로 모든 화물에 대해 15퍼센트 할인은 보장하겠네.";
			link.l1 = "저런 놈들, 제기랄! 그런 돈을 요구하다니! 저렇게 탐욕스러우면 왕의 보물을 사야지, 입 다물라고 흥정할 게 아니잖아! 얀, 우리... 누가 이 제도에서 진짜 힘인지 보여줘야 하지 않겠어?";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "my friend";
			if (startHeroType == 2) sStr = "my friend";
			if (startHeroType == 3) sStr = "my friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "하! 기백이 대단하군, "+sStr+"! 하지만 지금 영국 전체를 적으로 돌리는 건 내게 이득이 아니고, 나도 예전만큼 젊지 않지. 그냥 이 피를 빠는 놈들한테 돈이나 주고 조용히 있게 두자고 - 우리도 할 일이 따로 있으니까. 필요한 돈을 모으면, 쓸데없는 질문 없이 길이 열릴 거다!\n";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "좋아, 얀, 네 말에 넘어갔군. 어쩔 수 없으니 그렇게 하지. 여기 네가 원하는 삼천 두블룬이다. 하지만 명심해라. 내가 이 구두쇠 놈들 밥줄을 영원히 대줄 생각은 없으니.";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "악마가 데려가라, 얀! 정말 다른 방법이 없다고 생각하나? 좋아. 그 두블룬을 찾아보지. 하지만 지금은 그런 돈이 없어.";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "젠장, 얀, 정말 내가 저 관리들이랑 그 귀족 아가씨들까지 먹여 살리길 바라는 거야? 지들은 의자에 앉아서 아무 일도 안 하고 돈만 요구하잖아! 난 이런 거 싫어! 내 피땀으로 저놈들 주머니 채워줄 생각 없어! 이전 조건으로 돌아가자. 그걸로 충분해.";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "이제야 제대로 되는군! 자네의 기여 덕분에 우리 사업이 순조롭게 굴러갈 거고, 그 구두쇠 놈들도 마땅한 대가를 치르게 될 거야. 이제부터는 철목 쪽은 쳐다보지도 못할 테지. 장담하는데, 곧 모든 투자를 백 배로 회수하게 될 거야.";
			link.l1 = "그러길 바라오, 얀, 정말 그러길 바라오.";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "일은 원래대로 진행될 것이니 걱정하지 마시오. 그리고 앞으로의 거래에 관해서는, 이전과 마찬가지로 매달 14일과 28일까지 철목 125통을 준비해 두겠소. 전량을 3,150 두블론에 가져가면 되오.";
			link.l1 = "이런 대화가 훨씬 마음에 드는군! 그럼, 통나무 125개지? 훌륭해, 얀. 곧 보자고, 물건 기다리고 있겠네!";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "원하시는 대로, "+sStr+". 그리고 너무 흥분하지 마라. 세상이 원래 이런 법이지.";
			link.l1 = "그래, 얀, 이 세상이 어떻게 돌아가는지 나도 알아. 그렇다고 해서 내가 이 꼴을 참아야 한다는 뜻은 아니지. 좋아, 이제 가봐야겠군.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "네가 돈을 모을 때까지 기다릴게. 네가 방법을 찾을 거라는 거 알아. 준비가 되면, 내가 돈을 들고 기다리고 있을 테니, 그때 계속하자.";
			link.l1 = "좋아.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "만나서 반갑소, "+pchar.name+". 내 사람들은 준비됐어. 셀바로 갈까?";
			link.l1 = "그래, 얀. 내 부대는 전투 준비가 되어 있다.";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "그럼 출발하자. 광산은 정글 깊숙이, 이 길을 따라가면 돼. 갈림길에서는 오른쪽으로 가. 앞으로!";
			link.l1 = "전진하라!";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "그러면, "+pchar.name+", 이제 이 작전을 어떻게 진행할지 논의할 시간이야. 이미 몇몇 미스키토 인디언들을 앞서 보내서 지역을 정찰하게 했고, 그들의 관찰을 바탕으로 행동 계획도 세웠지.";
			link.l1 = "자초지종을 말해 줘!";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "구덩이는 정글 산 아래에 있는 광산을 나타내지. 광산 입구 근처에는 캠프가 있어. 집 몇 채와 말뚝 울타리가 있고, 울타리로 이어지는 길도 있지. 저길 봐, 여기서 멀지 않은 정글 속 작은 공터로 이어져. 그곳이 바로 구덩이의 주 입구야\n그건 두 가파른 언덕 사이에 세워진 높은 돌담을 의미해. 아무도 몰래 들어가지 못하게 막는 거지. 문은 여섯 명이 지키고 있어. 별거 아니지만, 거기에 대포 두 문도 설치해 놨어. 그게 제일 큰 문제야.\n산탄 두 발만 맞아도 우리 부대 절반이 쓰러질 수 있으니, 그건 재앙이야. 정면 공격은 선택지가 아니지...";
			link.l1 = "하! 하지만 우리에겐 비장의 수가 있지 — 안으로 들어갈 수 있는 암호를 알고 있으니까...";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "맞아. 그 점을 우리에게 유리하게 활용할 거야. 하지만 지금은 내 계획 전체를 끝까지 너에게 알려줄게.";
			link.l1 = "그래, 얀. 다 듣고 있어.";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "갱으로 들어가는 또 다른 입구가 있어. 저 정글 속 길을 따라가면 되지. 그 길은 광산을 둘러싼 언덕을 돌아 작은 좁은 골짜기로 이어지는데, 그곳을 통해 안으로 들어갈 수 있어. 하지만 산적들이 높은 울타리를 세우고 경비병도 배치해 놨지. 울타리에 작은 문이 있긴 한데, 반대편에서 막아놨어.\n이제 우리가 할 일을 잘 들어. 우리는 광산의 두 번째 입구를 지키는 놈들을 처리할 거야. 우리 부대 일부는 그 자리에 남아, 통나무를 찾아서 공성추로 쓸 거고.\n우리는 다시 주 입구로 돌아가서 대포병들을 죽일 거야. 우리가 가진 암호가 두 번이나 도움이 될 거다. 그 후 양쪽에서 광산을 공격할 거야. 내가 첫 번째 돌격대를 이끌고, 네가 두 번째 돌격대를 이끌어.";
			link.l1 = "글쎄, 논리적이군. 두 전선에서 우리와 싸우게 만들자. 전진!";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "좋아, 이제 도착했군... 이 길이 도적 놈들의 장물아비에게 가는 길이야. 이제 저놈들을 어떻게 처리할지 결정해야 해. 전부 다 몰려가면 너무 수상해서 놈들이 경보를 울릴 거야.\n세 명, 그 이상은 안 돼. 소규모로 가야 의심받지 않고 가까이 접근해서 기습할 수 있어. 나는 얼굴이 너무 알려져 있어서 직접 나설 수 없어.\n그러니 네가 맡아야 해. "+pchar.name+", 자네만이 이 작전을 망치지 않고 지휘할 수 있는 유일한 사람이기 때문이오. 내가 그레고리와 머스킷병 한 명을 붙여 주겠소...";
			link.l1 = "피켓 울타리에 경비병이 몇 명 있지?";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "넷. 머스킷총병 둘, 병사 둘.";
			link.l1 = "우리가 놈들 잡을 거야...";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "너를 아니까, 나는 한 치도 의심하지 않아. 저놈들에게 다가가서 잭맨이 보냈다고 해. 암호도 알려주고. 그리고 모두가 안심하면... 상황에 맞게 행동해.";
			link.l1 = "좋아. 우리가 놈들을 긴장하게 만들어 주지.";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "행운을 빌어요, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "잘했어, "+pchar.name+"! 역시 당신이 이겼군. 이제 내 녀석들이 이쪽 갱도에서 폭풍을 일으킬 준비를 할 거다, 그리고 우리가 정문을 깨끗이 비워주지.";
			link.l1 = "또 다시 내가 직접 경비병들에게 가야 하는 건가?";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "그래, "+pchar.name+", 또 한 번이네. 나도 직접 가고 싶지만, 분명히 나를 알아볼 테니 작전 전체가 엉망이 될 거야. 적이 더 많아져서 더 위험할 거고, 무기도 잊지 마.";
			link.l1 = "내 장교들을 데리고 가겠다.";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "그래, "+pchar.name+", 또 한 번이군. 나도 직접 가고 싶지만, 분명히 나를 알아볼 테니 작전 전체가 엉망이 될 거야. 적이 더 많으니 더 위험할 거고, 무기들도 잊지 마라. 누구를 데려갈 생각이지? 네 장교들을 데려갈 건가, 아니면 지난번처럼 그레고리와 머스킷총수를 데려갈 건가?";
			link.l1 = "내 장교들을 데려가겠다.";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "그레고리랑 머스킷병을 데려가겠다.";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "좋아. 네 사람들만큼 든든한 지원군도 없지. 이제 정문 쪽으로 다시 가자. 길 기억나지?";
			link.l1 = "물론이지. 우리가 온 길로 돌아가서 왼쪽으로 계속 가, 그리고 언덕을 돌아가는 길을 따라가면 돼.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "좋아. 한 번 해냈으니 두 번째도 식은 죽 먹기겠지. 이제 우리는 정문으로 돌아갈 거야. 길 기억하지?";
			link.l1 = "물론이지. 우리가 온 길로 돌아가서, 왼쪽으로 계속 가고, 언덕을 돌아가는 길을 따라가면 돼.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "시간 낭비할 틈 없어. 진격하자!";
			link.l1 = "전진하라!";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "그래, "+pchar.name+", 마지막 지시를 잘 들어라. 문을 지키는 놈들은 아주 강해서 쉽지 않을 거다. 네 주요 목표는 문 근처에 서 있는 포수들을 죽이는 거다. 그 놈들이 살아 있으면 우리가 도와줄 수 없으니까.\n둘 다 죽고 총격을 당할 위험이 없어지면, 우리 모두가 달려가서 순식간에 놈들을 처리할 거다. 알겠나, "+pchar.name+"? 영웅 놀이하지 말고, 포수들만 죽이고 나머지는 우리에게 맡겨.";
			link.l1 = "좋아, 얀. 계획한 대로 다 해보도록 하지. 그리고 뭔가 잘못되면, 그때 가서 알아서 대처할게.";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "좋군. 신의 가호가 함께하길!";
			link.l1 = "고맙다...";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "휴! 저 개자식들 싹 쓸어버렸군... 아주 성질 더러운 놈들이었어. 저 용병들, 예전엔 정규군에서 복무했던 놈들인 게 분명해. 우리가 여기서 꽤 시끄럽게 굴었으니, 들켰을지도 몰라. 한시도 지체할 수 없어! "+pchar.name+", 이제 우리가 광산을 공격할 때다.\n나는 두 번째 입구에 있는 우리 그룹으로 돌아가겠다. 그들은 이미 울타리를 들이받을 통나무를 찾아 준비했을 거다. 너와 네 부하들은 중앙 문으로 들어가라. 우리를 반 시간 동안 기다려라, 바로 공격하지 말고...";
			link.l1 = "얀, 만약 그들이 광산에서 총소리를 들었다면 우리에겐 반 시간도 없어. 저 악당들이 방어선을 구축할 수도 있고, 아니면 곧장 중앙 문으로 와서 가진 모든 걸로 내 일행을 공격할 수도 있어...";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "젠장! 그럴 수도 있겠군. 어떻게 해야 한다고 보나?";
			link.l1 = "흠... 하! 좋은 생각이 났어! 대포다! 주위를 봐. 산탄뿐만 아니라 폭탄도 있잖아! 이제 저 도적들은 끝장이야! 왜 진작 이 생각을 못 했지?!";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "우리가 어떻게 해야 한다고 생각해?";
			link.l1 = "대포 하나만 가져가자. 하나만 있으면 훨씬 더 빠르고 효율적으로 움직일 수 있어. 그걸 안으로, 성문 너머 광산까지 굴려서 자리에 설치하자고. 놈들이 직접 공격해 오면 크게 한 방 먹일 수 있고, 머뭇거리면 우리가 그놈들 야영지를 포격하면 돼. 성문 뒤쪽에 그 야영지가 정확히 어디에 있는지 말해줄 수 있겠어?";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "야영지는 산 옆의 낮은 지대에 있다. 문을 지나면 언덕을 따라 내려가며 구불구불 이어지는 오솔길이 있다.\n야영지는 바로 이 언덕 뒤에 자리 잡고 있다.";
			link.l1 = "훌륭해! 우리가 길 꼭대기에 자리를 잡고 언덕 너머 그놈들 소굴에 폭탄 몇 개를 던지자고! 아, 녀석들이 이리저리 뛰어다니게 만들어 주지!";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "젠장, "+pchar.name+", 잘했어! 전속력으로 앞으로! 랜돌프는 네 지휘 아래 둘게, 내 최고의 대포 사수야. 그를 네 포수로 삼으면 절대 실망시키지 않을 거야. 나는 지금 내 부대로 간다.";
			link.l1 = "좋아. 네가 성문을 부술 때까지 내가 저놈들 진지를 반 시간 동안 지옥으로 쏴버리겠어.";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "제시간에 도착하도록 해볼게. 캠프에서 보자!";
			link.l1 = "거래다... 분대! 내 명령을 들어라! 대포를 새로운 위치로 옮길 준비를 해라! 화약, 폭탄, 산탄도 챙겨! 문을 지나 광산으로 간다. 앞으로, 행진!";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "휴, 우리 너무 늦은 거 아니야? "+pchar.name+"?";
			link.l1 = "얀, 젠장! 왜 이렇게 오래 걸렸어? 내 부하들이 방금 큰 피해를 입었어!";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "그 빌어먹을 나무 울타리가 생각보다 정말 튼튼하더군. 힘으로 부숴버렸지... 네가 내는 소란과 소리를 들었어. 이곳을 제대로 쓸어버린 모양이군! 완전히 불타고 있잖아!";
			link.l1 = "랜돌프가 한 짓들 말이야... 우리가 결국 백병전에 들어가기 전에 얼마나 많은 놈들을 묻었는지 네가 봤으면 좋았을 텐데!";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "카람바! 네게 모자를 벗겠군, "+pchar.name+". 잘했네! 이제 손실에 대해 말하자면... 전쟁 중엔 언제든 그런 게 있기 마련이야.";
			link.l1 = "이제 우리가 해야 할 일은 광산 내부를 소탕하는 거야. 그 안에 살아남은 자들이 숨어 있을 수도 있어.";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "우리 둘이서만 가자. 거기서 무슨 일이 벌어지는지 보자고.";
			link.l1 = "좋은 생각이야!";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "아직 광산 전체를 다 뒤진 건 아니야! 분명 여기 어딘가에 저 악당들이 더 숨어 있을 거라고 장담해!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "남은 악당은 더 이상 없는 것 같군...";
			link.l1 = "얀, 우리는 그냥 상황만 살피러 온 줄 알았는데...";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "하하, 뭐, 내가 특별한 탐험, 피비린내 나는 탐험이라고는 말 안 했지... 이런 몸풀기는 오랜만이야! 이제 모두 안심해도 돼, 이 탄광에서 쓰레기 하나도 못 빠져나갔으니까!";
			link.l1 = "그럼 이제 우리 다음엔 뭘 할 거야, 얀?";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "다음에 뭘 할 거냐니, 그게 무슨 소리야? 금이랑 은을 찾아야지. 잭맨이 심심해서 이런 보루를 지키고 있었던 건 아니라고 본다. 여기 주둔군 전체를 배치했잖아. 광산에 있는 노예들 봤어? 광석을 어디에 보관하는지 알아내야 해.";
			link.l1 = "좋아. 그럼 너는 노예들을 심문하고, 나는 올라가서 캠프에 있는 집들을 모두 뒤져볼게. 뭔가 찾을지도 모르니까.";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "잡았다! 이제 움직일 시간이야!";
			link.l1 = "...";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "가라, 이봐. 그리고 이 초라한 오두막들을 샅샅이 뒤져!";
			link.l1 = "가고 있어!";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "하하! "+pchar.name+", 네가 나랑 같이 이 광산을 쑥대밭으로 만들겠다고 자원했다니 정말 멋지다! 네가 행운의 별 아래 태어났다는 또 하나의 분명한 증거지.";
			link.l1 = "금 찾았어?";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "그래, 젠장! 금이 아니라 은이었어, 그것도 꽤 쌓여 있더군. 하루만 늦었어도 그놈들이 은을 야영지에서 옮겼을 거야. 그래서 이곳에 깡패들이 그렇게 많았던 거지 - 전부 호위대였어.\n네 덕분에 제때 도착했어. 네가 없었으면 아직도 사람들 모으고 있었을 거야. 축하한다, 동료!";
			link.l1 = "하! 알겠군... 우리가 가진 은화가 얼마나 되지?";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "우리에겐 약 사천 단위가 있어. 두 부분으로 나눌 거야 - 절반은 내 몫, 절반은 네 몫, 약속한 대로지.";
			link.l1 = "대단하군! 저 물건으로 돈을 엄청 벌 수 있겠어!";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "그건 확실하지... 값진 거라도 찾았어?";
			link.l1 = "아니. 이 오두막들엔 더블룬 한 닢도 없어. 하지만 서류 몇 장을 찾았지. 읽어보니 이 광산의 주인은 포트 로얄 출신의 로렌스 벨트로프라는 사람이더군.";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "오, 정말인가? 그 서류들 좀 보여줘...";
			link.l1 = "여기 있어.";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(읽는 중)... 좋아... 벨트로프? 어디서 들어본 성인데. 아, 맞아! 토마스 벨트로프! 흥미롭군... 알겠다, 블루벨드로 돌아가면 이걸 조사해 보지. 괜찮다면 이 서류들은 내가 가지고 있겠네?";
			link.l1 = "전혀 아니오. 나에게는 아무 쓸모도 없소.";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "좋아. 이제 가장 중요한 부분이 남았어. 내가 은을 배로 옮길 거야. 미스키토족이 우리를 도와줄 거고, 마차도 준비할 거야... 그동안 너는 가서 좀 쉬어. "+pchar.name+". 누구보다도 그럴 자격이 있소!";
			link.l1 = "고마워, 얀. 저 언덕에 야영지를 차리자. 여기 잿냄새가 너무 심하군. 그래, 그리고 이 오두막들에 난 불도 꺼야 해. 누가 알겠어, 언젠가 우리한테 쓸모가 있을지도 모르니까...\n";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "광산을 차지할 생각인가? 하하! 나도 이미 그 생각을 해봤지. 하지만 약탈하는 것과 소유로 가져가는 건 완전히 다르다네. 친구, 이 광산은 이미 주인이 있어. 우리가 괜히 영국 당국과 문제를 일으킬 수도 있지.\n게다가 내가 얘기 나눠본 노예들 말로는 여기 광맥은 거의 다 파냈다고 하더군. 이미 여러 번 대량의 은이 반출됐대. 내 생각엔 이 광산은 끝난 것 같아.";
			link.l1 = "흠... 두고 보자고. 아직 다 끝난 건 아닐지도 모르지. 좋아, 나도 좀 쉬어야겠어. 나중에 보자, 얀";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "가보시오. 아무 걱정 마시오. 나머지는 우리가 다 알아서 하겠소.";
			link.l1 = "...";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "잘 쉬었나, "+pchar.name+"?";
			link.l1 = "나쁘진 않았어... 하지만 솔직히 말해서, 선술집을 찾아서 한잔하고, 깨끗한 침대에서 잠 좀 자면 정말 좋겠는데.";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "인디언들이 은을 해안에 가져다 놓았고, 내 장교들의 감독 아래 네 배에 싣고 있다네. 이제 돌아가도 되네. 럼주와 선술집, 그리고 침대를 바란 그 소원이 곧 이루어질 걸세. 그리고 닷새 후 내 집에 들러주게. 아직 해야 할 일이 많으니.";
			link.l1 = "알겠어, 얀. 다섯 날 뒤에 블루웰드에서 보자! 행운을 빌어!";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "얀, 나한테 소리 지르지 마. 우리 이성적으로 해결하자고, 우리 할 일이 있잖아!";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "지금 당장 내 개들을 풀어버릴 거야, 이 두꺼비 같은 놈! 르바쇠르는 잊고 꺼져버려!";
			link.l1 = "얀! 내 말 좀 들어봐...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "무슨 통 말이야? 헬렌이라면, 내가 제대로 혼 좀 내줄 거야... 농담이야, 샤를, 농담이라고! 어떤 사정인지 나도 알아. 그리고 조안나에 대해서는... 이번 일이 그녀에게 좀 생각할 거리를 줬으면 해. 요즘 특히 신경이 곤두서 있거든... 뭐, 인생이 다 그런 거지. 아무튼, 카르타헤나에서 행운을 빌어!\n";
			link.l1 = "다시 만날 때까지, 얀.";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
