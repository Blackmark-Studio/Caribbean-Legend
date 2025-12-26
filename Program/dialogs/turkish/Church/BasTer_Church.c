// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular, "+GetSexPhrase("evladım","kızım")+"?","Sor, dinliyorum..."),"Dinliyorum, şimdi konuş. "+GetSexPhrase("evladım","kızım")+"...","Üçüncü kez, "+GetSexPhrase("evladım","kızım")+", neye ihtiyacın varsa sor.","Bir din adamının çok işi olur ve sen beni oyalıyorsun, "+GetSexPhrase("evladım","kızım")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda değil, padre..."),"Söyleyecek bir şeyim yok, özür dilerim.","Daha sonra soracağım. Beni affedin, baba.","Affedersiniz, kutsal baba...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";		
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Sana alışılmadık bir meseleyle geldim, kutsal baba. Guy Marchais adında bir korsan yakın zamanda cemaatinize çok değerli bir eşya sundu. İçine lazurit yerleştirilmiş altın bir göğüs haçıydı. Bu doğru mu?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ah evet, evladım!  Bu, cemaatimizin en değerli eşyasıdır. Hayatımda böyle bir ihtişam görmedim! Ama neden soruyorsun, evladım? Bu haç neden ilgini çekti?";
			link.l1 = "Kutsal Baba, biliyorum bu hoşunuza gitmeyecek, ama bu haç başka bir kiliseden çalındı ve rahip o sırada öldürüldü. Bu eşyayı size getiren adam bir katil.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hepimiz günah işleriz, evladım, ama bir din adamını öldürmek ciddi bir suçlama. Elinde bir kanıt var mı? Bu haç hangi cemaatten çalındı?";
			link.l1 = "Sözüm yeterli kanıt değil mi? Bu haç Santiago’daki kiliseden çalındı ve geri verilmesi gerekiyor.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Santiago mu? O bir İspanyol şehri değil mi? Evladım, beni şaşırtıyorsun...";
			link.l1 = "Kutsal Baba, Tanrı'nın huzurunda herkes eşittir. İspanyollar da tıpkı bizim gibi Hristiyanlar ve milletler arasındaki anlaşmazlıklar inananların duygularını etkilememeli. Size yalvarıyorum, lütfen bu haçı Santiago cemaatine geri verin.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Oğlum, bu haçın cemaatimiz için kendini adamış Hristiyanlardan bir armağan olduğunu anlamıyor musun?! Hayır oğlum, istediğini yapamam.";
			link.l1 = "Bu haç uğruna kan döküldüğüne aldırmıyor musun? Bir din adamının kanı, İspanyol olup olmaması önemli değil.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Oğlum, bana hiçbir kanıt sunmadın ve sözüne körü körüne inanamam. Haç bizim cemaatimizde kalacak. Bu son kararım. Ayrıca, bu konuda İspanyollara yardım etmen beni fazlasıyla rahatsız ediyor.";
			link.l1 = "O halde öyle olsun. Hoşça kalın, kutsal baba...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			pchar.questTemp.Guardoftruth.Baster_church = "seek";
			AddQuestRecord("Guardoftruth", "27");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
