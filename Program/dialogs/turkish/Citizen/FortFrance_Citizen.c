// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsun?");
			link.l1 = RandPhraseSimple("Fikrimi değiştirdim.'","Şu anda söyleyecek bir şeyim yok.");
			link.l1.go = "exit";
			//Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = "Affedersiniz, "+GetAddress_FormToNPC(NPChar)+" Michel de Monper'i nerede bulabileceğimi söyleyebilir misiniz? Onun bu kasabada olduğunu duydum.";
				link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = "Dinle, "+GetAddress_FormToNPC(NPChar)+", Sana bir şey sormak istiyorum... Gemimde görev yapacak bir rotacı arıyorum, tanıdığın biri var mı?";
				link.l1.go = "Sharlie_1";
			}
			//Бремя гасконца
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Sence gizli servis için mi çalışıyorum "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Pekâlâ... hayır. O halde hoşça kal.";
			link.l1.go = "exit";
			link.l2 = "Başka bir sorunuz var mı, peki?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Ben soruşturma bürosu muyum? Bilmiyorum, hiçbir şey bilmiyorum.";

            link.l1 = "Sen tam bir şaşkınsın! Defol.";
			link.l1.go = "exit";
			link.l2 = "Başka sorunuz var mı, o halde?";
			link.l2.go = "new question";
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = "Hmm... I suspect you've only just arrived here, since you so fearlessly ask such questions... I advise you to stop if you don't want any trouble. Speak to the Abbot; he may help you 'come to your senses'. You can find him at the church.";
				link.l1 = "Anladım...";
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
			else
			{
				dialog.text = LinkRandPhrase("Hayır, ondan hiç duymadım.","Sana yardımcı olamam, yapacak işlerim var.","Kim? Hiçbir şey çağrıştırmıyor, hayır. Ben yoluma devam edeyim.");
				link.l1 = "Anladım...  O zaman yoluma devam edeyim. ";
				link.l1.go = "exit";
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase("Hayır, hiç denizci tanımıyorum.","Yapmam gereken işler var ve hayır, başkasına sor...","Maalesef, sana yardımcı olamam. Kimseyi tanımıyorum.");
			link.l1 = "Anladım. O zaman başka birine soracağım.";
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
