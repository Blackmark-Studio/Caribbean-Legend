void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Konuşacak bir şeyimiz yok.";
			link.l1 = "Peki...";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "CitizenNotBlade":
			if(LoadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu kasabanın bir vatandaşıyım ve senden kılıcını indirmeni rica ediyorum.","Dinle, ben bu kasabanın bir vatandaşıyım ve senden kılıcını indirmeni istiyorum.");
				link.l1 = LinkRandPhrase("Pekala.","Tabii.","Peki...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol, "+GetSexPhrase("kanka","kız")+", elinde silahla orada burada dolaşıyorsun. Bu beni tedirgin ediyor...","Ortada   olduğunda hoşlanmıyorum "+GetSexPhrase("adamlar","insanlar")+" önümde silahını çekmiş yürüyen biri var. Bu beni korkutuyor...");
				link.l1 = RandPhraseSimple("Anladım.","Anladım.");
			}
			
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = "Hadi bakalım dostum, ceplerini göster.";
			link.l1 = "Ne?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "Beni duydun. Hadi, lafı uzatma. Konuşmayı sevmem...";
			link.l1 = "Lanet olsun! Ve "+pchar.questTemp.different.FackWaitress.Name+" seninle çalışmak?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "O yapar, yapar... Paranı ver yoksa seni doğrarım!";
			link.l1 = "Hayır! Karnını deşerim!";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "Al paralarımı, alçak! Ama bununla paçayı sıyıramayacaksın...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "Elbette, buna itiraz edemem. Hoşça kal, dostum. Ve unutma, garson kızları baştan çıkaracak kadar yakışıklı değilsin. Bir dahaki sefere akıllı ol!";
			link.l1 = "...Hadi, devam et.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "Dediğiniz gibi...";
			link.l1 = "Bunu yaparım...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "Buradayım! Beni istiyor musun, yakışıklı?";
			link.l1 = "Vay canına, işler ne çabuk büyüdü...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "Vaktimizi boşa harcamayalım!";
			link.l1 = "Heh, daha fazla katılamazdım!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "Günaydın. Benim adım "+GetFullName(npchar)+". Ben   kaptanıyım "+GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName+"Acc"))+" '"+npchar.Ship.name+"'."; 
			link.l1 = "Harika! Sonunda seni buldum.";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "Beni mi buldun?!";
			link.l1 = "Evet. Şey, liman ofisinde unuttuğunuz seyir defterinizi getirdim "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "Lanet olsun! Şimdi kaybettiğim yeri anladım. Bu kayıp neredeyse gemimde isyana yol açacaktı...";
			link.l1 = "Her şey yolunda, sonu iyi biten hikaye iyidir. Seyir defterini al ve şimdi paramdan konuşalım.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Tam zamanında geldin, henüz yeni bir tane başlatmadım, bu yüzden elimden geldiğince ödeyeceğim. "+FindRussianMoneyString(sti(npchar.quest.money))+" ve birkaç parça kişisel takımımdan kabul et.";
				link.l1 = "Güzel. Al şunu.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Hm, biliyor musun, yeni bir seyir defteri tutmaya başladım bile. Yine de, eskisinin benim için hâlâ bir değeri var. O yüzden sana ödeme yapacağım "+FindRussianMoneyString(sti(npchar.quest.money))+" ve birkaç parça kişisel takımımdan kabul et.";
					link.l1 = "Anlaştık o zaman. Al defterini.";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "Yeni seyir defterini çoktan başlattım. Eski defterdeki tüm notları da aktardım. Artık ona ihtiyacım yok, bu yüzden sana verecek param yok.";
					link.l1 = "Harika. Yani bütün bu kovalamaca boşunaymış.";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "Teşekkür ederim. Hoşça kal, "+GetSexPhrase("kanka","kız")+".";
			link.l1 = "Sana da...";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "Ha, bir dahaki sefere zamanlamana dikkat et.";
			link.l1 = "Doğru, öyle.";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "Seni gemimin güvertesinde selamlıyorum. Açıkçası, beni ödümü kopardın - Tek Gözlü At Avcısı'nın peşimde olduğunu sandım...";
				link.l1 = "Hayır, kaptan, bugün keyfim yerinde. Sana yardımcı olmak için buradayım.";
			}
			else
			{
				dialog.text = "Gemime hoş geldiniz!";
				link.l1 = "Selam, Kaptan! Seni arıyordum.";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "Neden?";
			link.l1 = " Günlük defterinizi liman başkanının evinde unuttunuz "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Kahretsin, demek orasıymış! Bu kayıp bana şimdiden bir sürü bela açtı.";
				link.l1 = "Bir ödül ne dersin?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Kahretsin, şimdi kaybettiğim yeri gördüm! Teşekkür ederim, ama beni aramakta fazlasıyla geciktin. Çoktan yeni bir seyir defteri tutmaya başladım bile. Yine de, eski notları yenisine aktarmam gerekecek...";
					link.l1 = "Ve ne kadar?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "Yeni seyir defterini çoktan başlattım. Eskisindeki tüm notları da aktardım. Artık ona ihtiyacım yok.";
					link.l1 = "Yani eski bir günlüğe ihtiyacın yok mu? Gerçekten mi?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "Sana ödeme yapabilirim "+FindRussianMoneyString(sti(npchar.quest.money))+" ve birkaç mücevherim. Elimden gelen sadece bu kadar.";
			link.l1 = "Pekala o zaman. Al günlüğünü.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "Tekrar teşekkürler. Hoşça kal, dostum.";
			link.l1 = "Böyle devam et.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "Kesinlikle öyle. Birini kovalıyorsan, ondan daha hızlı olmalısın.";
			link.l1 = "Öncelikle seyir defterlerini kaybetmemeye bak. Peki.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(100/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "Hepimizin sakinleştiğini sanmıştım.";
			link.l1 = "Evet, doğru.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "Selam. Ne istiyorsun?";
			link.l1 = "Bir şey değil, sadece biraz haber duymak istedim. Satacak bir şeyin var mı?";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "Sana satacak bir şeyim yok, haberim de yok. Bu arada, burada olmandan memnun değilim. Anlaşıldı mı?";
			link.l1 = "Sen... O zaman hoşça kal, dostum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "Sana söyledim, burada olmanın hiçbir anlamı yok!";
			link.l1 = "Anladım...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = "Neden bana saldırdın?!";
			link.l1 = "Gemiyi sahibine geri götürmem gerek.";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "Ne sahibi? Ben sahibiyim!";
			link.l1 = "Hayır, değilsin. Bu geminin kime ait olduğunu bilmiyorum. Ama çalındı ve onu geri götürmem gerekiyor.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "Lanet olsun! Ama benim için henüz bitmedi. En azından seni öldürmeye çalışacağım...";
			link.l1 = "Denemek elinden gelen tek şey.";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------поисковый генератор горожан--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "SCQ_exit":
			DialogExit();
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "SCQ_exit_clear":
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		
//--------------------------------------------поисковые квесты дворян---------------------------------------------
		
		case "SCQ_Nobleman":
			dialog.text = "Selamlar, "+GetAddress_Form(NPChar)+". Kendi geminin kaptanı olduğunu görüyorum? Benim adım "+GetFullName(npchar)+" ve sana bir teklif sunmak istiyorum.";
			link.l1 = RandPhraseSimple("Çok üzgünüm, ama gitmem gerekiyor.","Çok üzgünüm, ama seninle konuşacak vaktim yok.");
			link.l1.go = "SCQ_exit";
			link.l2 = "Tamamen seni dinliyorum.";
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //вариант А
					if (sti(pchar.reputation.nobility) < 35)
					{
						dialog.text = "Dinle o zaman. "+SelectNB_battleText()+"\nOnu bulacak ne vaktim ne de imkanım var. Çünkü buraya hiç uğramaz. Sanırım şimdi anladın, sana ne teklif edeceğimi görüyorsun, değil mi?";
						link.l1 = LinkRandPhrase("Sanırım birini bulup sana getirmem gerekiyor?","Belki de o alçağı bulup size getirmemi istiyorsunuz?","Bu adamı bulup buraya getirmemi mi istiyorsun?");
						link.l1.go = "SCQ_NM_battle";
					}
					else //вариант В
					{
						SelectNB_prisonerText(npchar);
						dialog.text = "Öyleyse dinle."+SelectNB_battleText()+"\nOnu bulacak ne vaktim ne de imkanım var. Buraya hiç gelmez. Sanırım artık anlıyorsun, sana ne teklif edeceğimi görüyorsun, değil mi?";
						link.l1 = LinkRandPhrase("Siz istiyorsunuz ki birini bulup size getireyim, öyle mi?","Belki de o piçi bulup size getirmemi istiyorsunuz?","Bu adamı bulup buraya getirmemi mi istiyorsun?");
						link.l1.go = "SCQ_NM_prisoner"
					}
		break;
				
				case 1: //вариант С
					SelectNB_peaceText(npchar);
					dialog.text = "O zaman dinle. Aslında, "+npchar.quest.text+" donanmada kaptan olarak görev yapıyor. Benim de burada olduğumdan haberi bile yok!\nOnunla tanışmak isterdim, ama ne zamanım var ne de onu bulacak fırsatım...";
					link.l1 = "Yani, bu kaptanı bulup ona senden bahsetmemi mi istiyorsun?";
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;
		
		case "SCQ_NM_battle": //вариант А
			dialog.text = "Tam olarak öyle değil. Onu bul, ama buraya getirmen gerekmiyor. Onu öldür, bu yeterli olacak. Pis gemisiyle birlikte batır, vur, kılıcınla sapla - nasıl yaparsan yap umurumda değil, yeter ki bu herifin varlığıyla dünyayı zehirlemesine bir son ver. Ödül cömert olacak.";
			link.l1 = "Ha! Kolay iş. Bana onun adını ve gemisinin adını söyle.";
			link.l1.go = "SCQ_NM_battle_1";
		break;
		
		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			dialog.text = ""+npchar.quest.SeekCap.capName+" of the "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" named "+npchar.quest.SeekCap.shipName+". O, limanın sık sık misafiridir "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Sana ödeyeceğim "+FindRussianMoneyString(sti(npchar.quest.money))+" altın dublon olarak.";
			link.l1 = "Bilmem gereken tek şey bu. Denizde gözümü dört açacağım. Ve arkadaşını bulduğumda, ona... 'sesini alçaltarak' ...pek de canlı olmayacak şekilde davranacağım.";
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = "Bu iş için o kadar yetmez.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_battle_2":
			dialog.text = "Anlaştığımıza sevindim. Dönüşünü bekliyor olacağım.";
			link.l1 = "Seni nerede bulabileceğim? Bunu şimdi netleştirelim, seni arayarak zaman kaybetmek istemiyorum.";
			link.l1.go = "SCQ_NM_battle_3";
		break;
		
		case "SCQ_NM_battle_3":
			dialog.text = "Her sabah yerel kilisede ayine katılırım. Beni her gün sabah 8 ile 9 arasında orada bulabilirsin.";
			link.l1 = "Anlaştık o zaman! Sonuçları yakında bekle.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_battle";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_prisoner": //вариант В
			dialog.text = "Aynen öyle. Onu bul ve bana getir. Canlı olarak. Onunla kendim ilgileneceğim. Seni cömertçe ödüllendireceğim.";
			link.l1 = "Pekâlâ, onu bulmayı deneyebilirim ama ayrıntılara ihtiyacım var.";
			link.l1.go = "SCQ_NM_prisoner_1";
		break;
		
		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "O alçağın adı "+npchar.quest.SeekCap.name+". O, şu anda hizmet ediyor "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" named "+npchar.quest.SeekCap.shipName+",   komutası   altında olan "+npchar.quest.SeekCap.capName+". Gemi genellikle limanda görülür "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Bu iş için sana ödeme yapacağım "+FindRussianMoneyString(sti(npchar.quest.money))+" altın dublon olarak.";
			link.l1 = "Bu bana yeter. Açık denizde tetikte olacağım.";
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = "Böyle bir iş için bu yetmez.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_prisoner_2":
			dialog.text = "Anlaştığımıza sevindim. Dönüşünü bekliyor olacağım.";
			link.l1 = "Seni nerede bulabilirim? Bunu baştan netleştirelim, seni aramakla vakit kaybetmek istemiyorum.";
			link.l1.go = "SCQ_NM_prisoner_3";
		break;
		
		case "SCQ_NM_prisoner_3":
			dialog.text = "Her sabah yerel kilisede ayine katılırım. Beni her gün sabah 8'den 9'a kadar orada bulabilirsin.";
			link.l1 = "Anlaştık o zaman! Sonuçları yakında bekle.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_prisoner";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_peace": //вариант С
			dialog.text = "Aynen öyle! Onu bul ve bu kasabada yaşadığımı söyle. Hizmetlerin için sana ödeme yapacağım.";
			link.l1 = "Pekala... Deneyebilirim. Bana ayrıntıları anlat.";
			link.l1.go = "SCQ_NM_peace_1";
		break;
		
		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
			dialog.text = "Adı "+npchar.quest.SeekCap.capName+". Ve o hizmet ediyor "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" "+npchar.quest.SeekCap.shipName+"'. Sık sık uğrar "+XI_ConvertString("Colony"+npchar.quest.Qcity)+" . Bu iş için sana ödeme yapacağım "+FindRussianMoneyString(sti(npchar.quest.money))+" altın dublon olarak.";
			link.l1 = "Anlaştık! Sanırım arkadaşını yakında bulurum.";
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = "Bu benim için yeterli değil.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_peace_2":
			dialog.text = "Anlaştığımıza sevindim. Dönüşünü bekliyor olacağım.";
			link.l1 = "Seni nerede bulabileceğim? Bunu şimdi netleştirelim, seni arayarak zaman kaybetmek istemiyorum.";
			link.l1.go = "SCQ_NM_peace_3";
		break;
		
		case "SCQ_NM_peace_3":
			dialog.text = "Her zaman akşam ayinine yerel kilisede katılırım. Beni her gün saat 6'dan 8'e kadar orada bulabilirsin.";
			link.l1 = "Anlaştık o zaman! Sonucu yakında bekle.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 18.0, 20.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_peace";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		//--> разговор на суше, вариант А
		case "NM_battleCap":
			dialog.text = "Ee? Ne istiyorsunuz, efendim?";
			link.l1 = "Kaptan sen misin "+GetFullName(npchar)+"?";
			link.l1.go = "NM_battleCap_1";
		break;
		
		case "NM_battleCap_1":
			dialog.text = "Evet, benim. Ne var?";
			link.l1 = "Bir adam seninle fazlasıyla ilgileniyor, adı ise "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+" . Hatırlıyor musun?";
			link.l1.go = "NM_battleCap_2";
			link.l2 = "Ambarında çokça maun olduğunu duydum. Satın almak isterim. Bana satar mısın?";
			link.l2.go = "NM_battleCap_4";
		break;
		
		case "NM_battleCap_2":
			dialog.text = "Bu ismi ilk kez duyuyorum. Yanılıyor olmalısınız, kaptan. İşimiz bitti mi?";
			link.l1 = "Hm. Peki, affedersiniz...";
			link.l1.go = "NM_battleCap_exit";
			link.l2 = "Gerçekten mi? Ama seni gayet iyi hatırlıyor. Ona olan borcundan bahsetti...";
			link.l2.go = "NM_battleCap_3";
		break;
		
		case "NM_battleCap_3":
			dialog.text = "Hangi borç? Neyden bahsediyorsun?";
			link.l1 = "Onur borcu!";
			link.l1.go = "NM_battleCap_fight";
		break;
		
		case "NM_battleCap_4":
			dialog.text = "Yanılıyorsun. Hiçbir şekilde odun ticareti yapmıyorum. İşimiz bitti mi?";
			link.l1 = "Hm. Peki, affedersiniz...";
			link.l1.go = "NM_battleCap_exit";
		break;
		
		case "NM_battleCap_exit":
			DialogExit();
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
		break;
		
		case "NM_battleCap_fight":
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант В
		case "NM_prisonerCap":
			dialog.text = "Peki? Ne istiyorsun, señor?";
			link.l1 = "Kaptan sen misin "+GetFullName(npchar)+"?";
			link.l1.go = "NM_prisonerCap_1";
		break;
		
		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Evet, benim. Ne oldu?";
			link.l1 = "Bir adamın adı "+sld.quest.SeekCap.name+" emriniz altında hizmet edeyim mi?";
			link.l1.go = "NM_prisonerCap_2";
		break;
		 
		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Evet. O benim subaylarımdan biri. Şimdi söyle bakalım, neden soruyorsun?";
			link.l1 = "Elbette, sana anlatacağım. Bu adamı yetkililerin emriyle arıyorum "+XI_ConvertString("Colony"+sld.city+"Gen")+", ve onu tutuklama ve teslim etme yetkim var "+XI_ConvertString("Colony"+sld.city)+" . Bu meseleyi barışçıl bir şekilde çözebilmemiz için bana yardımcı olmanızı rica ediyorum.";
			link.l1.go = "NM_prisonerCap_3";
		break;
		
		case "NM_prisonerCap_3":
			if(sti(npchar.reputation.nobility) > 41)
			{
				dialog.text = "Gerçekten mi? Ve böyle bir adam benim mürettebatımda mı çalışıyor? Ciddi misin?";
				link.l1 = "Bunun için kendini yorma, "+GetAddress_FormToNPC(NPChar)+". Gemiyi̇ne sandal göndereceğim ve onu kendimiz alacağız.";
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = "Bunu da mı söylediniz? Biliyor musunuz, efendim, onun geçmişi umurumda bile değil. Beni ilgilendirmez. Ve siz kimsiniz, bu arada? Yetkililer mi? Gerçekten mi? Ha! Adamlarımı size de, başkasına da teslim etmem. Bu konuşma burada bitti. Hadi, yolunuza!";
				link.l1 = "Yanlış seçim... Hem de çok kötü bir seçim!";
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;
		
		case "NM_prisonerCap_good":
			dialog.text = "Ne yapman gerekiyorsa yap.";
			link.l1 = "Hemen.";
			link.l1.go = "NM_prisonerCap_good_1";
		break;
		
		case "NM_prisonerCap_good_1":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.release = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_"+(rand(9)+21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
			chr.name = sld.quest.SeekCap.name;
			chr.lastname = "";
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, chr, false);//добавить пассажира
			SetCharacterRemovable(chr, false);
			log_info(sld.quest.SeekCap.name+" is under arrest");
			PlaySound("interface\notebook.wav");
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
			pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
			//DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
		break;
		
		case "NM_prisonerCap_bad":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.mustboarding = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "NM_prisonerDeck_exit":
			dialog.text = "İşimiz bitti mi, kaptan?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант C
		case "NM_peaceCap":
			dialog.text = "İyi günler. Ne istiyorsunuz, kaptan?";
			link.l1 = "Sen kaptansın "+GetFullName(npchar)+", değil mi?";
			link.l1.go = "NM_peaceCap_1";
		break;
		
		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			dialog.text = "Haklısın. Benim için bir şeyin var mı?";
			link.l1 = "Var. Bir adam adıyla "+GetFullName(sld)+" seni arıyor. En kısa zamanda onu ziyaret etmeni istiyor. O,  adresinde yaşıyor "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+".";
			link.l1.go = "NM_peaceCap_2";
		break;
		 
		case "NM_peaceCap_2":
			dialog.text = "Ha! Demek o da Yeni Dünya'ya taşınmış? O halde onu gerçekten ziyaret etmeliyim... Bilgi için teşekkürler, efendim!";
			link.l1 = "Rica ederim. Yaptığım işin parasını arkadaşınız ödeyecek. İyi şanslar, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "NM_peaceCap_3";
		break;
		
		case "NM_peaceCap_3":
			DialogExit();
			NextDiag.CurrentNode = "NM_peaceCap_exit";
			npchar.DeckDialogNode = "NM_peaceCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		
		case "NM_peaceCap_exit":
			dialog.text = "Bir zevkti, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "Zevk bana aitti, kaptan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;
		
		//--> встреча на палубе, вариант А
		case "NM_battleDeck":
			dialog.text = "Ahoy, "+GetAddress_Form(NPChar)+". Ne istiyorsun?";
			link.l1 = "Yükünüzde çokça sekoya olduğunu duydum, satın almak isterim. Satar mısınız?";
			link.l1.go = "NM_battleDeck_1";
		break;
		
		case "NM_battleDeck_1":
			dialog.text = "Yanılıyorsunuz. Hiçbir şekilde odun ticareti yapmıyorum ve buraya gelişiniz bana oldukça şüpheli görünüyor. Sanırım gemimden ayrılmanız en iyisi olur!";
			link.l1 = "Pekala, sadece soruyordum. Hoşça kal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		
		case "NM_battleDeck_exit":
			dialog.text = "Belaya mı bulaşmak istiyorsunuz, efendim? Tekrar etmemi ister misiniz?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;
		
		 //--> абордаж, вариант А
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Neden gemime saldırdın, alçak?";
			link.l1 = "Sana en iyi dileklerimi iletmek için buradayım "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" ,   şu adamdan   "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Umarım şimdi durumu anladınız.";
			link.l1.go = "NM_battleBoard_1";
		break;
		
		case "NM_battleBoard_1":
			dialog.text = "İmkansız! O halde kaybedecek hiçbir şeyim kalmadı...";
			link.l1 = "Senin hayatın nasıl?";
			link.l1.go = "NM_battleBoard_2";
		break;
		
		case "NM_battleBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		 //--> абордаж, вариант В
		case "NM_prisonerBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];//квестодатель
			dialog.text = "Neden gemime saldırdın, alçak herif?";
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = "Bir fikrin var mı? Subayını bana güzelce teslim etmeni istemiştim. Şimdi onu da, seni de, şu tenekeni de alıyorum!";
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = "Emriniz altında hizmet eden bir alçak var. Adı "+sld.quest.SeekCap.name+".   Yetkililer  "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" onu gerçekten görmek için sabırsızlanıyorlar. Onu tutuklayıp ambarıma kapatacağım.";
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;
		
		case "NM_prisonerBoard_1":
			dialog.text = "Ve bu yüzden mi gemimde katliam yaptın? Alçak! Hâlâ biraz gücüm var... Seni öldüreceğim!";
			link.l1 = "Daha güçlü adamlar denedi...";
			link.l1.go = "NM_prisonerBoard_2";
		break;
		
		case "NM_prisonerBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			pchar.GenQuest.mustboarding = "true";//ставим этот флаг для завершения квеста
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+21); //модель для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;
		
		//--> результаты квестов дворян
		case "SCQ_NM_result":
			dialog.text = "Ne dersiniz, kaptan? Benim meselemle ilgili bir gelişme var mı?";
			link.l1 = "Henüz değil. Ama ilgileniyorum.";
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://сдача квеста, вариант А
					dialog.text = "Ne dersin, kaptan? Benim meselemde bir ilerleme kaydedebildin mi?";
					link.l1 = "Biliyorum. Ve sen de hoşlanacaksın."+npchar.quest.SeekCap.capName+" öldü ve onun "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" denizin dibinde.";
					link.l1.go = "SCQ_NM_result_A1";
				break;
				
				case "NM_prisonerover"://сдача квеста, вариант B
					dialog.text = "Ne dersin, kaptan? Benim meselemle ilgili bir gelişme var mı?";
					link.l1 = "Ben de. Ve bundan hoşlanacaksın."+npchar.quest.SeekCap.Name+" gemimın kamarasında tutuklu olarak oturuyor.";
					link.l1.go = "SCQ_NM_result_B1";
				break;
				
				case "NM_peaceover"://сдача квеста, вариант C
					dialog.text = "Aha, buradasın. Seni gördüğüme sevindim. Görevinin üstesinden geldiğini duydum!";
					link.l1 = "Arkadaşın seni ziyaret etti mi?";
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;
		
		case "SCQ_NM_result_A1":
			dialog.text = "Harika! Sana güvenebileceğimi biliyordum. Al, altınını al. Bunu hak ettin.";
			link.l1 = "Teşekkürler. Yeni bir düşmanın olursa yine konuş benimle.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_battle";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			OfficersReaction("bad");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "SCQ_NM_result_B1":
			dialog.text = "Harika! Adamlarıma hemen onu geminizden indirmelerini emredeceğim. Artık kaçamaz! Alın, altınınız burada. Bunu hak ettiniz.";
			link.l1 = "Teşekkürler. Böyle bir iş için bana her zaman yaklaşabilirsin.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_prisoner";
			CloseQuestHeader(sTitle);
			sld = characterFromId("NM_prisoner_" + npchar.City);
			RemovePassenger(pchar, sld); // 170712
			//ReleasePrisoner(sld);
			sld.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		break;
		
		case "SCQ_NM_result_C1":
			dialog.text = "Evet, buradaydı ve senden bahsetti. Al, altınını al. Bunu hak ettin.";
			link.l1 = "Teşekkür ederim. Hoşça kalın, efendim!";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			sld = characterFromId(npchar.quest.SeekCap.capId);
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможный таймер на выход в море
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_peace";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
//<-- поисковые квесты дворян

		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("Selamlar, Kaptan. Sizden yardımınızı rica etmek isterim.","Kaptan! Bana yardım edebilir misiniz? Lütfen.","Kaptan, yardımınızı istiyorum!");
			link.l1 = RandPhraseSimple("Meşgulüm.","Aceleyleyim.");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Ne oldu?","Ne derdin var, söyle. Belki yardımcı olabilirim.");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Bir yıl önce, bir kaptan beni götüreceğine söz vermişti "+XI_ConvertString("Colony"+SelectNotEnemyColony(NPChar)+"Acc")+". Ama onun gemisindeyken beni ambarına attılar ve sonra köle olarak sattılar. Zar zor hayatta kaldım. Ölümle birkaç kez burun buruna geldim... Neyse, 'dostuma' hâlâ hayatta olduğumu hatırlatmak istiyorum."; // belamour gen
					link.l1 = "Ne demek istiyorsun? Tam olarak ne istediğini söyle.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "Karımı kaçırdılar. Bir kaptan, dediklerine göre bir korsan, ona kur yapıyordu. Karım, onun tacizleri yüzünden günlerce evden çıkamadı. Kasabanın yetkililerinden yardım istedim ama başaramadım. Ve şimdi...";
					link.l1 = "Şimdi ne olacak?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "Biliyor musun, hemşehrimi arıyorum. Üç yıl önce, daha iyi bir hayat bulmak için Avrupa'dan buraya birlikte geldik. Birbirimizi kaybettik. Ama kısa süre önce onun artık bir ticaret kaptanı olduğunu duydum! Onu kendim bulmaya çalıştım, ama başaramadım.";
					link.l1 = "Ee?";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "Onu bulmanı ve öldürmeni istiyorum. O kadar çok ölmesini istiyorum ki, yemek bile yiyemiyorum...";
			link.l1 = "Anladım... Sanırım bu konuda sana yardımcı olabilirim. Bana onun adını ve gemisinin adını söyle.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "Üzgünüm, ama ilgilenmiyorum.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = ""+npchar.quest.SeekCap.capName+" of the "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" named "+npchar.quest.SeekCap.shipName+" . Sana ödeyeceğim  "+FindRussianMoneyString(sti(npchar.quest.money))+", artı tüm mücevherlerim."; // belamour gen
			link.l1 = "Anladım. Denizde dikkatli olacağım. Hedefi bulursam... Onu ölü bilin.";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "Bu kadar para için hiçbir şey yapmam. İntikamını almak için başka bir enayi bul.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "Tam da duymak istediğim şey buydu! Oh, artık yemek yiyebilirim! Sonunda! Hemen bir şeyler yemeliyim...";
			link.l1 = "Afiyet olsun. İş bitince seni bulacağım.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "Seni yerel kilisede bekliyor olacağım.";
			link.l1 = "İyi.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = "Ben fazla tembellik ettim, o alçak karımı yakalayıp gemisine götürdü. Senden bu herifi bulmanı istiyorum!";
			link.l1 = "Hm, neden başka bir alçağa karşı savaşayım ki?";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = "Zengin değilim, ama sahip olduğum tüm değerli eşyaları size vermekten memnuniyet duyarım! Eğer eşimi kurtarıp bana getirirseniz, size ödeme yapacağım "+FindRussianMoneyString(sti(npchar.quest.money))+", bir de tüm mücevherlerim.";
			link.l1 = "Pekâlâ, varım. Detayları anlat. Onun adı, gemisi ve karının adı ne?";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "Hayır dostum, bu kadar az bir paraya bunu yapmam. Üzgünüm...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "Adı "+npchar.quest.SeekCap.name+". Ve o piçin adı "+npchar.quest.SeekCap.capName+", yüzüyor "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" named "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Bok su yüzüne çıkar, dostum. Kaptanlar ise yelken açar...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "Evet, evet, çok üzgünüm! Ben denizci değilim, umarım anlarsınız...";
			link.l1 = "Sorun değil, merak etme. Zaten işim biter bitmez döneceğim.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "Çok teşekkür ederim! Seni yerel kilisede bekleyeceğim. Ama lütfen acele et. Karım için gerçekten endişeliyim...";
			link.l1 = "Evet, ben de ona imrenmiyorum.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = "Sorun şu ki, arkadaşımın hiçbir mülkü yok. Gemisi onun evi. Bu yüzden onu bulamıyorum, çünkü sürekli denizde. Boşuna yolculuk yapacak param da yok, yaşamak için para kazanmam gerek.";
			link.l1 = "Paran yoksa sana yardımcı olamam...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Sana ödeme yapabilirim "+FindRussianMoneyString(sti(npchar.quest.money))+" ve tüm mücevherlerimi sana vereceğim. Şu anda elimden gelen sadece bu.";
			link.l1 = "Bu miktar bana uyar. Varım. Hatta istersen yolcu olarak bana katılabilirsin, böylece arkadaşını bulur bulmaz görebilirsin.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "Bu bana yetmez. Başkasını bul, o yapsın.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "Hayır, sanırım burada kalacağım. Bu aramaların ne kadar süreceğini bilmiyoruz ve tüm paramı kaybedebilirim. Burada bir işim var.";
			link.l1 = "Anladım. Şimdi söyle bakalım, arkadaşın kim ve hangi gemide?";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "Adı "+npchar.quest.SeekCap.capName+". Bildiğim kadarıyla, o bir gemiye komuta ediyor "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Acc"))+" named "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Anladım. Onu görürsem, senden bahsederim.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "Teşekkür ederim. Seni yerel kilisede bekliyor olacağım. İş bittiğinde paranı alacaksın.";
			link.l1 = "Tabii. O halde hoşça kal, yakında sonuçları bekle.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = "İyi günler kaptan. Herhangi bir sonuç var mı?";
			link.l1 = " Sorunun neydi, bir hatırlatır mısın... ";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "Anlaşılan intikamım alınmış. Öyle mi?";
					link.l1 = "Aynen öyle. "+npchar.quest.SeekCap.capName+" öldü ve onun "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" denizin dibinde.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "Karımı bulmuşsunuz! İnanamıyorum! Gerçekten mi?";
					link.l1 = "Yapabilirsin. O benim yolcum. Onu geri götürebilirsin, eğer "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+" bu gerçekten senin karın...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "Günaydın kaptan. Yoldaşımı bulabildiniz mi?";
					link.l1 = "Anlattım, senden de bahsettim.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Ne? Kaptanın intikamını almanı istediğimi gerçekten unuttun mu "+npchar.quest.SeekCap.capName+" köleliğimin bir yılı için mi?";
					link.l1 = "Hayır, etmedim.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "Kulaklarıma inanamıyorum! Sana karımı bulup kurtarmanı istediğimi unuttun mu? Onu, adı   olan bir korsan kaçırdı."+npchar.quest.SeekCap.capName+"!";
					link.l1 = "Hayır, yapmadım.";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "Bir saniye... Benim arkadaşımı bulacağına dair verdiğin sözü unuttun mu yoksa "+npchar.quest.SeekCap.capName+"?";
					link.l1 = "Hayır, yapmadım.";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "Harika, senin hakkında yanılmamışım! Söz verdiğim gibi, işte senin "+FindRussianMoneyString(sti(npchar.quest.money))+" ve mücevherler. Yardımınız için teşekkür ederim.";
			link.l1 = "Rica ederim...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "Aman Tanrım! Bizi kurtardınız! Lütfen, alın şu "+FindRussianMoneyString(sti(npchar.quest.money))+" ve mücevherler. Ve bil ki, sonsuza dek senin için dua edeceğiz!";
			link.l1 = "Dua etmek istersen et. Benim için hiçbir sakıncası yok.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "Harika!... Al, buyur "+FindRussianMoneyString(sti(npchar.quest.money))+" ve mücevherler. Ve teşekkür ederim, Kaptan.";
			link.l1 = "Hoş geldin, dostum. Hoşça kal...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("Selam, Kaptan. Bana yardım edebilir misiniz?","Kaptan! Bir bayana yardım eder misiniz? Lütfen nazik olur musunuz...","Kaptan, yardım et "+GetSexPhrase("bir kız","ben")+".");
			link.l1 = RandPhraseSimple("Meşgulüm.","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+", ama hiç vaktim yok...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Senin derdin ne, "+GetAddress_FormToNPC(NPChar)+"?","Sıkıntını anlat, "+GetAddress_FormToNPC(NPChar)+". Sana yardım etmeye çalışacağım.");
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Kocam bir tüccar, her kolonide mal teslimatı yapar. Üç ay önce denize açıldı. Hâlâ dönmedi!";
					link.l1 = "Sence ona bir şey olmuş olabilir mi?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+GetSexPhrase("Kaptan, görüyorum ki cesur bir kaptansınız, tam bir düzenbazsınız","Kaptan, görüyorum ki güçlü bir kadınsınız, her adamın üstesinden gelebilirsiniz")+"...";
					link.l1 = "Ve bunu neden söylüyorsun, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "Kaptan, lütfen bana yardım edin, yalvarıyorum! Kocam esir alındı! Onu kurtarabilir misiniz?";
					link.l1 = "Bir saniye, anlamadım. Kim kimi esir aldı?";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "I don't know, but I still hope that he is just too busy to write to me. He could have sent me a letter; he knows that I worry about him!";
			link.l1 = "Denizde güvende değilsin, her an her şey olabilir...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Kesinlikle! Ne demek istediğimi anlıyorsun. Sen de tam bir "+GetSexPhrase("cesur kaptan","cesur kız")+", bu yüzden senden kocamı bulmanı istiyorum. Sana ödeme yapmaya hazırım "+FindRussianMoneyString(sti(npchar.quest.money))+", ayrıca tüm mücevherlerimi de sana vereceğim.";
			link.l1 = "Peki. Kocanı denizde ya da başka bir yerde görürsem, endişelerini ona ileteceğim. Bana adını ve gemisinin adını söyle.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "Böylesine küçük bir miktarla ilgilenmiyorum.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "Adı "+npchar.quest.SeekCap.capName+". O bir gemide yol alıyor "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" named "+npchar.quest.SeekCap.shipName+".";  // belamour gen
			link.l1 = "Anladım. Şimdi beklemen gerekiyor. Seni bulabilmem için zamanının çoğunu kilisede geçirmeye çalış.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = ""+GetSexPhrase("Bunu söylüyorum, efendim, çünkü sizi alışık olduğunuz iş için tutmak istiyorum... tabiri caizse.","Sana ihtiyacım var. Bir kadın olarak beni anlayacağını umuyorum.")+"Bir kaptan beni sinirlendirdi ve onun ölmesini istiyorum.";
			link.l1 = "Ve o zavallı ruh sana ne yaptı?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "Bu alçak beni kandırdı. Bana âşıkmış gibi davrandı, hatta bana kur yaptı. Bütün bunları yapmasının tek nedeni, kocamdan değerli bir şey almakmış! Ve o köpek istediğini alınca, bana hiçbir anlamı olmadığını söyledi... sadece arkadaşmışız!";
			link.l1 = "Hm, belki de haklıydı?";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "Ben aptal mıyım sanıyorsun?! Flört etmekle boş laf arasında farkı ayırt edemeyeceğimi mi düşünüyorsun?";
			link.l1 = "Tabii ki biliyorsun...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "Beni kullandı, o alçak! Bunu ona asla affetmeyeceğim!";
			link.l1 = "Evet, erkekler böyledir işte. Ama belki biraz sakinleşebilirsin? Bunda korkacak bir şey yok...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "Hiçbir korkunç şey olmadı mı?! "+GetSexPhrase("Sen de tam bir ahlak bekçisiymişsin, gerçek bir korsan değilsin!","Anlaşılan, sen hiç böyle bir durumda kalmamışsın! Tabii, kim böyle bir riske girer ki... ve ben de sadece zayıf bir kadınım...");
			link.l1 = "Pekâlâ. Yeter. Sadece niyetinin ne kadar ciddi olduğunu bilmek istiyorum.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "Lanet olsun, "+GetSexPhrase(" reddedilmiş bir kadının intikamının nasıl göründüğünü sen daha bilmiyorsun ","Sen bir kadınsın ve reddedilmenin nasıl bir his olduğunu bilmelisin! İntikam istiyorum ")+"!";
			link.l1 = ""+GetSexPhrase("Doğru, böyle bir deneyimim hiç olmadı","Bilirsin, biraz ağlar, birkaç cam kırar ve sonra her şey biterdi")+"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+GetSexPhrase("Kendini şanslı say. Beklentileri boşa çıkan ve kandırılan bir kadın tam bir öfke fırtınasıdır, eteğiyle şeytan kesilir! Dünyada hiçbir şey onun öfkesini dindiremez","Ve ben onun gibi değilim. Hiçbir şey öfkemi dindiremez")+"!\nBu yüzden onu bizzat senin öldürmeni istiyorum. Ve ölmeden önce, ölümünün bedelini kimin ödediğini mutlaka bilmeli...";
			link.l1 = "Hm, ne diyeceğimi bile bilmiyorum... Peki, bana ne kadar ödeyeceksin?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Her şeyim senin olsun. Mücevherlerimi ve "+FindRussianMoneyString(sti(npchar.quest.money))+"! Anlaştık mı?";
			link.l1 = "İlgimi çekti. Bana onun adını ve gemisinin adını söyle.";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = "İlgilenmiyorum. Hoşça kal.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "O alçağın adı "+npchar.quest.SeekCap.capName+" ve o bir gemiyle yol alıyor "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Gen"))+" named "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Oldu bile, "+GetAddress_FormToNPC(NPChar)+". Beni yerel kilisede bekle. Umarım biraz sakinleşirsin...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("",""));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = "Açıklayacağım. Sorun şu ki, sıradan bir adam olan kocam korsanlar tarafından esir alındı! Herkesi öldürüyorlardı, kimseyi sağ bırakmadılar...";
			link.l1 = "Kaptan direnmeye cesaret etmiş gibi görünüyor. Yoksa mürettebatı bağışlayacaklardı.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "Perhaps so, but my husband is an innocent soul. He was merely a passenger there. He had to tell them he was wealthy in order to save his life. The pirates spared him; he wasn't even put in the cargo hold.";
			link.l1 = "Bunu nereden biliyorsun?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "Bana bir mektup göndermeyi başardı. İyi olduğunu ve diğer tutsaklar gibi değil, bir kamarada tutulduğunu yazmış.";
			link.l1 = "Ve sen ne yapmayı düşünüyorsun? Böyle devam edemez. Er ya da geç, korsanlar onun gerçek yüzünü görecek.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "Sen de korsan mısın? Evet, evet, biliyorum... Ne olur, bize yardım et, kocamı kurtar! O korsan gemisini tarif etti ve kaptanın adını yazdı. Onları bulman zor olmayacak!";
			link.l1 = "Düşündüğünüz kadar kolay değil. Tüm esirler, kocanızı yakalayan kaptanın hakkı olan ganimettir ve ayrıca bu iş zaman alacak.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "Ama en azından denemelisin! Ayrıca, aramak için yeterince vaktin var. Kocam aptal değildir, kendini Eski Dünya'dan gelen bir tüccar gibi gösteriyor, bu yüzden o korsanlar şimdilik ondan para istemiyorlar. Onu kurtarırsan, sana sahip olduğum her şeyi vereceğim!";
			link.l1 = "   Peki sende ne var? ";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Pek bir şey değil, "+FindRussianMoneyString(sti(npchar.quest.money))+" ve tüm mücevherlerim... Ama ruhun için sonsuza dek dua edeceğim!";
			link.l1 = "Evet, bu gerçekten pek bir şey değil... Peki, sana yardım etmeye hazırım.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "Üzgünüm, ama bu benim için yeterli değil.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Teşekkür ederim, çok teşekkürler!";
			link.l1 = "Eğer başarılı olursam bana teşekkür edeceksin, o yüzden dur. Kocanın adını ve o korsanlar hakkında bildiğin her şeyi anlatman daha iyi olur.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "Adı "+GetFullName(forName)+". Kaptanın "+npchar.quest.SeekCap.capName+", denize açılıyor "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" named "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Anladım. Şimdi bekleyip arayışımda başarılı olmamı ummalısın. Kilisede kal, bekle ve dua et ...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "Oh, kaptan, sizi gördüğüme çok sevindim! Şimdi söyleyin, görevimle ilgili ne haberleriniz var?";
			link.l1 = "Hmm, hatırlatsana, "+GetAddress_FormToNPC(NPChar)+", hangi görevden bahsediyorsun?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "Ah, kaptan, kocamdan bir mektup aldım! Yazdığına göre onu bulmuşsunuz.";
					link.l1 = "Evet, doğru, "+GetAddress_FormToNPC(NPChar)+". Kocanız, "+npchar.quest.SeekCap.capName+",  iyi ve sağlıklı. Sadece çok meşgul...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "Ne dersiniz, kaptan? Sizden istediğimi yaptınız mı? Kaptan "+npchar.quest.SeekCap.capName+" öldü mü?";
					link.l1 = "Evet, o öldü, "+GetAddress_FormToNPC(NPChar)+". Ona ölümünden kimin sorumlu olduğunu söyledim. Hayatında duyduğu son şey senin adındı.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "Kocamı kurtardınız! Ne olur, bana bunun doğru olduğunu söyleyin!";
					link.l1 = "Evet, öyle. Şu anda gemimde. İstersen görebilirsin "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+"gerçekten senin kocan mı...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Gerçekten de kocamı bulacağına söz verdiğini unuttun mu? Onun adı "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "Ah, evet, tabii... Unutmadım.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "Anlamıyorum! Beni inciten kaptan, yani  [[[VARx]]]  adındaki adamı öldürmen gerektiğini unuttun mu?"+npchar.quest.SeekCap.capName+"?!";
					link.l1 = "Ah lütfen, tabii ki yapmadım. Siparişiniz hazırlanıyor, lütfen bekleyin...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "Tanrım kaptan, kocamı serbest bırakma sözünü unuttun mu?";
					link.l1 = "Hayır, hatırlamıyorum. ... 'Bekle ve dua et!'. Sadece bekle, "+GetAddress_FormToNPC(NPChar)+" "+npchar.lastname+".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "Tanrım, sana minnettarım! Ve evet, al şunu "+FindRussianMoneyString(sti(npchar.quest.money))+". Ve tekrar teşekkür ederim!";
			link.l1 = "Hm, hoş geldin...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "Mükemmel! Peki, al bakalım "+FindRussianMoneyString(sti(npchar.quest.money))+" ve mücevherler. Elveda...";
			link.l1 = "Elveda. ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			TakeNItems(pchar, "jewelry47", rand(3));
			TakeNItems(pchar, "jewelry43", rand(3));
			TakeNItems(pchar, "jewelry41", rand(3));
			TakeNItems(pchar, "jewelry48", rand(3));
			TakeNItems(pchar, "jewelry51", rand(3));
			TakeNItems(pchar, "jewelry46", rand(3));
			TakeNItems(pchar, "jewelry49", rand(3));
			TakeNItems(pchar, "jewelry40", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "Eminim o! Tanrım kaptan, size minnettarım. Alın sizin "+FindRussianMoneyString(sti(npchar.quest.money))+". Hayatımın her günü senin için dua edeceğim!";
			link.l1 = "Kulağa hoş geliyor...";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Meslektaşıma selamlar. Bir şey mi istiyorsun"+GetSexPhrase(", dostum ",",  kız")+"?";
					link.l1 = "Adınız "+GetFullName(npchar)+", değil mi?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "Evet, öylesin!";
			link.l1 = "Sana yazık. Sana bir isim söyleyeceğim, aklında tutsan iyi edersin."+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"  Onu hatırlıyor musun?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "Hm, evet...";
			link.l1 = "Şimdi dinle, sana çok kızgın, dostum. Özgür bir adamı köleliğe sattığın için bedelini ödeme zamanı geldi.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "Ödemek mi?! Ne saçmalıyorsun sen, lanet olsun?";
			link.l1 = "Seni tam da olduğun yerde öldüreceğim demek istiyorum.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "Bir düşün, kimin için çalışıyorsun?! Bu adam rezil biri ve yeri şeker plantasyonunda!";
			link.l1 = "Bu seni ilgilendirmez. Şimdi yaptıklarının hesabını vermelisin!";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "Ho! Cevabımı her zamanki gibi vereceğim!";
			link.l1 = "Devam et...";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Sana bir şey sormak istiyorum, yolcu alıyor musun? ";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "Ve bu seni neden ilgilendiriyor?";
			link.l1 = "Sadece soruyorum.";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "Sadece soruyorum... Bak, sana hâlâ bu fırsatı veriyorken buradan gitmen en iyisi olur. Senden hoşlanmıyorum!";
			link.l1 = "Pekala, pekala, sakin ol. Gidiyorum...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "Zaten konuştuk, o yüzden beni sınama!";
			link.l1 = "Yapmayacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Selamlar, meslektaşım! Bir şeye ihtiyacın var mı?";
			link.l1 = "Bilmek isterim, kadını sen mi götürdün "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" named "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "Heh, doğru söylüyorsun, o benim kamarada! Güzel kız, bu arada bacakları da harika... Neden soruyorsun?";
			link.l1 = "Dostum, bu kadın evli. Bu doğru değil.";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "Ee, ne olmuş yani? Ondan hoşlanıyorum, hepsi bu. Sırf kocası diye, üstü başı dökülmüş bir aptalın ilişkimizi bozmasına izin vermem!";
			link.l1 = "Sana şunu söyleyeyim, Kardeşlik böyle şeyleri onaylamaz ve bazı kişiler yaptıklarını duyarsa, kara işaret sana gönderilir.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "Bana vaaz mı vermeye başlayacaksın?";
			link.l1 = "Sakin ol, sadece biraz ilgi gösteriyordum... Hoşça kal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "Kadın hakkında zaten konuştuk. Bu meseleyi tekrar konuşmak istemiyorum!";
			link.l1 = "Her neyse...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Güvertemde bir meslektaşı ağırlamaktan memnuniyet duyarım! Ne istiyorsun?";
			link.l1 = "Bir kadını buradan kaçırıp kaçırmadığını bilmek istiyorum "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" adında "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "Heh, doğru söylüyorsun, o benim kamarada! Güzel kız, bu arada bacakları da hoş!... Neden soruyorsun?";
			link.l1 = "Dostum, bu kadın evli. Bu doğru değil.";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "Ne olmuş yani? Ondan hoşlanıyorum, hepsi bu. Sırf kocası diye, o perişan adamın ilişkimize karışmasına izin vermem!";
			link.l1 = "Sana şunu söyleyeyim, Kardeşlik böyle şeyleri hiç hoş karşılamaz, ve eğer bazı kişiler yaptıklarını duyarsa, kara işaret sana gönderilir.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "Bana vaaz mı vermeye başlayacaksın?";
			link.l1 = "Sakin ol, sadece biraz ilgi gösteriyordum... Hoşça kal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Benden ne istiyorsun, pislik?!";
			link.l1 = "Ben buraya, kocasından çaldığın kadın için geldim. Hatırla "+XI_ConvertString("Colony"+npchar.quest.cribCity)+"? Adı neydi "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "Lanet olsun! Onu asla göremeyeceksin, tıpkı kendi kulaklarını göremeyeceğin gibi!";
			link.l1 = "Salak. Onları aynada görebiliyorum. Ve seninkini de keseceğim!";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "women_"+(hrand(3)+7); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = "Sen kimsin?";
			link.l1 = "Merhaba. Kocanızın isteği üzerine sizi bulmaya geldim. Artık özgürsünüz, sizi ona götürebilirim.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "Bu bir rüya mı?! Gerçek mi?!";
			link.l1 = "Öyle, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "Tanrı'ya şükür! Hazırım, hadi buradan uzaklaşalım!";
			link.l1 = "Tabii, "+GetAddress_FormToNPC(NPChar)+", kocana güvenli bir şekilde dönmeye hazırlan.";
			link.l1.go = "exit";
			//уберем жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = "Merhaba! Karada bir dostla karşılaşmak ne güzel...";
			link.l1 = TimeGreeting()+", seninle biraz işim var.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "Dinliyorum.";
			link.l1 = "Senin bir arkadaşın seni arıyor. Birlikte yelken açıp Eski Dünya'dan buraya geldiniz."+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+", hatırlıyor musun?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "Ha, tabii ki biliyorum! Peki, şimdi nerede yaşıyor?";
			link.l1 = "In "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat");
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = " Teşekkür ederim! Biliyor musun, seni bir korsan sanmıştım!";
			link.l1 = "Benim. Bir bakıma. Belki de değilim. Ama neyse, bugün keyfim yerinde, endişelenecek bir şeyin yok. Hoşça kal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "Bir sorun mu var? Üzgünüm, biraz gerginim...";
			link.l1 = "Sorun yok, dostum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting()+" . Benden ne istiyorsun? Ben sadece mütevazı bir tüccarım ve...";
			link.l1 = "Biliyorum dostum. Bu kadar endişelenme, sağlığa zararlı derler. Seninle konuşmam gereken bir işim var.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "Ne işten bahsediyorsun?";
			link.l1 = "Bir arkadaşın seni arıyor. Adı "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+" . Onu tanıyor musun?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "Ah, sonunda! Bu harika... Böyle kaba bir karşılama için özür dilerim, ama seni bir korsan sandım.";
			link.l1 = "Benim. Bir bakıma. Ya da belki de değilim. Ama neyse, bugün keyfim yerinde, o yüzden endişelenecek bir şeyin yok. Sana bir mesaj iletmem istendi ve işimi yaptım. Dostun şurada yaşıyor "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+"."; // belamour gen
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "Bu da bir şey! Gerçekten onurlu bir adamsın. Teşekkür ederim!";
			link.l1 = "Rica ederim. Hoşça kal, kendine iyi bak, dostum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = "Merhaba. Bir şey mi istiyorsunuz?";
			link.l1 = "Adınız "+GetFullName(npchar)+", değil mi?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "Evet, benim.";
			link.l1 = "Saçma gelebilir, ama eşiniz sizin için endişelendiğini bana iletmemi istedi.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "Ha! Anlıyorum... Aslında çok meşguldüm, kârlı tekliflerim çok ve sırf karım fazla endişeleniyor diye potansiyel kazancımı kaybedemem.";
			link.l1 = "Ama en azından ona bir mektup yazıp iyi olduğunu söyleyebilirsin.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "Evet, haklısınız. Ona hemen yazacağım! Aile meselelerimize dahil olduğunuz için teşekkür ederim!";
			link.l1 = "Hoş geldin, dostum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = "Günaydın. Size nasıl yardımcı olabilirim?";
			link.l1 = "Adınız "+GetFullName(npchar)+", değil mi?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Evet, benim.";
			link.l1 = "Belki saçma gelebilir, ama eşiniz sizin için endişelendiğini bana iletmemi istedi.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Fuh, kahretsin! O meşhur ödül avcısı, Tek Göz Steve, beni bulmaya geldi sandım. Neyse ki yanılmışım\nBakın, işimle o kadar meşgulüm ki ona hiç vakit ayıramıyorum. Sürekli kârlı teklifler geliyor ve sırf karım endişeleniyor diye bunları reddedemem.";			
			link.l1 = "Elbette haklısın. Ama en azından ona bir mektup yazıp iyi olduğunu söyleyebilirsin.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Evet, haklısınız. Bunu ilk limanda yapacağım... Aile meselelerimize dahil olduğunuz için teşekkür ederim!";
			link.l1 = "Hoş geldin, dostum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "Sana minnettarım, Kaptan...";
			link.l1 = "Rica ederim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "Sizi bu kasabada görmek güzel, kaptan. Benden bir isteğiniz var mı?";
			link.l1 = ""+GetSexPhrase("Biliyor musun, kaptan... Off, nasıl desem bilemiyorum!","Evet, var.")+"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+GetSexPhrase("Olduğu gibi söyle.","İlginç, peki nedir bu?")+"";
			link.l1 = " Sana bir sorum var.  [[[VAR1]]] adında bir kadını tanıyor musun? "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "Heh, biliyorum. Onu tanıdığım için şanssızdım. Aptal bir kızdı, sana söyleyeyim...";
			link.l1 = "Hm... Evet, ve bu aptal kız benden seni öldürmemi istedi. Hepsi bu....";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "Saçmalık.";
			link.l1 = ""+GetSexPhrase("Katılıyorum. Affınıza sığınırım, fakat başınıza ödül konmuş.","Hayır, öyle değil. Bir ödül var")+". Ve onu alacağım.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "Ho-ho!... Şaka mı yapıyorsun, kaptan?";
			link.l1 = ""+GetSexPhrase("Hayır, dostum.","Zaten öyle bir niyetim yoktu!")+"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+GetSexPhrase("Sen benim dostum değilsin, ahmak! Kendine kaptan bile diyemezsin. Sadece bu aptal öfkenin oyuncağısın!","Lanet olsun! Bir cadı başka bir cadıyı tutmuş! Bu dünyada neler oluyor böyle?")+"!";
			link.l1 = ""+GetSexPhrase("Ağzını topla, pislik.","Onu kullandın, bu yüzden intikam almaya karar vermesine şaşırma.")+"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+GetSexPhrase("Bir yarana mı dokundum?","Kadın dayanışması?!")+"";
			link.l1 = "Bunu bitirelim!";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "Seninle zaten konuştum. Defol git, aptal!";
			link.l1 = "Aptal mı dedin?! Peki o zaman...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "Sizi gemide görmek güzel, kaptan. Ne istiyorsunuz?";
			link.l1 = "Sana bir sorum var.  Tanıdığın bir kadın var mı, adı "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "Heh, biliyorum. Onu tanıdığım için şanssızdım. Aptal bir kızdı, sana söyleyeyim...";
			link.l1 = "Evet, ve bu aptal kız benden seni öldürmemi istedi.";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "Kaptan, beni güldürme. Eğer bana söyleyecek ciddi bir işin yoksa, o zaman hoşça kal.";
			link.l1 = "Öyleyse elveda. Ama sana söylediklerimi bir düşün.";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "Elbette, kaptan, başka nasıl olabilirdi?!";
			link.l1 = "Elveda.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "Bu konuyu daha fazla konuşmak istemiyorum, kaptan. Bu gerçekten fazlasıyla saçma.";
			link.l1 = "Sen nasıl istersen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "Burada ne oluyor böyle?! Neden gemime saldırdınız?";
			link.l1 = "   Bir hanımefendinin isteği üzerine  "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+" . Onu tanıyor musun?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "Ne oluyor! Buna inanamıyorum...";
			link.l1 = "Yapmalısın! Kadınları bilmiyor musun, dostum? Isırabilirler.";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "Pekâlâ, öylece ölüp gitmeyeceğim. Sohbet için teşekkürler, şimdi biraz güç topladım.";
			link.l1 = "Sana bir faydası olmayacak.";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Seni gemide görmek güzel. Sana yardımcı olabilir miyim?";
			link.l1 = "Yapabilirsin.  Ben de  adını aradığım bir adamı bulmaya çalışıyorum "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "Bu adam benim esirim ve onu fidye karşılığında serbest bırakmayı planlıyorum.";
			link.l1 = "Onu almak istiyorum.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "Maalesef, bu imkânsız. Eğer başka bir şey yoksa, gemimden ayrılmanızı rica edeceğim.";
			link.l1 = "Peki, kaptan, nasıl istersen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCapCap_exit":
			dialog.text = "Tutsak hakkında zaten konuştuk. Hiçbir şey değişmedi.";
			link.l1 = "Anladım...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Sizi tanıdığıma memnun oldum. Size yardımcı olabilir miyim?";
			link.l1 = "Buyurun.   Ben   adını   aradığım   bir   adamı   bulmaya   çalışıyorum. "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "Bu adam benim esirim ve onu fidye karşılığında serbest bırakmayı planlıyorum.";
			link.l1 = "Onu almak istiyorum.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "Üzgünüm, ama bu mümkün değil.";
			link.l1 = "Ne yazık...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Lanet olsun! Ne oluyor böyle?!";
			link.l1 = "İçerideki tutuklunuzun adını istiyorum "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ha! Asla, ancak cesedimi çiğnersin!";
			link.l1 = "Madem sordun...";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+11); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = "Sen kimsin?";
			link.l1 = "Ben kaptanım "+GetFullName(pchar)+" . Merak etme, seni karına götürmek için buradayım.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "Lanet olsun, herhalde rüya görüyorum!";
			link.l1 = "Sana bunun böyle olmadığını temin edebilirim... Neyse, artık her şey bitti, hadi seni buradan uzaklaştıralım.";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Çok yoruldum, bana yardım et.","Artık böyle yaşamaya gücüm kalmadı!"),RandPhraseSimple("Bu iş bizi bitiriyor.","Lanet olası muhafızlar sırtımda deri bırakmadı!"));				
				link.l1 = RandPhraseSimple("Ne yazık.","Evet, hayat tam bir bela.");
				link.l1.go = "exit";				
    		} 
		break;
		
		//=====================================================================================================================================
		// Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
		//=====================================================================================================================================
		case "AffairOfHonor_1":
			LAi_CharacterDisableDialog(NPChar);
			
			if(LoadedLocation.type == "tavern")
			{
				// "Честь мундира".
				if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
				{
					dialog.text = "Ah kaptan, gel yanıma otur. Ben ısmarlıyorum!";
					link.l1 = "Memnuniyetle.";
					link.l1.go = "AffairOfHonor_CoatHonor_1";
					PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
					break;
				}
			}
			else
			{
				if(NPChar.sex == "man")
				{
					// "Невольник чести".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
					{
						dialog.text = "Merhaba, kaptan. Siz bir kaptansınız, değil mi? Belki de donanma kaptanısınız?\nEvet, siz kesinlikle kılıç kullanmada ustasınız, benim işe yaramaz oğlumun aksine... O yarın ölecek, hepsi de oğlumun gönlünü kaptırdığı hanıma göz diken o arsız herif yüzünden!";
						link.l1 = "Evet, kaptanım ve kılıcım beni defalarca kurtardı, ama senin o karamsar konuşmanın geri kalanı ne olacak? Açıklamak ister misin?";
						link.l1.go = "AffairOfHonor_HonorSlave_1";
						PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;
					}
					
					// "Красотка и пират".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
					{
						dialog.text = "Selamlar, kaptan. Söylesene, acaba korsan mısın? Ah, tabii ki hayır! Sen değilsin. Korsanlar korkunç görünür, hayvan gibi davranır ve o pis koku...";
						link.l1 = "Korsanlara karşı bir kin besliyor musun?";
						link.l1.go = "AffairOfHonor_BeautifulPirate_1";
						PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
						break;
					}
					
					// "Заносчивый нахал".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
					{
						//if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
						//{
						// Jason: что за чудное условие? Типа - столица? Кроме Гаваны, квест более нигде не выпадет - остальные города непригодны априори. Убираю. Неразумно ограничивать одним городом.
							dialog.text = "Hey, sen! Evet, sen, söyle bakalım, nerede senin terbiyen? Ne diye burada dikilip beni rahatsız ediyorsun? Şuna bak hele, ne budala! Sana söylüyorum! Çekil yolumdan! Burada fazla yabancı var!";
							link.l1 = "Sakin ol, seni rahatsız etmek istemedim. Affedersin.";
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = "Diline dikkat et, yoksa onu keserim, sayın bayım.";
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
							break;
						//}
					}
					
					// "Волки и овцы".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
					{
						dialog.text = "Selamlar, kaptan. Sizden bir ricam olacak. Eğer onurlu bir insansanız, kenara çekilmezsiniz.\nO yüzden lafı uzatmadan söyleyeyim: Bir ay önce bir soylu bizim meyhanede kaldı. Meğer ahlaksızın ve alçağın tekiymiş! Üstelik bir de katil!";
						link.l1 = "Hatırladığım kadarıyla, masum birini öldürmenin cezası darağacı. Serseri ve piç olmanın da mahkemede pek işine yaramaz. Yanılıyor muyum?";
						link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
						PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;
					}
					                                                                                                                                                
					// "Трусливый фехтовалщик".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
					{
						dialog.text = "Kaptan, lütfen bekleyin, size yalvarıyorum. Oldukça yetenekli bir silahşöre benziyorsunuz, benden çok daha iyisiniz. Bu yüzden yerime geçmenizi rica etmek istiyorum.";
						link.l1 = "İlginç. Devam et.";
						link.l1.go = "AffairOfHonor_CowardFencer_1";
						PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;
					}
					
					// "Божий суд".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
					{
						dialog.text = "Lütfen, yalvarıyorum, gitmeyin! Bekleyin... Böylesine cesur bir subayın müdahalesini gerektiren bir meselede zavallı birine yardım etmez misiniz?\nMesele şu ki, komşumla buradaki üzüm bağları hakkında bir tartışma yaşadım. Bu arada, kendisinin kaçakçılarla işbirliği yaptığına dair şüpheler var. Evet, evet, hatta korsanlarla da bağlantısı olabilir—başka türlü bu kadar kısa sürede nasıl böyle bir servet edinebilir ki?\nDaha bir yıl önce elinde sadece bir barque vardı, şimdi ise benim bağlarımı almak istiyor, duyuyor musunuz?! Benim bağlarımı!";
						link.l1 = "Bağlarınız için üzgünüm. Gerçekten. Hoşça kalın.";
						link.l1.go = "exit";
						link.l2 = "Affedersiniz, ama yerel yetkililere başvuramaz mısınız?";
						link.l2.go = "AffairOfHonor_GodJudgement_1";
						PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
						break;
					}
				}
				else
				{
					// "Навязчивый кавалер".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
					{
						dialog.text = "Kaptan, kaptan, yalvarırım! Masum bir kızın onurunu koruyun!";
						link.l1 = "Benim buna vaktim yok, güzelim. Başkasını bul...";
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = "Selamlar, hanımefendi. Böyle titremeyin! Ne oldu?";
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
			
			dialog.text = "Hata. Geliştiricilere bildirin.";
			link.l1 = RandSwear();
			link.l1.go = "exit";
		break;
		
		case "AffairOfHonor_Exit":
			ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		case "AffairOfHonor_Cavalier_1":
			dialog.text = "Kaptan, garnizonumuzdan bir subay tarafından en açık şekilde takip ediliyorum. Hakkımda yaydığı iğrenç dedikoduları duymuş olmalısınız, beni utandırmaya çalışıyor!\nNe yazık ki, namusumu koruyacak bir dostum yok! Çok çaresizim! Tanrım, işte o! Lütfen yardım edin!";
			link.l1 = "Merak etme, sonuna kadar götüreceğim.";
			link.l1.go = "exit";
			int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_14"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
			float Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, PChar, "", -1, 5);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
			PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
			DisableAllExits(true);
		break;
		
		case "AffairOfHonor_Cavalier_2":
			dialog.text = "Ah, işte buradasın, hanımefendi! Yine bir başka şövalye, öyle mi? Ne zaman uslanacaksın? Belki de asla... Git geneleve çalış, orası tam sana göre bir yer...";
			link.l1 = "Subay, ağzından hakaretler saçmayı bırak yoksa seni kendi yöntemimle sustururum!";
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;
		
		case "AffairOfHonor_Cavalier_2a":
			dialog.text = "Hm... Sen kimsin? A-ah, denizin kendisiyle yoğrulmuş, küçük bir teknenin cesur kaptanı, değil mi? Peki ne yapacaksın, deniz... yavrusu?";
			link.l1 = "Bu hanımefendi benim dostum! Ve senin için de bir eldivenim var!";
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;
		
		case "AffairOfHonor_Cavalier_3":
			dialog.text = "Ne?! Bu konuda benimle yüzleşmeyecek misin...";
			link.l1 = "Yeter! İki saat sonra seni deniz fenerinin yanında bekliyor olacağım. Ve kılıcını getirmeyi sakın unutma!";
			link.l1.go = "AffairOfHonor_Cavalier_4";
		break;
		
		case "AffairOfHonor_Cavalier_4":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DisableAllExits(false);
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "1");
		break;
		
		case "AffairOfHonor_Cavalier_5":
			dialog.text = "Ah, her şeyi biliyorum efendim! Size ne kadar minnettar olduğumu tahmin bile edemezsiniz! Tanrı sizi korusun!";
			link.l1 = "Sana yardımcı olabildiğim için mutluyum. İyi şanslar!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar, "nobility", 7);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Cavalier_6":
			dialog.text = "Ah, sen de diğerleri gibisin, bırak beni!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1) sTemp = "or in the brothel ";
			dialog.text = "Ah, "+GetAddress_Form(NPChar)+"... Umut etmeye bile cesaret edemiyorum, ama belki bu kez kılıcınız ailemi koruyabilir mi?\nDediğim gibi, oğlum bir dövüşçü değil, ama gün doğarken düelloya çıkmak zorunda. Ah, şu kadını ve lanet olası onuru olmasaydı\nAma geri çekilemedi, şimdi ise mahvoldu, bunu göremiyor musunuz? Umutsuzum—o benim tek oğlum ve varisim, bu yüzden yalvarıyorum, oğluma meydan okuyan o alçağı şafaktan önce öldürün. Karşılığını fazlasıyla alacaksınız, söz veriyorum!\nAdamı meyhanede bulacaksınız "+sTemp+" - orada, onun gibi heriflerin boş vakitlerini geçirdiği yerde... Ne olur, yalvarırım...";
			link.l1 = "Ne seninle ne de oğlunla ilgileniyorum. Bırak beni gideyim!";
			link.l1.go = "exit";
			link.l2 = "Hm ... Öyle mi yani? Peki, bakalım nasıl bitecek.";
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;
		
		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = "Oğluma gerçekten yardım edecek misiniz? Ah, "+GetAddress_Form(NPChar)+"! Senin ve şansının yolunda gitmesi için dua edeceğim!";
			link.l1 = "Bunda bir sakınca görmüyorum... Beni bekle!";
			link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;
		
		case "AffairOfHonor_HonorSlave_2":
			DialogExit();
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
			Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04","blade_06"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			if(rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
			{
				FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
				ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
				LAi_SetSitType(sld);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
				LAi_SetCitizenType(sld);
			}
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "3");
		break;
		
		case "AffairOfHonor_HonorSlave_3":
			dialog.text = "Benden ne istiyorsun? Burada dinlenmeye çalışıyorum ve rahatsız edilmek istemiyorum. Boş yer de çok, dinleyecek insan da var, o yüzden beni rahat bırak, beyefendi!";
			link.l1 = "Ne yazık ki, dinlenmenizi daha iyi zamanlara ertelemek zorunda kalacaksınız.";
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;
		
		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = "Ne?! Sen de kimsin bana ne yapacağımı söyleyecek?!";
			link.l1 = "Beni unuttun mu, ha? Ama ben seni unutmadım! Demek istediğim şu ki, senin gibi alçaklar, sadece varlıklarıyla bile dünyamızı zehirliyor!";
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;
		
		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = "Ha?! Denizci, galiba fazla sarhoşsun! Seni ilk kez görüyorum! Ama bu davranışını görmezden gelmeyeceğim! Bu, sefil hayatını kurtarmak için son şansın! Hemen özrünü dile, şişkin ringa, yoksa küstahlığını unutmayacağım!";
			link.l1 = "Ben bahanelerimi sadece onurlu adamlara yaparım, pis domuzlara değil!";
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;
		
		case "AffairOfHonor_HonorSlave_4":
			dialog.text = "Ne oluyor lan?! Bela mı arıyorsun, tuvalet faresı?";
			link.l1 = "Kendi sözlerinle o lanet ağzını kapatacağım, fare! İki saat içinde deniz fenerinin yanında seni bekliyor olacağım, ve o kemerinde taşıdığın paslı hurdayı getirmeyi sakın unutma!";
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;
		
		case "AffairOfHonor_HonorSlave_5":
			dialog.text = "Ha! Orada olacağım!";
			link.l1 = "Yakında görüşürüz!";
			link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;
		
		case "AffairOfHonor_HonorSlave_6":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			AddQuestRecord("AffairOfHonor", "3_1");
		break;
		
		case "AffairOfHonor_HonorSlave_7":
			dialog.text = "Ah, sen misin! Hayattasın, yani demek ki...";
			link.l1 = "Evet, öyleyim, ve oğlunuzun yarın sabah düelloya çıkmasına gerek yok...";
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;
		
		case "AffairOfHonor_HonorSlave_8":
			dialog.text = "Böyle güzel bir gün! Hemen gidip karıma bu iyi haberi vermeliyim!\nKaptan, kader sizi bana yardım etmek için gönderdi. Alın şu paraları ve ailemizin minnettarlığını kabul edin!";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(iTemp)+"");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_9":
			dialog.text = "Defol, çocuk katili!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = "Ben mi? Tanrıya şükür, ben iyiyim ama kız kardeşim o kadar şanslı değil. Bir meyhanede çalışıyor.\nOraya sık sık gelen bir korsan var, çok tehlikeli biri. Korsan! Gemisi en az bir haftadır denizdeymiş. Adam içiyor, insanları tehdit ediyor ve onunla konuşmaya çalışan herkesi öldüreceğini söylüyor. En kötüsü, kız kardeşim bana onun, isteklerini yerine getirmezse onu kaçırıp Tanrı bilir nereye götüreceğiyle övündüğünü anlattı!\nNe yapacağımı bilmiyorum! Yetkililer bir hizmetçi kız için kılını kıpırdatmaz, benim gibi sakin insanlar ise bu korsandan korkuyor. Lütfen, bize yardım edin, ondan kurtulmamıza yardım edin!";
			link.l1 = "Meyhanede sarhoşları sakinleştirecek vaktim yok. Komutanla konuş, böyle meseleleri çözmesi için ona para veriyorlar.";
			link.l1.go = "exit";
			link.l2 = "Hm, tehditkâr bir korsan mı? Peki, onunla ben ilgileneceğim.";
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = "Ah, teşekkür ederim kaptan! Eminim o da bir denizcinin başka bir denizciyi dinlediği gibi sizi dinleyecektir! Kız kardeşimi sonsuza dek rahat bıraksın! Zengin değiliz ama zahmetinizin karşılığını iyi ödeyeceğiz!";
			link.l1 = "Pekala, pekala... Sorunlarını çözmeye gidiyorum. Beni bekle!";
			link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1_1":
			DialogExit();
			NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
			npchar.lifeday = 3;
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 25+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "5");
		break;
		
		case "AffairOfHonor_BeautifulPirate_r":
			dialog.text = "Peki ne olmuş? O korsanla konuştun mu? Bizi rahat bırakacak mı?";
			link.l1 = "Biraz bekle. Hallediyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;
		
		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = "Ne istiyorsun? Görmüyor musun, burada dinlenmeye çalışıyorum?";
			link.l1 = "Vay vay... Karşımızda bira bardaklarının büyük efendisi, kızların baş belası ve bu küçük kasabanın fırtınası, değil mi? Peki, kasabanın dışında da böyle cesur olur muydun? Fenerin orada, iki saat sonra, düello?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = "Oh-ho-ho! Kahraman mı taklidi yapıyorsun? Neyse dostum, bugün keyfim yerinde, seni affediyorum. Hadi git bana birkaç bardak bira al!";
			link.l1 = "Ben senin dostun değilim. Senin gibi bir aptala kendimi tekrar mı etmeliyim? Meyhaneye gelmekte gösterdiğin cesareti düelloya gelmekte de gösterebilecek misin?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;
		
		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = "Bana meydan mı okuyorsun?! Neyin var senin? Hayattan sıkıldın mı, ölmek mi istiyorsun, köpek herif? Peki, madem gerçekten bunu istiyorsun, fenerin oraya kadar yürüyeceğim, bağırsaklarını deşecek, sonra da şu lanet meyhaneyi yerle bir edeceğim!";
			link.l1 = " Laf ucuzdur, kılıçlar değil, o yüzden yanına bir tane almayı unutma! ";
			link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;
		
		case "AffairOfHonor_BeautifulPirate_4":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_5":
			dialog.text = "Ee, ne olmuş yani? O korsanla konuştun mu? Bizi rahat bırakacak mı? Kız kardeşim, meyhaneden çıkıp bir daha geri dönmediğini söyledi...";
			link.l1 = "Konuşmamız oldu. Adam biraz kabaydı, ama söylediklerim oldukça mantıklı ve ikna ediciydi. Kız kardeşinin artık korkacak bir şeyi yok.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;
		
		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = "Bu... bitti mi? Artık rahatça nefes alabilir miyiz? Teşekkürler, kaptan! Peki... o alçak nerede??";
			link.l1 = "O... o gemisinde. Bu kasabadan bir an önce ayrılmaya karar verdi.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;
		
		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = "Bu koloninin vatandaşlarına büyük bir iyilik yaptınız! Alın, bu ödül sizin yardımınız için! Oldukça mütevazı, ama tüm dostlarımın saygısını kazanacaksınız ve inanın bana, dostlarım çoktur!";
			link.l1 = "Teşekkür ederim! Sana ve kız kardeşine bol şans. Umarım onurlu bir adamla evlenir. Hoşça kal!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Jackanapes_1":
			dialog.text = "Gerçekten mi? Peki, beni durdurmayı nasıl düşünüyorsun?";
			link.l1 = "Tabii ki kılıcımla, senin gibi küstah bir domuz için başka uygun bir yol yok.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;
		
		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = "Harika! İki saat içinde seni deniz fenerinin yakınında bekliyor olacağım.";
			link.l1 = "Güzel! Kesinlikle orada olacağım.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;
		
		case "AffairOfHonor_Jackanapes_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			NPChar.id = "AffairOfHonor_Jackanapes_Man";
			LAi_SetImmortal(NPChar, true); // Еще успеем.
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "7");
		break;
		
		case "AffairOfHonor_Jackanapes_2":
			dialog.text = "Çekil önümden, korkak!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = "Kaptan, o herif o kadar basit biri değil. Tom, eski dostum, onunla düelloda öldü, kart hilesiyle suçlandı! Masumdu, yemin ederim. Ama vali, o lanet düelloda suç olmadığını söyledi.";
			link.l1 = "Hm...   Her şey senin arkadaşının suçu. Kart hileciliği sağlığın için kötü sonuçlanabilir.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = "Öyle mi? Son iki haftada kasabamızda dört hilebaz kartçı çıktı zaten. Ve hepsi de bizim soylumuzu dolandırmaya çalışıyormuş, öyle mi? Ne dersin buna? Aslında demek istediğim şu: O soylu dediğin adamın kendisi kartçı. Bana inanmıyorsan, git kendin gör.";
			link.l1 = "Onunla kumar mı oynayacaksın? Hayır, kumar oynamayı sevmem. Asla olmaz.";
			link.l1.go = "exit";
			link.l2 = "Sanırım bunu yapacağım... Burada bir gariplik var.";
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = "Kaptan, arkadaşlarım ve ben o soyluyu ortaya çıkaracak ve yaptıklarının hesabını soracak adama ödemek için bir miktar para topladık. İş bitince ödülünüzü vermek için şehirde sizi bekliyor olacağım.";
			link.l1 = "Eğer söylediğin doğruysa, bunu yapacağım.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_4":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			sld.skill.Fortune = 1;
			sld.Default = NPChar.city + "_tavern";
			sld.Default.group = "sit";
			sld.Default.ToLocator = "sit_front1";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "9");
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_5":
			dialog.text = "Saygılarımı sunarım, efendim! Karşımda bir soylu görüyorum ve belki de... bir kumarbaz? Bir oyun ister misiniz?";
			link.l1 = "Tabii! Bahisleri konuşalım. 50 sikke nasıl olur?";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_6":
			if(sti(PChar.money) < 200)
			{
				dialog.text = "Şaka mı yapıyorsun? Onlar sende yok ki!";
				link.l1 = "Haklısın...";
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
			}
			else
			{
				dialog.text = "Bahis önemsiz, kumar oynayacağız, işin en güzel yanı da bu. Şu yerel aptallar sayesinde kartların nasıl göründüğünü neredeyse unutuyordum.";
				link.l1 = "Pekala, başlayalım.";
				link.l1.go = "exit";
				PChar.QuestTemp.friend_in_tavern = NPChar.id;
				AddDialogExitQuest("alc");
				DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
				SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_7":
			dialog.text = "Yani, bahis 50 altın.";
			link.l1 = "...";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
			PChar.GenQuest.Cards.npcharIdx = NPChar.index;
			PChar.GenQuest.Cards.iRate = 50;
            PChar.GenQuest.Cards.SitType = true;
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_8":
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_9":
			dialog.text = "Bir dakika, bu da ne?.. İmkansız! Bayım, siz bir sahtekârsınız! Paralarımı geri verin!";
			link.l1 = "Beni suçlamak için sağlam nedenlerin olmalı,  "+GetAddress_FormToNPC(NPChar)+". Onları hemen vurmazsan, bu bir düello olur!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = "Ah, öyle mi diyorsun? Peki, o zaman düello! Bugün, iki saat sonra, deniz fenerinin orada!";
			link.l1 = "Anlaştık!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_11":
			AddDialogExitQuest("exit_sit");
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_12":
			dialog.text = "Bir haber var mı, kaptan?";
			link.l1 = "Sen haklıydın, beni de hile yapmakla suçladılar, bu yüzden o alçağı düelloda yere sermek zorunda kaldım.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = "Bak şimdi? Bunu biliyordum! Bana ve arkadaşlarıma büyük bir iyilik yaptın! Al, ödülünü al kaptan.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_1":
			dialog.text = "Did I tell you that I have come here to apply for a fencing tutor position? No? Well, the local governor is looking for a tutor for his nephew, and it suits me just perfectly. I know the basics of this art, though I have never tried it in practice.\nI almost had the job in my pocket, but it turned out that the local merchant has run into trouble; some dangerous-looking rascal is threatening him. The governor ordered me to deal with this matter to test my professional skills.";
			link.l1 = "O halde yap. Elveda.";
			link.l1.go = "exit";
			link.l2 = "Bu alçak tüccardan ne istiyor, peki beni neden istiyorsun?";
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;
		
		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = "Adamın bir paralı asker olduğunu sanmıştım, paralı askerlerle her zaman bir anlaşmaya varabilirsin. Eski borçlar falan... Ama tüccara baskı yapmaya devam etmekte kararlıydı. Senden, tüccarı ve beni o paralı askerden kurtarıp valinin emirlerini yerine getirerek bize yardım etmeni isteyecektim.\nBu mevkiye gerçekten ihtiyacım var ve paralı askerden tek başıma kurtulamam. Lütfen bana yardım et, biriktirdiğim bütün parayı sana vereceğim, yoksa utanç içinde şehri terk etmek zorunda kalacağım!";
			link.l1 = "Peki, peki, sana yardım edeceğim... 'eskrim ustası'.";
			link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;
		
		case "AffairOfHonor_CowardFencer_1_2":
			DialogExit();
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
			Scl = 30+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_"+(rand(7)+23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06","blade_10"), RandPhraseSimple("pistol4","pistol6"), "bullet", Scl*3+70);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "11");
		break;
		
		case "AffairOfHonor_CowardFencer_2":
			dialog.text = "Ne istiyorsun? Meşgul olduğumu görmüyor musun?!";
			link.l1 = "Saygın bir tüccarı rahatsız edip ortalığı birbirine mi katıyorsun!?";
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_CowardFencer_3":
			dialog.text = "Bah! Bir koruyucu daha mı? Her gün muhafız tutmaktan bana ödeme yapmak daha ucuza gelir. Borç tahsil etmek dışında adam öldürmekten pek hoşlanmam, yani madem bu kadar kahramansın, deniz fenerine gel de birbirimizi düelloda sınayalım. Yok eğer değilsen, bir daha yoluma çıkma.";
			link.l1 = "Anlaştık! Orada seni bekliyor olacağım.";
			link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;
		
		case "AffairOfHonor_CowardFencer_4":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_4_1":
			dialog.text = "Görünüşe bakılırsa, sen benden bile daha büyük bir korkaksın...";
			link.l1 = "Evet, öyleyim.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_5":
			dialog.text = "Bir haber var mı, kaptan?";
			link.l1 = "Paralı asker öldü. Umarım artık o mevki senindir?";
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;
		
		case "AffairOfHonor_CowardFencer_6":
			dialog.text = "Oh, kaptan, teşekkür ederim! Ödülünüzü alın, ben de valimize rapor vereceğim!";
			link.l1 = "Elveda... efendim.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
			GiveItem2Character(pchar, "chest"); 
			Log_Info("You have received a chest filled with doubloons");
			PlaySound("interface\important_item.wav");
		break;
		
		case "AffairOfHonor_CoatHonor_1":
			LAi_CharacterEnableDialog(NPChar);
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.QuestTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "AffairOfHonor_CoatHonor_2":
			dialog.text = "Bir tane daha?";
			link.l1 = "Şerefe.";
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;
		
		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = "Ve dahası!";
			link.l1 = "Biraz bekle! Nereye böyle aceleyle gidiyorsun?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;
		
		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = "Soruları boşver! İç!";
			link.l1 = "Peki, ama belki sonra bana başına ne geldiğini anlatırsın?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;
		
		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = "Gerçekten ilgini çekiyor mu? O zaman dinle, hâlâ konuşabiliyorken! Birkaç güne kadar konuşamayacağım çünkü ölmüş olacağım... Evet, ölü! Ve bunun suçlusu rom. Çok fazla rom ve başıma musallat olan şu subay, belli ki şeytanın işi!\nTabii ki ayık olsaydım ya da en azından bu kadar sarhoş olmasaydım, garnizonumuzun ve tüm şehrin en iyi kılıç ustasıyla dövüşmezdim. Ama şimdi ne olacak? Mahvoldum, bittim ve öldüm! Ne aptalım ben...";
			link.l1 = "Evet, bu oldukça aptalcaydı. Ama muhtemelen gelecekte daha akıllıca davranırsın... tabii düellodan sağ çıkarsan. Elveda.";
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = "Sarhoş olmak da en iyi seçenek değil, memur. Eminim bu belaya bir çözüm vardır.";
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;
		
		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = "Ne tür bir çözüm? Kaçıp üniformamı ve itibarımı kaybetmek mi? Yoksa bir domuz gibi doğranmamak için intihar etmek mi? Senin tavsiyen ne olacak?";
			link.l1 = "Hiçbiri değil. Sana yardım edeceğim ve düellonun vakti gelene kadar rakibinin sana zarar vermesini engellemeye çalışacağım. Onu nerede bulabilirim?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;
		
		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = "Ciddi misin? Bunu yapacak mısın?! Sana yemin ederim, karşılığını fazlasıyla alacaksın!\nOnu şehirde bulabilirsin. Sevgilisi burada yaşıyor, bütün subaylar ondan haberdar ama ne yazık ki adresi bilinmiyor... Yani bence onu da orada bulabilirsin.";
			link.l1 = "Yeter artık. Burada bekle. Ben gidip şu... 'en iyi kılıç ustasıyla' konuşacağım.";
			link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;
		
		case "AffairOfHonor_CoatHonor_Exit":
			DialogExit();
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "AffairOfHonor_CoatHonor_3":
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
			DialogExit();
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
			PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "13");
			npchar.lifeday = 2;
		break;
		
		case "AffairOfHonor_CoatHonor_Next":
			dialog.text = "Benim için bir haber var mı, efendim? İyi mi, yoksa... pek iyi değil mi?";
			link.l1 = "Henüz bir haberim yok. Burada bekle. Her şey yoluna girecek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;
		
		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = "Benim için bir haberin var mı, efendim? İyi mi yoksa... pek iyi değil mi?";
			link.l1 = "Her şey bitti. Potansiyel rakibin artık kimseye zarar veremeyecek... Artık güvendesin. Ama umarım bu yaşadıklarından ders alırsın ve tanımadığın insanlara karşı saldırgan davranmazsın.";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = "Şaka yapmıyorsun, değil mi? Ben... Gerçekten minnettarım, "+GetAddress_Form(NPChar)+"! Al, sahip olduğum her şeyi al. Bu benim maaşım, hepsini al!\nBir ders mi diyorsun? Evet, lanet olsun, haklısın! Bir daha olmayacak, sana söz veriyorum. Ve bana bir şans daha verdiğin için tekrar teşekkür ederim!";
			link.l1 = "Pekâlâ o zaman. Elveda, subay...";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			TakeNItems(pchar, "purse3", 1); 
			Log_Info("You have received a purse with doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "AffairOfHonor_CoatHonor_End":
			dialog.text = "Tekrar teşekkürler, "+GetAddress_Form(NPChar)+", yardımın için!";
			link.l1 = "Her zaman hoş geldiniz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;
		
		case "AffairOfHonor_CoatHonor_4":
			dialog.text = "Hey, ne oluyor? Ne işin var hanımımın odasında? Defol buradan yoksa seni zorla dışarı atarım!";
			link.l1 = "Canım nereye isterse oraya giderim ve böyle bir davranış için seni kimseye şikayet edecek değilim! Zorla mı? Hadi, dene bakalım!";
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;
		
		case "AffairOfHonor_CoatHonor_5":
			dialog.text = "Böylesine bir küstahlık! Eşi benzeri görülmemiş bir saygısızlık! Bayım, fena halde yanılıyorsunuz! Derhal bu evden çıkın, yoksa yaşadığınıza pişman olacağınıza yemin ederim!";
			link.l1 = " Lafla peynir gemisi yürümez! Pişman olacak olan sensin, ben değil, "+GetAddress_FormToNPC(NPChar)+"! ";
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;
		
		case "AffairOfHonor_CoatHonor_6":
			dialog.text = "Really? Beware then! If I kill you in this house, it will be murder. So your death won't tarnish my name; men of honour settle such matters near a lighthouse!\nI challenge you, "+GetAddress_Form(NPChar)+", you insolent man! You shall answer for your words! So, a duel in two hours?";
			link.l1 = "Tabii, "+GetAddress_FormToNPC(NPChar)+" cesur adam.";
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;
		
		case "AffairOfHonor_CoatHonor_7":
			dialog.text = "O halde orada doğru zamanda olmayı unutma. Hâlâ rahibimizden bir requiem sipariş etmek için vaktin var.";
			link.l1 = "Senin için bir ağıt mı? Bir kuruş bile etmezsin. Fenerin orada görüşürüz!";
			link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;
		
		case "AffairOfHonor_CoatHonor_8":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
			LAi_SetWarriorType(npchar); // 140313
		break;
		
		case "AffairOfHonor_CoatHonor_9":
			dialog.text = "Kaybol!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;
		
		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Valiyi mi kastediyorsun? Ha! Şikayetlerime karşılık vali bana 'Tanrı'nın hükmü' dedi! Düello! Ne diyorsun buna? Ben sadece sessiz, huzur isteyen bir çiftçiyim, ne haydutum ne de dövüşçü\nBu bir düello değil, resmen cinayet olacak! Ve sen, şüphesiz, bu işlerde benden çok daha iyisin. Bu yüzden yaklaşan düelloda benim yerime temsilcim olmanı istiyorum. İnan bana, bu iyiliğini karşılıksız bırakmam.";
			link.l1 = "Düello ne zaman?";
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;
		
		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = "Bu gece, gece yarısından önce deniz fenerinin yakınında. Bana yardım edecek misin?";
			link.l1 = "Pekala, sana yardım edeceğim. Kasabada beni bekle!";
			link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;
		
		case "AffairOfHonor_GodJudgement_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05","blade_07"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "15");
		break;
		
		case "AffairOfHonor_GodJudgement_2":
			dialog.text = "Bana orada ne olduğunu anlatır mısın? Biz... Affedersin, sen mi kazandın?";
			link.l1 = "Eminim bilmek ilginç olurdu: bir pusu vardı. Belki de komşunuz işi sağlama almak için sadece birini değil, birkaç temsilciyi davet etmeye karar verdi ve hepsi de deneyimli hayduttu. Neyse ki ben usta bir kılıç ustasıyım.";
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;
		
		case "AffairOfHonor_GodJudgement_3":
			dialog.text = "Ne alçak adam! Şimdi sanırım valimizin o herifi tutuklama talebimi reddetmek için hiçbir bahanesi kalmadı! Teşekkürler! Al ödülünü, ben de konağa gitmeliyim.";
			link.l1 = "Elveda.";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			TakeNItems(pchar, "purse3", 1); 
			TakeNItems(pchar, "purse"+(hrand(2)+1), 1); 
			Log_Info("You have received purses of doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		// Диалоги до боя -->
		case "AffairOfHonor_BeforeFight_1":
			dialog.text = "Hatalar olmadan oynamak eğlenceli, çünkü o pislikleri bulmak gerçekten zor.";
			link.l1 = "Sakin ol, geliştiricilere haber vereceğim.";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			
			switch(AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = "Ah, işte buradasın. Bunlar benim arkadaşlarım ve yardımcılarım. Başlayalım mı?";
					link.l1 = "Emrinizdeyim!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "HonorSlave":
					dialog.text = "Herkes toplandı. Hazır mısın?";
					link.l1 = "Evet, başlayabiliriz!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "BeautifulPirate":
					dialog.text = "Sonunda! Bu kadar uzun bir yolu boşuna yürüdüğümü düşünmeye başlamıştım... Hadi bunu çabucak bitirelim, meyhanede bir kadeh rom ve ateşli bir kadın bıraktım!";
					link.l1 = "Artık ikisine de ihtiyacın olmayacağından eminim!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "Jackanapes":
					dialog.text = "Demek gelmeye karar verdin? Sonunda! O zaman başlayalım!";
					link.l1 = "Böyle acele etme, bir bıçağın üstüne düşebilirsin.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "WolvesAndSheeps":
					dialog.text = "Ve bunlar da yardımcılarım, efendim. Şimdi ölmeye hazırlanın!";
					link.l1 = "Önce siz.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CowardFencer":
					dialog.text = "İşte geldik. Kılıcınızı hazırlayın, efendim!";
					link.l1 = "Memnuniyetle, en iyisi kazansın!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CoatHonor":
					dialog.text = "Mükemmel, herkes geldi... Başlayalım, efendim!";
					link.l1 = "Hadi dans edelim!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "GodJudgement":
					dialog.text = "Sen de kimsin? Sıradan bir vatandaş gibi görünmüyorsun, dostum...";
					link.l1 = "Peki? Seninle bir düello mu ayarladım?!";
					link.l1.go = "AffairOfHonor_BeforeFight_2_1"
				break;
			}
		break;
		
		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = "Ha! Bir düello! Demek aradığımız müşteri sensin. Çocuklar, şunu bıçaklayalım da ödülümüzü alıp gidelim. Karnını deşin!";
			link.l1 = "Bir pusu mu? Ne kadar zavallıca, beni alt etmek için bundan çok daha fazlasına ihtiyacın olacak...";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;
		
		case "AffairOfHonor_BeforeFight_2":
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
			PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
			if(hrand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
			{
				PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
				Log_TestInfo("Seconds will fight");
			}
			// В квесте "Божий суд" всегда нападают.
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				Log_TestInfo("Global massacre");
				sld = CharacterFromID("AffairOfHonor_Helper_1");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				sld = CharacterFromID("AffairOfHonor_Helper_2");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				iTemp = hrand(3);
				if(AffairOfHonor_GetCurQuest() == "GodJudgement")
				{
					for(i = 0; i < iTemp; i++)
					{
						sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
						SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
						ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
						LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
					}
				}
			}
			LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги до боя.
		
		// Диалоги после боя -->
		case "AffairOfHonor_AfterFight_1":
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
			{
				dialog.text = "Arkadaşımızı öldürüp de paçayı sıyıracağını mı sandın? Silah başına!";
				link.l1 = "Böylesine sefil bir heriften bunu beklemeliydim!";
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = "Kaptan, onurun geri kazandı, kazandın. Ama sana iyi bir tavsiye vereyim – kasabadan ayrıl ve bir süre burada görünme...";
				link.l1 = " Peki sorun ne? ";
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = "Hepsi onur içindi, şimdi ise gidip dostumuzu alalım.";
				link.l1 = "Tabii, seni durdurmayacağım...";
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;
		
		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = "Sorun şu ki, komutanımızın bir yardımcısını öldürdünüz. O kötü bir adamdı ve kimse onun ölümüne üzülmeyecek... ama komutan ona çok düşkündü ve arkadaşının ölümünü asla affetmeyecek.";
			link.l1 = "Tavsiyen için teşekkür ederim, mutlaka dikkate alacağım. Hoşça kal.";
			link.l1.go = "AffairOfHonor_AfterFight_2";
		break;
		
		case "AffairOfHonor_AfterFight_2":
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				ChangeCharacterComplexReputation(PChar, "nobility", 5);
			}
		break;
		
		case "AffairOfHonor_AfterFight_FightWithHelpers":
			iTemp = hrand(3);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for(i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги после боя.
		//=====================================================================================================================================
		// <-- Серия миниквестов "Дело чести".
		//=====================================================================================================================================
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank)+5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_"+npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*8000+sti(pchar.rank)*500;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_prisoner": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+sti(pchar.rank)*600;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_peace": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*6000+sti(pchar.rank)*400;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
	
		case "manSlave": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manRapeWife": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manFriend": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanHasband": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanRevenge": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanPirates": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	npchar.quest.Qcity = sld.city;
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. He got frightened and run away on his ship" break;
		case 1: sText = "One dishonourable bastard has lost a huge sum to me in gambling and has run away on his ship" break;
		case 2: sText = "One scoundrel has loaned money from me, and when I wasn't at home he has repaid the debt with false coins to my servant. Now he is hiding somewhere on his ship" break;
		case 3: sText = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed and this bastard had run away on his ship " break;
		case 4: sText = "It was my mistake, I have hired some rogue as an accountant. He has committed a great peculation, bought a ship and run away " break;
		case 5: sText = "My ex-guard has stolen a box filled with jewels from my wife's boudoir and run away. Now I see where has he got enough coins to buy a ship " break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
		case 0:
			npchar.quest.text = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. But he got hired as a ship master and sailed away";
			npchar.quest.text1 = " dishonoured a woman and cowardly run away";
		break;
		case 1:
			npchar.quest.text = "One dishonourable bastard had lost a huge sum to me in gambling but he didn't pay me yet, I heard that he got hired as a cannoneer and run away";
			npchar.quest.text1 = "lost all his money in gambling and didn't want to repay the debit ";
		break;
		case 2:
			npchar.quest.text = "One scoundrel has loaned money from me, and when I wasn't at home he had repaid the debt with false coins to my servant. Now he is serving on one ship as quartermaster and hiding from me ";
			npchar.quest.text1 = "counterfeiter who has committed a crime";
		break;
		case 3:
			npchar.quest.text = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed. Luckily for him bastard got hired as a doctor on one ship and run away";
			npchar.quest.text1 = "slanderer and intrigant who has tried to dishonour one good citizen";
		break;
		case 4:
			npchar.quest.text = "It was my mistake, I have hired some rogue as an accountant. He had committed a great peculation and now he is serving on one ship as quartermaster and hiding from me";
			npchar.quest.text1 = "is blamed in peculation and misappropriation";
		break;
		case 5:
			npchar.quest.text = "My ex-guard stole a box filled with jewels from my wife's boudoir and run away. He got hired as an officer for the boarding party on one ship";
			npchar.quest.text1 = "a common thief and his place is in jail. He has stolen jewels from his own employer";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
		case 0: 
			npchar.quest.text = "my old pal, who was my close friend in the Old World";
			npchar.quest.text1 = "he is your old friend";
		break;
		case 1:
			npchar.quest.text = "a man, who basically was my father";
			npchar.quest.text1 = "you were like a father for him";
		break;
		case 2:
			npchar.quest.text = "my stepbrother, who had left the old world in his youth";
			npchar.quest.text1 = "you are his stepbrother";
		break;
		case 3:
			npchar.quest.text = "a man who really helped me in the Old World";
			npchar.quest.text1 = "you have helped him a lot";
		break;
		case 4:
			npchar.quest.text = "my sister's husband who was my friend in the Old World";
			npchar.quest.text1 = "you are his sister's husband";
		break;
		case 5:
			npchar.quest.text = "my friend, my brother in arms in the Old World";
			npchar.quest.text1 = "you were brothers in arms";
		break;
	}
}
