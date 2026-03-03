// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Sana nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bugün boyunca, bu senin üçüncü kez bir soru sorman...","Sanırım daha fazla sorunuz var?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = "Monsieur, iş arıyorum. Sizin için yapacak bir iş var mı?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "Verdiğiniz görevi yerine getirdim. Rom dolu sandal Le François Körfezi'ne teslim edildi ve adamlarınıza verildi.";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца */
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "Birkaç günlüğüne odalarınızdan birini kiralamam gerekiyor. Gemide yaralı bir adamım var. Dinlenip iyileşmesi lazım.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "Söylesene, oda kiraladığım arkadaşım gitti mi? Beni bekleyeceğine söz vermişti ama oda boş.";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "Adamlarım için bir eğlence düzenleyeceğim. Sanırım bundan zaten haberiniz var?";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Kutlamamız için ihtiyacımız olan her şeyi getirdim.";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			DelLandQuestMark(npchar);
			dialog.text = "Bir iş mi? Hm... Akıllı birine benziyorsun, delikanlı. Belki sana verebileceğim bir şeyler vardır\nBu iş kulağa kolay gelebilir ama sorumluluk ve zeka ister. Şu aptallara güvenemem, işi kesin batırırlar...";
			link.l1 = "Dinle, lütfen bana tam olarak neyi bana vermek istediğini söyleyebilir misin? Yemin ederim, seni hayal kırıklığına uğratmam, ya da en azından elimden gelenin en iyisini yaparım.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "Old Thomas has grown tired of waiting for the beer";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "The boards and the oakum will be here in the morning";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "Don't wait for the south wind";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "The bay is ready for disembarkation";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "The camels are going north";
				break;
			}
			dialog.text = "Güzel. Jamaika'nın en iyi romundan birkaç sandık dolusu malı meyhaneme getirecek birine ihtiyacım var. Şöyle bir durum var, ithalat vergileri kârımı azaltıyor ve en iyi müşterilerim susuz, bu yüzden gümrük memurlarını atlatmak için akıllıca davranmamız gerek. 'Hayalet' isimli lugger bu gece Martinique açıklarına gelecek\nLamanten Körfezi'nden çok uzakta demirlemeyecekler. Bu gemiyi bulup, güverteye çıkmalısın. Sana bir sandal ve beş denizci vereceğim, hepsi senin emirlerini dinleyecek\nGemiye çıktığında biri sana yaklaşacak. Ona bir parola söylemen gerekecek: '"+pchar.questTemp.Sharlie.Rum.Pass+"'\nCevap şu olacak: 'Neden bir rom içmeyelim, denizci?'. Sadece bir hakkın var, o yüzden yaz ve sakın hata yapma, yoksa anlaşma iptal olur. İşte bu yüzden bunu seninle yelken açacak o akılsızlara emanet edemem. Parolayı tekrar et.";
			link.l1 = "'"+pchar.questTemp.Sharlie.Rum.Pass+"'.";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "Harika. Bunu kendine birkaç kez daha tekrar et, ya da daha iyisi, bir yere yaz. Şifreyi lugger'ın kaptanına söylediğinde, rom sandıkları sandalete yüklenecek ve sen de onları korsan yerleşimi Le Francois'nin koyuna götüreceksin - orada seni karşılayacaklar.\nBütün iş bu kadar. Le Francois Koyu'ndan Saint Pierre'e yürüyerek gidebilirsin - sandalet koyda kalacak. İş bitince beş bin sekizlik ödeyeceğim.";
			link.l1 = "Kaçakçılık kulağa hem heyecanlı hem de kârlı geliyor. Dediğin gibi yapacağım. Sandal nerede?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "Yani, bana kaçakçılık yapmamı mı teklif ediyorsun? Hm... Biliyor musun, ismimi riske atamam. Beni mazur gör, hiçbir şey duymamış gibi davranalım.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "Nasıl isterseniz, efendim. Başka bir işim yok.";
			link.l1 = "Anladım. O zaman sana en iyisini dilerim, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "Sandal akşam yedide iskelede olacak. Sandaldaki tayfa yeteneklidir, bu yüzden luggere hızlıca ulaşmalısın. Tüm iş dört saatten fazla sürmemeli - eminim akşam on birde Saint Pierre'de olacaksın. Al bu dürbünü, hurda ama eldekiyle idare et. Lamanten Plajı adanın kuzeyinde, bu yüzden limandan çıkınca rotanı kuzeye çevir. Bol şans!";
			link.l1 = "Pekala, anladım. Yakında görüşürüz, "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("You've received a spyglass");
			PlaySound("interface\important_item.wav");
			if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			{
				GiveItem2Character(pchar, "map_martiniqua");
				Log_Info("You have received a map of Martinique");
				RefreshEquippedMaps(GetMainCharacter());
			}
			/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
			//pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			//pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
			NewGameTip("Open your inventory (F1) and equip the spyglass.");
			pchar.quest.NgtBarkas.win_condition.l1 = "location";
			pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
			pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
			pchar.quest.NgtBarkas.function = "NgtBarkas";
			AddTimeToCurrent(1,30);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "Harika! Sana güvenebileceğimi biliyordum. Zor muydu?";
			link.l1 = "Eh, bu zorun tanımına göre değişir...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "İşte ödülünüz: beş bin peso. Dürbünü de sizde kalsın. Ayrıca, küçük bir hediye daha—lütfen şu üç şişe romu da alın. Tadına baktığınızda, neden bu kadar rağbet gördüğünü anlayacaksınız.";
			link.l1 = "Teşekkürler! Seninle çalışmak büyük bir zevkti! Görüşmek üzere!";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			DelLandQuestMark(npchar);
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = " Sorun değil, bir odam var. 50 peso karşılığında, üç günlüğüne senin.";
			if (sti(pchar.money) >= 50)
			{
				link.l1 = "Buyurun.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "Kasadardan parayı alıp hemen döneceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "Ben onun kendi başına kalkıp odadan çıktığını söyleyemem, monsieur. Dün buradan bazı adamlar geçti. Biri uzun boylu, sıska, tek gözlü biriydi – görünüşünden tam bir haydut olduğu belliydi, yanında da peltek konuşan, Kastilyalıya benzeyen bir adam vardı. Sadece şaşırdım, ama o peltek bana öyle bir baktı ki... sanki bir biti ezmeden önce nasıl bakarsan öyle. Sonra arkadaşını sordular... ben de anlattım. Başka ne yapabilirdim ki?";
			link.l1 = "Biliyorum, "+npchar.name+", sen kahraman değilsin, doğru. Başka ne gördün? Nereye gittiler?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Hepsi bu... bekleyin, hayır! Durun, tek gözlü adam bir arabadan bahsetti. Sanırım bir araba bulup arkadaşınızı adanın öbür ucuna kadar sürüklemişler. Hepsi bu, monsieur, yemin ederim... Muhafızları çağırırdım ama o peltek adam gitmeden önce bana güzel bir karım olduğunu söyledi... Görüyor musunuz? Eğer bütün bunları size anlattığımı öğrenirlerse, onlar...";
			if (pchar.money >= 1000)
			{
				link.l1 = "Korkma, benden başka bir şey duymayacaklar, kurşunlar hariç. Bana gerçekten yardım ettin, sağ ol. Al, bu 1000 peso ödülün olsun.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "Çok bir şey değil, ama yine de sağ ol. Bir dahaki sefere muhafızı çağır ve bu kadar korkak olma.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Teşekkür ederim, monsieur. Size söz verebilirim, arkadaşınız neredeyse tamamen iyileşti. En azından kendi başına yürüyebiliyordu. Ve o adam, sessiz Hollandalı, tam o anda dışarıdan içeri girdi, bütün o karmaşayı gördü ve hemen geri dışarı fırladı, sonra da ortadan kayboldu.";
			link.l1 = "Bence o, bulabildiği ilk gemiyle çoktan ayrılmıştır. Bilgi için teşekkürler, artık gitme vakti.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "Her adam kılıcı kınından çekilmiş bir kahraman olamaz, kaptan.";
			link.l1 = "Pekâlâ... bu adamın kendi seçimi.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "Evet, yardımcınız uğradı, ama ona da söyledim, size de tekrar edeceğim - sarhoş denizcilerden oluşan kalabalıklara alışığım, ama sizin partilerinizin nasıl geçtiğini biliyorum. Geriye kalanlar, İspanyol terciosu Antwerp'e uğradıktan sonraki haline benzeyecek. Duvarlar yerinde kalırsa mutlu olacağım. Yani, kalabalığı birbirine düşürmek istiyorsanız, getirdiğinizin dışında iade edilmeyen bir depozito isteyeceğim. Olası sonuçlar için, tabii ki.";
			link.l1 = "Sen tam bir tilkisin! Yıllardır denizcilerle içtim, her türlü... mekânda bulundum, ve getirdiğim parayla senin meyhaneni baştan aşağı yeniden inşa edebilirdik! Durumdan faydalanmaya mı çalışıyorsun? Peki, bir düğüne yetişmem lazım ve böyle ufak tefek şeylerle uğraşacak havada değilim - ne kadar istiyorsun?";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "Bir 100.000 sekizli daha yeterli olur, merak etme - her şeyi en iyi şekilde halledeceğim. Adamların bu eğlenceyi uzun süre unutamayacak, söz veriyorum!";
			if (sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Biraz çaba göstermelisin – bu özel bir gün, anladın mı. Ve evet, kutlamadan sonra, ister meyhanen yansın ister başka bir şey olsun, bana gelip şikâyet etme.";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "Şimdiden kendimi bir kralın düğününü düzenliyormuş gibi hissediyorum! Bekle, birazdan döneceğim.";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "Adamlarınız bu eğlenceyi uzun süre unutamayacak, aklınızda bulunsun!";
			link.l1 = "Biraz çabalamalısın - bu özel bir durum, anlıyor musun. Eğer adamlarım yanlışlıkla meyhaneni yakarsa bana gelip ağlama.";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
