// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bugün boyunca bu soruyu üçüncü kez gündeme getiriyorsun...","Yine sorularınız var, öyle mi?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";						
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "Dinle, "+npchar.name+", sana alışılmadık bir meseleyle geldim. Saint-Pierre'deki bir dükkânda tüccarın yardımcısı olarak körfezde sakin ve huzurlu bir hayat yaşamak isteyen bir adam arıyorum. Maaşı iyi, başını sokacak bir yeri de olacak. Bana kimi önerebileceğini söyleyebilir misin?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Guadeloupe'a teslim edilmek üzere gemime yüklemek üzere olduğunuz şarap fıçıları için geldim...";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Biliyor musun, "+npchar.name+", Bir arkadaşımı arıyorum. Buraya gelmesi gerekiyordu ama kendini iyi hissetmiyordu. Belki arkadaşları ona yardım etmiştir...";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "Hm... Burada denizci hayatını bırakıp karada yaşamak isteyen birkaç kişi var. Sana yardımcı olabilirim, ama baştan söyleyeyim: bu bedavaya olmaz.";
			link.l1 = "Heh! Peki, ne kadar istiyorsun?";
			link.l1.go = "storehelper_1";
		break;
		
		case "storehelper_1":
			dialog.text = "One thousand pieces of eight. And there's nothing you'll have to do; in an hour, your candidates for the job will be in my tavern—several candidates. You'll be able to talk with them and select the one who appeals to you more than the rest.";
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = "Ahh... Peki, al, işte bin altın!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "Üzgünüm, ama o kadar param yok!";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Don't worry, mate. You'll get half of this amount back from the candidate. I'll tell him that's the cost of your services, heh heh... They won't give any more than five hundred. Stop by my tavern in an hour; by that time I'll have the people you need waiting for you.";
			link.l1 = "Pekâlâ. Bir saat sonra döneceğim, "+npchar.name+".";
			link.l1.go = "storehelper_3";
			npchar.quest.storehelper = "true";
			DelLandQuestMark(npchar);
		break;
		
		case "storehelper_3":
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			Storehelper_hire("");
		break;
		
		case "storehelper_exit":
			dialog.text = "Üzgünüm, sende de o kadar para yok. Ama sen de biliyorsun, böyle işler sadece bir 'teşekkür' için yapılmaz. Yani...";
			link.l1 = "Anlıyorum. Ama gerçekten param yok. Peki, hoşça kal...";
			link.l1.go = "exit";
			//pchar.quest.storehelper.over = "yes";
			//AddTimeToCurrent(2,0);
			//DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			//CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			DelLandQuestMark(npchar);
			dialog.text = "Ne diyorsun sen? Hangi şaraptan bahsediyorsun?";
			link.l1 = "Beni sana Walter Catcher adında bir adam gönderdi. Guadeloupe'a biraz şarap yükü taşımak için bir gemiye ihtiyacın olduğunu ve bunun için on bin peso ödeyeceğini söyledi. Ve bu iş için tam olarak benim gemime ihtiyacın varmış...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "Dinle, ben şarap satmam, senin hizmetlerine ihtiyacım yok, Walter Catcher'ı da tanımam.";
			link.l1 = "Vay canına! Demek o Avcı'yı sen göndermemişsin... O zaman, bu bütün komedi de neyin nesi?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "Heh! Bu ya bir yanlışlık, ya da kötü bir şaka, ya da...";
			link.l1 = "Ya da ne?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "Bunu kendin anlayamıyor musun? Birileri seni Le Francois'ya çekmek istemiş, ama nedenini bilmiyorum. Yerinde olsam hemen buradan ayrılır, her türlü önlemi alırdım. Bu işte bir bit yeniği var, dostum...";
			link.l1 = "Sanırım haklısın. Catcher'ın suratı hiç hoşuma gitmedi. Peki, tavsiyeni dinleyeceğim. Hoşça kal, Cesar!";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
			
			pchar.quest.NewGameTip4.win_condition.l1 = "location";
			pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.NewGameTip4.function = "ShowNewGameTip";
			pchar.quest.NewGameTip4.text = "Your first sea battle is coming! Save you game!";					  
		break;
		
		case "Portugal":
			dialog.text = "Evet, arkadaşınız buraya geldi, kaptan. Dün geldi ve üst katta bir oda kiraladı. Arkadaşları da burada, hehe... Şurada oturuyorlar. Onlara sorun!";
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
