// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştın "+GetAddress_Form(NPChar)+"...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bak, eğer limanın işleriyle ilgili bana anlatacak bir şeyin yoksa, o zaman sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boşver.","Gerçekten de, bu zaten üçüncü sefer...","Üzgünüm, ama şimdilik limanın işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Günaydın. ' adında bir korvet hakkında bilgi almak istiyorum."+pchar.questTemp.Slavetrader.ShipName+"François Gontier komutasında.";
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Affedersiniz, Joachim Merriman adında bir adam limanınıza geldi mi? Orta yaşlı bir bey, Portekizli, bıyıklı, keçi sakallı ve delici bakışlara sahip?";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "'Cantavro' adında bir gemiyle ilgileniyorum. Kaptanı Esberdo Cabanas'ı özel bir mesele için arıyorum. Bana yardımcı olabilir misiniz?";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Evet, buradaydı. Ama çoktan gitti. Onun hakkında meyhanecimize sor, yukarıda bir oda kiraladı.","Bunu zaten sordunuz ve ben de cevapladım.","Sana söyledim, bu Gontier hakkında zaten sormuştun..","Sana zahmet vermemeni rica ediyorum!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Teşekkürler. Bunu yapacağım.","Hm, peki ...","Evet, gerçekten sordum ...","Affedersiniz, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Onun hakkında sana hiçbir şey söyleyemem. Gelse bile hiçbir yere kaydolmamış.";
			link.l1 = "Anladım. Ne yazık... Peki, aramaya devam edeceğim...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = "Let's see... the schooner 'Cantavro' set sail two days ago on patrol... however, the location is not listed. It is a military vessel, so the destination is known only to its captain and the fort commandant. I would suggest you speak with the commandant directly; you can find him at the fort if you wish to know more. Unfortunately, that is all I can do for you.";
			link.l1 = "Anladım. Peki, vaktinizi ayırdığınız için teşekkür ederim...";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Havana_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
