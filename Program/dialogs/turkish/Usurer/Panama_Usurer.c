// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Bana bu soruyu daha önce de sormuştunuz...","Evet, dur tahmin edeyim... Yine aynı şeyleri mi dönüp duruyorsun?","Bakın, burada finans işlerini ben yürütüyorum, soruları cevaplamam...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Doğru tahmin ettiniz, üzgünüm...","Anladım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// Реакция ростовщика Панамы на репутацию ГГ или на разграбление Картахены по сюжету
		case "Panama_Deposit_NoReputation":
			dialog.text = "Evet... Kralın tebaası tarafından sevilen onurlu bir adamı, hangi milletten olursa olsun, bankam asla geri çevirmez.";
			link.l1 = "Anladım. Hoşça kal.";
			link.l1.go = "exit";
		break;
		
		case "Panama_Deposit_Cartahena":
			dialog.text = "Ama maalesef kızım ve kayınpederim yakalandı. Cartagena'da yaşıyorlardı. Git buradan, "+GetAddress_Form(NPChar)+". Burada istenmiyorsunuz.";
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
			{
				link.l1 = "Beni affedin. Hoşça kalın.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Sen bilirsin. Hoşça kal.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
		
		case "Panama_Deposit_SgorelVklad":
			dialog.text = "Fonlar, Cartagena şehrinin yağmalanmasının mağdurlarına yardım etmek için Taç tarafından el konuldu. Size yardımcı olamam. Muhafızları çağırmadan önce bankamı derhal terk etmenizi istiyorum!";
			link.l1 = "Bunu   pişman   olacaksın...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
