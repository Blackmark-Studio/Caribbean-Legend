// Ричард Флитвуд - английский капитан
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
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "Selamlar, kaptan! Görünüşüm sizi yanıltmasın, iyiyim—neredeyse körüm ama hâlâ iyiyim. Kendimi tanıtayım: Ben Richard Fleetwood.";
					link.l1 = "İyi günler, tanıştığımıza memnun oldum. Ben kaptan "+GetFullName(pchar)+".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "Sana gemini demirlemeni söyledim. Beni dinliyor musun hiç?";
						link.l1 = "Tabii, ilgileniyorum. Ben hallederim.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Demek yine geldin. 'Valkyrie'nin komutasını al - mürettebatım ayrıntılar hakkında bilgilendirildi - ve Bridgetown'a yelken aç. Şehirdeki önemli kişilerin hepsini ziyaret et ve konuştuğumuz dedikoduları yay. Sonra da o alçağın saldırısına hazır ol. Gemiyi değiştirme ve filo kurma, yoksa tuzak olduğunu anlayıp gelmeyecektir\nOnun gemisine çıkmalı ve onu St. John's'a teslim etmelisin. Korsanın günlüğünü bulman şart, çünkü Lucas Rodenburg'un işin içinde olduğuna dair elimizdeki tek kanıt o olacak. Bunu başaracağından eminim. Yolun açık olsun, kaptan.";
						link.l1 = "Teşekkür ederim! Anlaştığımız gibi işi halledeceğim.";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "Geri döndünüz, kaptan... Yolculuğunuz hakkında her şeyi zaten biliyorum.";
						link.l1 = "Öyle mi? O zaman biliyor olmalısın ki...";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "Geri döndünüz, kaptan... Yolculuğunuz hakkında her şeyi zaten biliyorum.";
						link.l1 = "Öyle mi? O zaman biliyor olmalısın ki...";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "Geri döndünüz, kaptan... Yolculuğunuzun her ayrıntısını zaten biliyorum.";
						link.l1 = "Biliyor musun? O zaman şunu da bilmelisin ki...";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "Geri döndünüz, kaptan... Yolculuğunuz hakkında her şeyi zaten biliyorum.";
						link.l1 = "Öyle mi? O halde şunu da biliyor olmalısın...";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "Selam, dostum! Seni görmek ne güzel! Abigail geminde mi?";
					link.l1 = "Maalesef bilmiyorum, Richard. Benimle gelmeyi reddetti, çünkü onun gidişi babasına ağır bir darbe olurdu; adam zaten elindeki son parayı da kaybetmiş. Ben de bu meseleyi çözmeye, Solomon'un parasını ve o adayı bulmaya karar verdim...";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "Başka bir şey var mı, kaptan?";
				link.l1 = "Hayır, zaten gidiyorum.";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "Başka bir şey var mı, kaptan?";
				link.l1 = "Hayır, zaten gidiyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("Voice\English\hambit\Richard Flitwood-03.wav");
			dialog.text = "Lanet olası korsan! Çatışmayı kazandın ama görevimi yine de yerine getireceğim. Barut mahzenini ateşlemeye hazırladım, gemim birazdan senin 'Hayalet Gemin'le birlikte havaya uçacak. Bir daha asla tek bir İngiliz gemisini bile batıramayacaksın. Onurla öleceğim!";
			link.l1 = "I'm sorry to disappoint you, but you're wrong, Fleetwood. There are no pirates on my ship; I've dealt with them before. I needed you, and this ship served as a perfect trap.\nEnough with the pleasantries, I still have to kill you and get away from your flaming tub!";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "Charlie has already informed me about your successful interception of the enemy's trade caravan. I am glad to meet you; England needs such brave captains. Now, let me tell you something of great importance.";
			link.l1 = "Dinliyorum, Bay Fleetwood.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "Bir korsan, takımadalar boyunca şiddet eylemleri gerçekleştiriyor ve kendini efsanevi hayalet gemi 'Uçan Hollandalı' olarak tanıtıyor. 'Uçan Hollandalı' gibi davranıyor, efsanevi bir hayalet gemi. Eminim ki Hollandalı, ama uçtuğu yok. Bence bu adam, Hollanda Batı Hint Şirketi'nin başkan yardımcısı Lucas Rodenburg'un paralı askerlerinden biri.\nRodenburg, İngiltere'ye karşı gizli bir ticaret savaşı başlattı – bu 'hayalet gemi' sadece İngiliz bayrağı altındaki ticaret gemilerine saldırıyor. Şirket için, gerçek bir savaşa girmeden bu bölgedeki etkimiz zayıflatılmalı.\nBir süredir bu hayalet geminin peşindeyim, fakat kaptanı çok tecrübeli bir denizci ve gemisi hem hızlı hem de izini kaybettiriyor.\nÇakalı açık çatışmada yakalamak imkânsız olduğuna göre, kurnazca hareket etmeliyiz. Son suikast girişimi de işimizi kolaylaştıracak. Ne dersin kaptan, korkuyor musun?";
			link.l1 = "Hiç şansın yok. Bu alçağı bulup batırmana yardım etmekten memnuniyet duyarım. Bunu benden isteyecektin, değil mi?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "You are right. Now, let's discuss the details. My men will spread rumours that I am on my deathbed and have sold my ship, the 'Valkyrie', to you. Next, we will proceed with our little deception. You will pretend to be a merchant who bought the brig from me and got rid of most of the cannons.\nTherefore, your task is to sail to Barbados and tell everyone there that your holds are filled with valuable cargo and your pockets are brimming with coins. Let them know that you are planning to set sail soon. Play the role of a greedy, simple, yet wealthy merchant.\nOur damned Dutchman gets his information about trading ships from Bridgetown. It is unknown who exactly supplies him with it. Everyone is under suspicion—from a local merchant to the governor, though the latter possibility is quite terrifying.\nTake command of my 'Valkyrie' and her crew. But first, you should leave all your ships here; I have already spoken to the local harbour master. It will cost 10,000 pesos per month for your flagship.\nOnce that's done, return to me and I will make the arrangements. Ah, captain, don't forget to take your cut for capturing the silver caravan, and ten thousand for the harbour master—the money is in the chest of drawers.";
			link.l1 = "Anladım, Bay Fleetwood. Liman başkanını görmeye gidiyorum.";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "Evet, korsan gemisini ele geçirme görevinde başarısız olduğunu biliyorum. Bütün planlarım suya düştü. 'Valkyrie'yi senden alıyorum. Artık gidebilirsin, sana daha fazla ihtiyacım yok.";
			link.l1 = "Bunun için gerçekten üzgünüm. Hoşça kalın, Bay Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "Evet, 'Valkyrie'yi kaybettiğinin farkındayım. Bu hiç kabul edilemezdi... Ele geçirilen korsan gemisini senden alacağım. Artık gidebilirsin, hizmetine ihtiyacım yok.";
			link.l1 = "Bunun için gerçekten üzgünüm. Hoşça kalın, Bay Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "Evet, senin nadir rastlanan bir beceriksiz ve sakar olduğunu biliyorum. Korsan gemisini ele geçiremedin ve 'Valkyrie'mi kaybettin. Gerçekten hayal kırıklığına uğrattın beni. Çık dışarı!";
			link.l1 = "Bunun için çok üzgünüm. Hoşça kalın, Bay Fleetwood.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "Evet, planımızda başarılı olduğunu biliyorum. O alçak korsanı ortadan kaldırdın ve gemisini ele geçirdin. Gerçek adı nedir?";
				link.l1 = "Serap";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "Evet, planımızı başarıyla tamamladığının farkındayım. O alçak korsanı ortadan kaldırdın ve gemisini ele geçirdin. 'Valkyrie'yi geri alacağım. Korsanın gemisi ise ödül olarak sende kalabilir. Bu aynı zamanda bir tür... tazminat da sayılır. Limanda demirli olan kendi gemin ise, iskelede çıkan yangının yayılmasıyla tamamen yandı. Bu aksaklık için özür dilerim, "+pchar.name+"... I hope the ghost ship will serve you better.\nI have ordered your new vessel to be cleaned of the stubborn dirt and seaweed. They will also dress your beauty in new sails of the finest cotton.\nFinally, please accept your reward of 100,000 pesos and this navigation tool. I have always wanted to present it to a worthy sailor, and you did an admirable job out there! Well, the time has come to say farewell; I have finished my business here and should return to Europe. Good fortune to you, captain!";
				link.l1 = "Sana da aynısı, Richard!";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("They say that you and Richard Fleetwood has planned some military operation and you have personally destroyed that elusive pirate who has been robbing our trade ships. You are a real hero, captain!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "Serap mı? Çok uygun bir isim, bence... 'Valkyrie'mi senden geri alacağım, bu yüzden korsan gemisini ödül olarak alabilirsin. Bu aynı zamanda bir tür tazminat da olur. Limanda demirlemiş olan gemin, iskeledeki yangın yayılmaya başlayınca tamamen yandı. Üzgünüm, "+pchar.name+"... Umarım hayalet gemi sana daha iyi hizmet eder.\nYeni geminin o inatçı kir ve yosundan arındırılması için emir verdim. Ayrıca güzelliğine en kaliteli pamuktan yeni yelkenler giydirecekler.\nSon olarak, 100.000 peso ödülünü ve bu seyir aletini kabul et. Onu her zaman layık bir denizciye vermek istemiştim... Orada harika bir iş çıkardın, seninle gurur duyuyorum! O alçağın seyir defteri yanında mı?";
			link.l1 = "Evet, tabii ki. İşte burada, al. Sana bir şey sormak istiyorum, Lucas Rodenburg'un adamları arasında... Asyalı biri var mı?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "Evet, var. Çinli Longway, kendi gemisi 'Meifeng'in kaptanı. Korsanın günlüğünde bunu okudun mu? Hadi bakalım...(okuyor) Demek öyle. Beklediğim gibi, tüm bunların arkasında Lucas Rodenburg varmış! Neyse, artık bu bizim meselemiz değil... Genel valimiz bu herifle ilgilenecek. Lucas Rodenburg yaptıklarının bedelini ödeyecek!";
			link.l1 = "Hm, ilginç, peki İngiliz genel valisi Hollanda'nın bir tebaasıyla nasıl 'baş edecek'?";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "Her zaman siyasi oyunlar vardır, sevgili dostum... Hollanda, İngiltere'ye karşı ticaret savaşını başlatan taraf olduklarını kabul etmek zorunda kalacak, ama muhtemelen bunu yapmayacaklar. Onun yerine, her şeyin suçunu Rodenburg'a atacaklar. Lucas makamını kaybedebilir ya da kaybetmeyebilir. Her halükarda, kariyeri ağır bir darbe alacak. Ama bu artık bizim meselemiz değil, kaptan. Siz işinizi gayet iyi yaptınız. Bu yüzden size çok hassas bir başka mesele daha vermek istiyorum.";
			link.l1 = "Dinliyorum, Richard. Bu sefer İngiliz tacının sıradaki düşmanı kim olacak, yok edilecek olan?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "Hayır, bu sefer senden daha kişisel ve huzurlu bir meseleyle ilgilenmeni isteyeceğim. Sana kısa bir hikaye anlatayım, ki bu arada, 'Mirage'ınla da ilgili.";
			link.l1 = "Devam et.";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "I was on a raid, hunting the ghost ship a month before you and I met. It was south of Martinique, not far from longitude 64° 41'. We heard a fight going on somewhere in the distance, but the wind was too weak, so we didn't make it in time. An English flute was sunk by a ghost ship close to some small island which isn't even marked on the map\nI failed to catch the pirate and decided to visit that island, hoping to find any survivors. And I found them. A couple of Jewish refugees, father and daughter. The girl was called Abigail and she was beautiful! A living miracle... I took them aboard and delivered them to Curacao, though her father, Solomon, didn't show much sympathy to me\nAs far as I understood, he thought that I was the pirate who sank their vessel, old man didn't know much about ships or the differences between them. During that little voyage, Abigail and I became friends, or, to be completely honest, fell in love with each other. Isn't that a story?\nAnd I've recently found out that bastard Rodenburg has been courting my Abigail for a while, just think about it! I was going to bring her here, once I solved the matter concerning her father's lost money; he stashed every single coin he had on that island I mentioned. I failed to find its location. We cannot wait any longer\nSince my health still doesn't allow me to set sail myself, I am asking you to go to Willemstad, find Abigail and bring her here. Mention my name and she will trust you.";
			link.l1 = "Bu konuda hiçbir sorun görmüyorum. Şimdi yelken açmaya hazırım.";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "Harika! Sana güvenebileceğim için memnunum, "+pchar.name+". Yaptığın işin karşılığını fazlasıyla alacaksın, merak etme.";
			link.l1 = "Seni fazla bekletmeyeceğim. Yakında görüşürüz, Richard!";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = ""+pchar.name+", adayı gerçekten bulmaya karar verdin mi? Cömertliğinden etkilendim. Buldun mu?";
			link.l1 = "Evet, yaptım. Ne yazık ki, kötü haberler de burada başlıyor. O lanet yerden canımı zor kurtardım... Hâlâ düşündükçe titriyorum...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "Orada ne oldu? Söyle bana, dostum, beni merakta bırakma!";
			link.l1 = "Adaya geldim ve Solomon'un sandığını saklamış olabileceği mağaraya yöneldim. Gerçekten de oradaydı. Ama ona dokunduğumda, bilinmeyen bir güç beni geri fırlattı. Bir patlama duydum ve sandıktan on adım ötede yere savruldum...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "İnanılmaz!";
			link.l1 = "Az daha ölüyordum - birkaç acı verici yara aldım. Kendime gelmeye çalışırken, kafamda korkunç sesler uğulduyordu ve o iğrenç yaratık birdenbire yerin altından çıktı... Tanrım, o canavar!";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Richard, deli değilim. Gerçekten oldu, ben bile zor inanıyorum. Tamamen kurumuş ve boyanmış bir Kızılderili cesediydi, başında bir sürü tüy vardı. Bu yaratık bir şeyler mırıldandı, sonra kocaman bir Kızılderili sopası çekip bana saldırdı!";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "Aman Tanrım... Hâlâ o şeyle nasıl başa çıkabildiğimi anlamıyorum... Ona o kadar çok darbe indirdim ki, on iki adamı öldürmeye yeterdi, ama hâlâ ayaktaydı... Nefesimi toparladıktan sonra, o uğursuz sandığı açtım... İçinde para yoktu, ama başka bir şey vardı. Bak, bu gerçekten ilginç bir eşya!";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "B-r-r... korkunç..."+pchar.name+", dur bekle... Eminim o! Bu, bana biberle gözümü kör edip öldürmeye çalışan o alçağın kafası!";
			link.l1 = "Onu tanıyor musun? Adı Gaston, Bridgetown'un barmeni ve hayalet geminin kaptanı van Berg'in destekçisi. Onu hemen tanıdım, ama onu kimin öldürdüğünü ya da kesik başının o bilinmeyen adada Solomon'un sandığında nasıl bittiğini bilmiyorum!";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "Haklısın, gerçekten ürkütücü ve tuhaf bir hikaye bu. Gizemli...";
			link.l1 = "Aynen öyle. Para gittiği için Abigail’e dönmenin anlamı yoktu. Bu yüzden sana anlatmaya geldim. Belki sen, Richard, bu karmaşadan bir anlam çıkarabilirsin...";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "Ben mi? Burada hiçbir şey anlamıyorum, tıpkı senin gibi... Ama sana bir şeyi kesin olarak söyleyebilirim – içimde kötü bir his var..."+pchar.name+", şimdi beni dinle. Git ve Bridgetown'u kontrol et, Gaston'un gerçekten gittiğinden emin ol. Sonra senden rica ediyorum, 20 gün sonra Curaçao'daki Blanca Lagoon'a gel. Charlie Knippel orada seni bekliyor olacak. Abigail'in babası için parayı ben toplayacağım. Parayı Charlie'ye vereceğim, sen de onu Solomon'a götürüp Abigail'i Antigua'ya teslim edeceksin. Bu sefer hiçbir engel olmayacak, bunu anlamalısın. Hadi, dostum!";
			link.l1 = "Pekala, Richard. Hemen yelken açacağım.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Oh, captain, I have heard that Richard Fleetwood really admires you. Trust me, his praise costs a lot. You must be a very important person...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "Anladığım kadarıyla, Abigail'imi kaçıran alçak sensin. Charlie de bana dönmediğine göre, onun da sorumlusu sen olmalısın.";
			link.l1 = "Haklısınız, Bay Fleetwood. Benim. Charlie, sizin Abigail’e yazdığınız mektup sayesinde onun güvenini kazanmama yardımcı oldu. Ama hemen konuya geçelim... Parayı getirdiniz mi?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "Yaptım. Ama önce Abigail’i görmek istiyorum. Onun hayatta ve sağ olduğundan emin olmalıyım, çünkü bir piçin sözüne güvenmeyeceğim.";
			link.l1 = "Sizce efendim, şartlarınızı dikte edecek bir konumda olmadığınızı düşünmüyor musunuz?";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "Artık bu oyunu oynamak istemiyorum. Abi benimle kalacak, sen ise bu sahilde sıkışıp kaldın! Ateş!";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://массовая драка на необитаемом острове
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Anlıyorum, ama ben de aptal değilim. Abigail'i görmeden para konuşmak yok. Peki, ne olmuş? Bekliyorum.";
			link.l1 = "Güzel. Şimdi kartlarımı masaya koyma vakti, Kaptan Fleetwood. Bu buluşmayı burada ayarladım, çünkü mesele para değil. Tabii ki, parayı almak isterim ama önce size ihtiyacım var.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "Ben mi? Bu giderek daha ilginç bir hal alıyor... Sanırım burada gerçekten neler döndüğünü anlamaya başlıyorum. Söyle bana, Abigail hayatta mı? Yaşıyor mu, yoksa onu öldürdün mü, alçak?";
			link.l1 = "Sanırım onun akıbetinden seni habersiz bırakacağım. Bilmen gereken tek şey – burada olmadığı. Rolünü gayet iyi oynadı ve şimdi sen benim ellerimdesin. Aşk ne harika bir şey... Başka nasıl bir tilkiyi ininden çıkarıp ortaya çekebilirdim? Ha-ha-ha!";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "Daha sevinmek için erken, seni serseri. Bu adada sana güzel bir karşılama hazırladım ve burada kimin söz sahibi olduğu henüz belli değil! O yüzden hazır ol, bana anlatacak çok şeyin var – Abigail hakkında, Charlie hakkında. Onlara zarar verdiğinin hesabını vereceksin!";
			link.l1 = "Şimdiden korkudan titriyorum! Sohbetimizi burada bitirelim, Bayım. Cehenneme gitmeye hazırlan, çünkü cennette sana yer yok.";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
