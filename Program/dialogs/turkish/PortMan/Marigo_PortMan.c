// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştın "+GetAddress_Form(NPChar)+"...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bak, eğer limanın işleriyle ilgili bana söyleyecek bir şeyin yoksa, sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boşver.","Gerçekten de, bu üçüncü sefer...","Üzgünüm, ama şimdilik liman işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten1")
			{
				link.l1 = "Fransız bayrağı altındaki 'Admirable' adlı bir kalyonu arıyorum. Kaptanının adı Gaius Marchais idi. Bana bir sonraki rotasını söyleyebilir misiniz? Belki burada kaydını yaptırmıştır?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Hmmm, 'Admirable'? Galyon mu? Hatırlıyorum onu. Bakalım... Onu Barbados'taki Bridgetown'a paprika götürmesi için kiralamıştık. Bir şey mi oldu?";
			link.l1 = "Hayır, ama Gaius benim arkadaşım ve onunla tanışmak için sabırsızlanıyorum.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "O zaman Barbados'a yelken aç. Ama onu orada bulacağından şüpheliyim, bu uzun zaman önceydi. En azından yerel liman müdüründen sana yardım etmesini isteyebilirsin.";
			link.l1 = "Sanırım yine gidiyorum.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "12");
			pchar.questTemp.Guardoftruth = "barbados";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
