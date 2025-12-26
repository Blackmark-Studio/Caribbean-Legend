// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Az önce bana bir soru sormaya çalıştınız...","Benim tersanemde ya da bu kasabada, böylesine meraklı insanlarla hiç karşılaşmadım.","Bu kadar çok soru neden? Benim işim gemi yapmak. Hadi onunla ilgilenelim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Hm, peki...","Devam et...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Dinle, François Gontier adında bir korsan tesadüfen uğrayıp seninle konuşmadı, değil mi? Son zamanlarda Porto Bello'daydı, bunu biliyorum.";
                link.l1.go = "Portobello_ratS_1";
            }
		break;
		
		case "Portobello_ratS_1":
			dialog.text = " Evet, aldı. Benden bir korvet satın aldı ve kısa süre sonra denize açıldı.";
			link.l1 = "Teşekkür ederim! Peki, nereye gittiği hakkında bir fikriniz var mı?";
			link.l1.go = "Portobello_ratS_2";
		break;
			
		case "Portobello_ratS_2":
			dialog.text = "Hayır dostum, hiçbir fikrim yok. Ben gemi tamir eder ve satarım, nereye gittiklerini takip etmem. Bu benim işim değil.";
			link.l1 = "Pekâlâ, teşekkürler... Bakalım nereye kayboldun...";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");
		break;
			
			
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
