// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Az önce bana bir soru sormaya çalıştınız...","Benim tersanemde ya da bu kasabada böyle meraklı insanlarla hiç karşılaşmadım.","Bu kadar çok soru da neyin nesi? Benim işim gemi yapmak. Hadi, onunla ilgilenelim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Hm, şey...","Devam et...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "Dinle usta, burada gemi yapıyorsun, değil mi?.. Yelkenleri de değiştiriyorsun... hiç düşündün mü... daha iyi bir yelken bezi malzemesi hakkında?";
                link.l1.go = "mtraxx";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Bulmaca gibi konuşuyorsunuz, efendim... Açık konuşun, sizi buraya getiren nedir? Endişelenecek bir şey yok, ben bürokrat değilim ve burası da gümrük dairesi değil.";
			link.l1 = "Ah, aynı fikirde olmamıza sevindim! İpek yelken bezi, efendim. Bildiğim kadarıyla, hız sizin için önemliyse yelkenler için bundan daha iyi bir malzeme yok.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Not only speed, but also her ability to sail close to the wind. You are offering ship silk for purchase? It's a valuable cargo, indeed. But there is an obstacle: I simply don't know how to use it in production. Do you follow? A material like this requires a very special set of abilities and skills which I lack. To be honest, my shipyard has a very different specialization; if you had offered me some ropes from the Tsardom of Russia, I'd gladly buy them all, no matter the price. We are in constant need of ropes, however, ship silk is not in demand here, I am sorry!";
			link.l1 = "Hm. Anladım. Vaktinizi ayırdığınız için teşekkürler, usta. İyi şanslar!";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
