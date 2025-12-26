// старпом Акулы - Лейтон Декстер
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Beni rahatsız etme, çocuk. Burada yetkili olan Köpekbalığı, onunla konuş.";
				link.l1 = "Sana en azından merhaba diyebilir miyim, yoksa bu da kurallara aykırı mı?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "Layton, Shark bana adanın bir haritası olduğunu söyledi. Onu senden satın alabilir miyim?";
					link.l2.go = "map";
				}
				dialog.text = "Ah, "+GetFullName(pchar)+"! Benimle bir işin mi var yoksa sadece sohbet mi etmek istiyorsun? Her halükarda, bir dahaki sefere bir şişe rom getir, ha-ha!";
				link.l1 = "Hayır, sadece merhaba demek istedim. Bir dahaki sefere sana özel rom getireceğim.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ha! Şakacı biri çıktı! Peki... Benim adım Layton Dexter. Buraya düşmeden önce Shark'ın yardımcısıydım, şimdi de bu 'Terk Edilmiş Gemiler Şehri'nde onun sağ koluyum. (tükürür)\nGünlerimi adalılara erzak satarak ve o aylak Fazio'dan para koparmaya çalışarak geçiriyorum.";
			link.l1 = "Ben "+GetFullName(pchar)+"… Tanıştığımıza memnun oldum… sanırım.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "Steve'in öldüğünü zaten duymuşsundur. Bunu yapanlar Narvallerdi.";
			link.l1 = "Duymuştum... Demek yeni Amiral sensin?";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "Benim. Chad Narvallara geçti, Steve öldü, yani... Amiralim ben. İtirazı olan?";
			link.l1 = "Hayır... hiçbir itirazım yok.";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "İyi.";
			link.l1 = " Köpekbalığı'nın ölümü için Narvallar'dan intikam mı alacaksın? ";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "Savaş mı ilan edeceğim diyorsun? Hayır. Onlara bedel ödetmenin daha iyi yolları var.\nÖnce, erzak için ödedikleri fiyatı üç katına çıkaracağım. Eğer hoşlarına gitmez ve San Augustine'e saldırmaya kalkarlarsa, o zaman bedelini kanla öderler.\nSonra, Rivados ile bir ateşkes görüşeceğim. Tabii, o pis zencilerden pek güven beklenmez, hele büyücüleri Chimiset'in ölümünden sonra, ama yiyecek ve rom birçok günahı unutturabilir.";
			link.l1 = "Anladım. Peki... hoşça kal, Layton...";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "Bekle. Steve bana adadan ayrılıp bir gemiyle geri dönmek istediğini söyledi. Hâlâ bu mu senin planın?";
			link.l1 = "Öyle.";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "Bu rotaları al. Bunların içinde seni buraya sağ salim geri getirecek denizcilik talimatları var – yani, kayalıklara oturmazsın, akıntıya kapılıp gitmezsin ve dış halkadaki enkazlara çarpmazsın.\nBunlar olmadan ya adayı tamamen kaçırırsın... ya da başka bir enkaza dönüşürsün.\nResiflerin arasından geçmek için sığ suya uygun küçük bir tekne kullanman gerektiğini unutma. Tartane, lugger, şunör, slooptan büyük olmasın. Anladın mı?";
			link.l1 = "Evet, biliyorum. Teşekkür ederim.";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Don't forget to fill your cargo hold with provisions - I'll buy them from you for a good price. And never show this document to anyone; our base must remain secret. I'm only giving it to you because Steve himself was going to, and because you're a friend of Jan Svenson.";
			link.l1 = "Bunları başkasına göstermeyeceğime söz veriyorum. Tekrar teşekkür ederim, Layton.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
			AddQuestRecord("LSC", "5");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dexter_wait":
			dialog.text = "Kaçışını planlamada bir ilerleme kaydedebildin mi, "+pchar.name+"?";
			link.l1 = "Henüz değil, Layton, üzerinde çalışıyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "İşte buradasın. Konuşmamız lazım.";
			link.l1 = "Demek şimdi Amiral sensin?";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "Evet, ben Amiralim. Steve'in her işte yoldaşıydım, o ölünce de yönetimi ben devraldım. İtirazı olan var mı?";
			link.l1 = "Hayır... itirazım yok. Hakkınız var.";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "Birbirimizi anladığımıza sevindim. Bir şeye ihtiyacın olursa bana haber ver.";
			link.l1 = " Köpekbalığı'nın ölümü için Narvallardan intikam mı alacaksın? ";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "Yani, onlara savaş mı ilan edeceğim diyorsun? Hayır. Onlara bedel ödetmenin daha iyi yolları var.\nÖnce erzak için ödedikleri fiyatı üç katına çıkaracağım. Eğer hoşlarına gitmezse ve San Augustine'e saldırmaya kalkarlarsa, o zaman bedelini kanlarıyla öderler.\nAyrıca, artık Rivados'la aramız iyi, bu yüzden Narvaller bize tekrar karşı hamle yapmaya çekinirler.";
			link.l1 = "Anladım. Başka bir şey var mı, yoksa gidebilir miyim?";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "Yes. I see only one way we can get to the Narwhals. It's not perfect, but I don't see any alternative.\nWe will attack them from two directions. A group of cutthroats on longboats will board the Ceres while a second group, joined by the Rivados, will storm the Esmeralda.\nThis will either eliminate them completely, or prompt them to flee to the San Gabriel.\nThe second scenario is more likely; the San Gabriel is a very defensible position and besieging her would take a long time. Either way, we win.";
			link.l1 = "";
			link.l1.go = "plan_1";
		break;
		
		case "plan_1": // ноду Акуле
			DialogExit();
			npchar.greeting = "dexter_1";
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "whyskey_final_3";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			NextDiag.CurrentNode = "plan_2";
		break;
		
		case "plan_2":
			dialog.text = "Donald Greenspan ile yaptığın konuşmanın raporunu bekliyorum. Bu çok önemli, o yüzden vakit kaybetme.";
			link.l1 = "Yoldayım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "Evet, bir haritam var. İstersen, sadece iki yüz dublona senin olabilir.";
			link.l1 = "Pesoya ne dersin?";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "No, I take gold - and haggling will get you nowhere; I know exactly what this map is worth, and that's two hundred doubloons.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Pekâlâ, kabul ediyorum. Al altınını.";
				link.l1.go = "map_2";
			}
			link.l2 = "O kadar altınım yok. Belki sonra...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveDublonsFromPCharTotal(200);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a map of the City of Abandoned Ships");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "Haritayı al. Fiyatına değer – onu çizmek için bütün bir hafta boyunca şehri karış karış gezdim. Hatta bence sana ucuza sattım.";
			link.l1 = "Ucuz mu dedin?! Ha! Peki... teşekkür ederim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "Olduğun yerde kal! Evet, Köpekbalığı haklıymış, bu herif delirmiş. Onun yüzünden kaç adam öldü... Zincire vurun ve ambarın dibine atın!";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "Steve made me Admiral in his stead - I take it you and he are going back to the Caribbean together.\nI'll stay here and carry on business; me and Steve are loathe to lose such a great base. And you, of course, will always be a welcome guest, here.";
			link.l1 = "Teşekkürler, Layton. Ufku gözle açık tut, bir gün geri döneceğim.";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "A-ha, "+GetFullName(pchar)+"! Başardın! Steve'in denizcilik talimatlarını kullanarak Adalet Adası'nı buldun, değil mi? Deli herif... tekrar hoş geldin!";
			link.l1 = "Teşekkürler, Layton. Bir gün geri döneceğimi söylemiştim, ha-ha!";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "Pekala. Satılık yiyeceğiniz var mı? Piyasa fiyatının iki katını ödemeye hazırım.";
			if (iTrade > 0)
			{
				link.l1 = "Evet, satacak erzaklarım var.";
				link.l1.go = "trade";
			}
			link.l2 = "Maalesef, şu anda sana satacak hiçbir şeyim yok.";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "Yazık. Bir dahaki sefere biraz getir, iyi öderim.";
			link.l1 = "Unutmamaya çalışacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "Ne kadar?";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "Ne o, sarhoş musun dostum? Ciddi konuşmaya hazır olduğunda geri gel.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "Bu çok az! Zamanıma değmez – bana daha fazlasını getir!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "Peki, kendin için hiçbir erzak olmadan nasıl yelken açacaksın, dostum? Adamlarının açlıktan ölmesini mi istiyorsun? En azından şunu unutma "+FindRussianQtyString(GetCrewQuantity(pchar))+".";
				link.l1 = "Ah, haklısın.";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "İsa Mesih, bu bizim için fazla! Çürümeye başlamadan önce asla hepsini yiyemeyiz. Şu anda bundan fazlasını alamam "+iTemp+".";
			 link.l1 = "Ne dersen de.";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+"? Peki, sana ödeyeceğim "+FindRussianMoneyString(iMoney)+"Anlaştık mı?";
			link.l1 = "Anlaştık! Seninle iş yapmak güzeldi!";
			link.l1.go = "trade_2";
			link.l2 = "Hm... hayır, fikrimi değiştirdim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "Anlaştık. Sana ödeyeceğim "+FindRussianMoneyString(iMoney)+" mallar için. Anlaştık mı?";
			link.l1 = "Adil! Seninle iş yapmak güzeldi!";
			link.l1.go = "trade_4";
			link.l2 = "Hm... hayır, fikrimi değiştirdim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_4": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Gözlerim kör olsun! Ambarım tıka basa dolu! Önümüzdeki altı ay boyunca erzak almama gerek kalmayacak.";
				link.l1 = "Güzel. O zaman bir sonraki erzak yükünü altı ay sonra sana getireceğim.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Harika! Bir dahaki sefere bana daha fazlasını getir.";
				link.l1 = "Tabii!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		case "trade_2":
			iTemp = dialogEditStrings[4];
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Mükemmel! Ambarım şimdi dolu. Önümüzdeki altı ay boyunca erzak almama gerek kalmayacak.";
				link.l1 = "Güzel. O zaman altı ay sonra bir sonraki erzak yükünü getireceğim.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Harika! Bir dahaki sefere bana daha fazlasını getir.";
				link.l1 = "Tabii!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // стандартный диалог Декстера-адмирала
			dialog.text = "A-ah, "+GetFullName(pchar)+"! Seni gördüğüme sevindim! Ne istiyorsun?";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "Benden biraz erzak almak ister misin?";
				link.l1.go = "trade";
			}
			link.l2 = "Bir şey değil, sadece nasıl olduğunu görmek istedim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
