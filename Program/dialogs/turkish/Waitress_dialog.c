// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "Ne istiyorsunuz, señor? Üzgünüm, sadece...'hıçkırır'... ah... özür dilerim.";
					link.l1 = "Neden bu kadar üzgünsünüz, hanımefendi? Böyle güzel bir yüzde gözyaşları mı? Ne oldu?";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! "+UpperFirst(GetAddress_Form(NPChar))+", yardım edin! Cinayet!";
				link.l1 = "Ha? Kimi öldürmek? Nerede? Bu bir şaka mı, canım?";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> Тайна Бетси Прайс
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Seni tekrar görmek ne güzel... Uğradığın için teşekkür ederim... ama korkarım şu an konuşmak için en uygun zaman değil. Yalnız olduğunda tekrar gel. O zaman... daha özel konuları konuşabiliriz.";
							link.l1 = "Her zaman sohbet etmek güzel, ama artık gitmeliyim. Belki tekrar karşılaşırız.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"...  Ben de artık bizim meyhaneye gelmeyi unuttun sandım. Keşke yalnız gelseydin. Seninle baş başa konuşmayı umuyordum.";
							link.l1 = "Bence kader bize hâlâ baş başa konuşma fırsatı verecek.";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Beni fazla bekletmeyeceğini biliyordum. Bir dakika daha kaybetmek istemiyorum. Üst kattaki oda boş... sadece ikimiz için. Hayır demezsin, değil mi?";
							link.l1 = "Beni nasıl cezbetmeyi bildiğini gösteriyorsun... Eh, karşı koymam için bir sebep yok. Devam edelim mi?";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Bugün gerçekten ilgilenmem gereken önemli işlerim var, üzgünüm. Ama söz veriyorum, bir dahaki sefere telafi edeceğim.";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"! Neredeyse beni bekletmekten zevk aldığını düşünmeye başlamıştım. Orada öylece bir heykel gibi duracak değilsin, değil mi? Bu zamanı çok daha güzel değerlendirebiliriz.";
							link.l1 = "Kimse senin cazibene karşı koyamaz... Zaman kaybetmenin anlamı yok – şimdi yukarı çıkıyorum.";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Bayağı baştan çıkarıcısın, Betsy... Ama ne yazık ki, şu anda başka bir yerde olmam gerek.";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "Sana birkaç soru sormak istiyorum.";
				link.l9.go = "quests";
				break;
			}
			//<-- Тайна Бетси Прайс
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "Yukarı çıkmanı istemiştim. Burada kalıp dikkat çekme.";
					link.l1 = "Pekala, gidiyorum, başını belaya sokmak istemem...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "Ben burada yeniyim, lütfen beni işimden alıkoyma. Hâlâ alışamadım...";
					link.l1 = "Ve senden önce burada çalışan garson nerede? "+pchar.questTemp.different.FackWaitress.Name+", hatırladığım kadarıyla...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "Yine gel, tatlım. Belki biraz daha eğleniriz. Keşke daha fazla boş vaktim olsaydı...";
					link.l1 = "Tabii ki yaparım, harikaydın!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "Seni tanımıyorum, o yüzden beni rahatsız etme...";
					link.l1 = "Param nerede?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Üzgünüm, "+GetSexPhrase("yakışıklı","güzel olan")+", şimdi çok meşgulüm. Meyhane için iyi bir zaman, ama konuşmak için değil!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "Lütfen kaptan, burada kavga etmeyin! Buranın temizliği zaten çok zor.";
					link.l1 = ""+GetSexPhrase("Hm... Zaten öyle bir niyetim yoktu.","Kavga arayan bir ayyaşa mı benziyorum? Ben de senin gibi bir kızım, merak etme.")+"";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+GetSexPhrase("Ah, kaptan! Bu gece benimle aynı yatağı paylaşmak ister misin? Övünmek gibi olmasın ama...","Buyurun oturun, kaptan. Sizin gibi gerçek bir deniz kurduyla tanışmak her zaman bir zevk.")+"";
						link.l1 = "Şimdi acelem var, ne yazık ki. Bir dahaki sefere!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "Büyük bir zevkle, güzelim!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "Buyurun kaptan, oturun. Romumuzu tadın, bir kart ya da zar oyunu oynayın. Kendinizi evinizde hissedin! Sizin gibi gerçek bir deniz kurduyla tanışmak her zaman büyük bir zevk.";
						link.l1 = "Teşekkür ederim, güzelim.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "Bir şey sipariş etmek istiyorsan ustayla konuş. O, barın arkasında.";
					link.l1 = " Tavsiyen için teşekkürler. ";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "Eğer dinlenip sağlığını toparlamak istiyorsan, o zaman kendine bir oda kirala. Bütün gece salonda oturmak sana pek fayda etmez.";
					link.l1 = "Teşekkür ederim.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "Sana birkaç soru sormak istiyorum.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "O zaman dinle. Hanede bir oda kirala. Oraya git ve beni bekle. Biraz sonra gizlice geleceğim...";
			link.l1 = "Ha! Halledeceğim, tatlım! Seni bekliyor olacağım!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "Artık burada çalışmıyor, emekli oldu... Üzgünüm, yapmam gereken bir iş var.";
			link.l1 = "Peki...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "İyi dinle, seni arsız aptal. Paranın nerede olduğunu bilmiyorum! Eğer üzerime gelmeye devam edersen, muhafızları çağırırım ve kendini zindanda bulursun!";
			link.l1 = "Pekala, muhafızlara gerek yok... Ne aptallık...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "Aynen öyle, tam bir aptalsın. Bir dahaki sefere daha akıllı ve daha düzgün olursun.";
			link.l1 = "Deneyeceğim... (fısıldayarak) Kahrolası orospu...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "Beni duyabiliyor musun?";
			link.l1 = "Ughh...";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "Kendini kötü mü hissediyorsun? Başın mı ağrıyor?";
			link.l1 = "Lanet olsun... neredeyim ben?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "Hatırlamıyor musun? Seni soydular.";
			link.l1 = "Ne? Ah... Başım... Kim cesaret edebilir ki?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "Ben nereden bileyim? İçeri daldılar, öldürmekle tehdit ettiler, ceplerini karıştırdılar ve çekip gittiler.";
			link.l2 = "Anladım... Kahretsin... Biraz su isterim... Teşekkür ederim.";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "Hayır, bir şey değil, señor... nezaketiniz için teşekkür ederim, ama ben... (ağlıyor)";
			link.l1 = "Biri seni üzdü mü? Sakin ol, güzelim, anlat bana her şeyi.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Hayır, hayır, señor, bir şey yok. Özür dilerim, kendimi tutamadım, sadece... Kardeşim. Onun öldüğünü söylüyorlar ama ben inanmıyorum. Neye inanacağımı bilmiyorum, ama içimde bir yerde onun büyük bir sıkıntıda olduğunu hissediyorum. Anne babamızdan sonra yanımda sadece Angelo kaldı... (ağlar)";
			link.l1 = "Anlıyorum, ama lütfen sakin olun. Kardeşinize ne oldu?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Señor... lütfen yanlış anlamayın, ama neden böyle bir kaptan sıradan, mütevazı bir meyhaneci kızla ilgilensin ki? Size yardımınız için vaat edebileceğim hiçbir şeyim bile yok... ";
			link.l1 = "Aslında, haklısın. Fedakârlık bana göre değil, o yüzden güçlü ol, hepimiz sevdiklerimizi kaybederiz. Hayat bu, Fransa'da dediğimiz gibi...";
			link.l1.go = "exit";
			link.l2 = "Bir kadın, bir erkeğe teşekkür etmenin bir yolunu her zaman bulur... Ha-ha. Şimdi, ağlamayı bırak da bana derdini anlat.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "Genç señorita, Kilisemizin birbirimize yardım etmemizi öğrettiğini bilmiyor musunuz? Elimden gelirse size yardımcı olmaya çalışırım, tabii ki.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				Notification_Reputation(false, 36, "high");
				dialog.text = "Bu bir 'ipucu' muydu? Affedersiniz, sizinle konuşmak benim hatamdı! Elveda, 'caballero'...";
				link.l1 = "Sen nasıl istersen, canım.";
				link.l1.go = "exit";
			}
			else
			{
				Notification_Reputation(true, 36, "high");
				dialog.text = "Pekala... En azından isteklerinde dürüstsün. Sana söz veriyorum, eğer Angelo'yu bulursan ya da başına gerçekten ne geldiğini bana söylersen, istediğini alacaksın...";
				link.l1 = "Sevgili señorita, sizinle iş yapmak büyük bir zevk... Şimdi doğrudan kardeşinizin hikayesine geçelim.";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "Benimle dalga mı geçiyorsun? Gerçekten bana bedavaya yardım etmek mi istiyorsun?";
			link.l1 = "Kötü bir adam dışında kimse ağlayan bir kıza yardım etmez. Merak etme, sana gerçekten yardım etmek istiyorum. Angelo'ya tam olarak ne oldu?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Pekala, señor. Kardeşim, o... ah, gözyaşlarımı tutmak benim için hiç kolay değil, çok üzgünüm... Çok fakirdik çünkü benim... belki de işteki başarısızlığım yüzünden... Ve Angelo yerel kaçakçılarla çalışmaya başladı. Küçük balıkçı teknesinin gümrükten kaçırılacak bir şeyler taşırsa daha çok para kazanacağını düşündü.";
			link.l1 = "Basitçe söylemek gerekirse, kardeşin bir suçlu oldu, değil mi?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Hayır, señor, siz anlamıyorsunuz... o öyle biri değil! Bunu benim için yaptı! Burada gizlice para kazanmamı engellemek için... ne demek istediğimi anlıyorsunuz. Borç içindeydik ve o bunu onurum ve ruhum için yaptı. Sonra... yakalandı. Büyük bir sorun değildi, serbest kalması için daha fazla borç bile aldım... Ama öldüğünü söylediler.";
			link.l1 = "Onlar mı söyledi? Kim söyledi? Peki neden onlara inanmıyorsun? Hapiste mi ölmüş?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Evet. Onu serbest bırakmak için para getirdiğimde, komutan bana Angelo'nun veremden öldüğünü söyledi. Düşünebiliyor musun! Oraya sağlıklı geldi ve iki hafta sonra, tam da o hücrelerde öldü. Onlar... bana cesedi bile göstermediler. Mahkumları kalede salgın olmasın diye körfezin hemen yanında gömdüklerini söylediler.";
			link.l1 = "Bir salgın mı? Oldukça mantıklı geliyor. Yani sadece buna inanmayı mı reddediyorsun, yoksa daha ciddi bir sebebin mi var?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "No... No! (crying) I know it sounds foolish, but I am sure I would know if he had died. You see, Angelo was always strong - a real sailor. But there is one more thing\nMy grandpa died of consumption when I was a child, and he, an old man, had been fighting it for years! I know how it works; consumption doesn't kill people in days, trust me!";
			link.l1 = "Hm... Ben de şüpheye düştüm, burada bir gariplik var. Sana bir şey vaat edemem, ama daha fazlasını öğrenmeye çalışacağım.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "Basit bir söz bile beklediğimden çok daha fazlası! Çok naziksiniz, señor! Burada bekliyor olacağım!";
			link.l1 = "Ah, gençlik! Ne kadar da değişken duygularda... Elimi geri verir misin güzelim, ona hâlâ ihtiyacım var, ha-ha... Peki öyleyse, gidip biraz etrafa bakayım.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "Hayır, şaka yapmıyorum! Yukarıda! İki haydut bir soyluyu öldürüyor! Yardım edin, Kaptan! Burada silahlı olarak sadece siz varsınız!";
			link.l1 = "Dışarı koş, muhafızları çağır! Yukarı çıkıyorum!";
			link.l1.go = "FMQP_1";
			link.l2 = "Sevgilim, beni bir muhafızla karıştırmış olmalısın. Cinayet durumunda devriye çağır.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "A-ah, muhafızlar! Yardım edin!";
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
