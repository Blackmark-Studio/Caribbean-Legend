// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bugün boyunca bu soruyu üçüncü kez gündeme getiriyorsun...","Yine sorularınız var, öyle mi?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye gitti böyle...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, Сага, Тени прошлого
			if (CheckAttribute(PChar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "sentjons")
			{
				link.l1 = "Raymond Baker'ı arıyorum, eski bir cellat. Hayatta olup olmadığını ve onu nerede bulabileceğimi biliyor musun?";
				link.l1.go = "baker";
			}
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Bay Jones'u arıyorum. Arayışımda bana yardımcı olabilir misin, dostum?";
				link.l1.go = "terrapin";
			}
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok")
			{
				link.l1 = "Dinle, bu kasabaya bir simyacı geldi mi, bir hekim? İtalyan, otuz yaşlarında, adı Gino Gvineili. Onun hakkında bir şey duydun mu?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Сага, Тени прошлого
		case "baker":
			dialog.text = "Bizim şişko dostumuz Albay Fox'tan bile daha popüler oldu! Zavallı adam hâlâ hayatta. Ama şu anda şehirde değil. Raymond, senin gibi ciddi insanların onunla ilgilendiğini öğrenince hemen kulübesini yok pahasına sattı ve ortadan kayboldu.";
			link.l1 = "Rüzgarla birlikte gitti, nereye?";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Kim bilir. Geçenlerde uğrayan ilk gemiye gemi doktoru olarak gitmişti. Ama o gemi bugün geri döndü ve Baker'ın henüz karaya çıktığını gören olmadı.";
			link.l1 = "Kaptanı   nasıl   bulabilirim?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Neden onu araman gerektiğini düşünüyorsun? Eminim o her zamanki gibi kamarasında çoktan sarhoş olmuştur. Dökülen kovasına 'Callow Meggy' adını vermiş. Kaptan nasıl, adı da öyle...";
			link.l1 = "Yardımın için sağ ol, dostum!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			DialogExit();
			AddQuestRecord("Shadows", "2");
			pchar.questTemp.Saga.Shadows = "baldmaggy";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1 = "location";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_ShadowsMaggy.function = "Saga_SetBaldMaggy";
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Bay Jones mu? Benimle dalga mı geçiyorsun dostum. Bu adada kaç tane Jones olduğunu biliyor musun? Bundan daha açık olmalısın.";
			link.l1 = "Onun yetişkin bir kız kardeşi var, Molly. Duyduğuma göre olağanüstü güzelmiş.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Hayır. Aklıma böyle bir şey gelmiyor. Üzgünüm dostum...";
			link.l1 = "Pekâlâ, bilmiyorsan bilmiyorsun...";
			link.l1.go = "exit";
			npchar.quest.terrapin = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Hayır, duymadım. Kasabada sadece bir simyacımız var, eczacı John Murdock. Onun iksirleri gerçekten etkileyici - her türlü derde deva olur.";
			link.l1 = "Sence bu iksirleri kendi mi yapıyor?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Güzel soru. Bunu arada bir ben de kendime sorarım. John, ilaç şişeleri, otlar ve tozlar konusunda uzman biri gibi hiç görünmüyor. Daha çok eski bir asker, bir paralı asker gibi... bu gerçeğe daha yakın.";
			link.l1 = "Pekâlâ, sanırım adam fazlasıyla nitelikli...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Belki de öyledir. Ama bir şeyi kesin olarak biliyorum: ikinci katta biri yaşıyor. Penceresi hep kapalı. John aşağıda olsa bile, yukarıdan şişelerin ve cam tüplerin tıkırtısı geliyor, ayrıca kaynayan otların kokusu yayılıyor, geceleri ise ışık hiç sönmüyor. Bu yüzden o odada oturan kişinin, John'un satmak için hazırladığı ilaçları yapan kişi olduğundan şüpheleniyorum.";
			link.l1 = "Hm. İlginç bir gözlem. Teşekkürler, dostum!";
			link.l1.go = "exit";
			pchar.questTemp.Guardoftruth = "merdok1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
