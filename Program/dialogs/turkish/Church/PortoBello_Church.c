// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular, "+GetSexPhrase("evladım","kızım")+"?","Sor, dinliyorum..."),"Dinliyorum, şimdi konuş. "+GetSexPhrase("evladım","kızım")+"...","Üçüncü kez, "+GetSexPhrase("evladım","kızım")+", neye ihtiyacın varsa sor.","Bir din adamının çok işi var, ve sen beni oyalıyorsun. "+GetSexPhrase("evladım","kızım")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda değil, padre..."),"Söyleyecek bir şeyim yok, özür dilerim.","Daha sonra soracağım. Beni affedin, baba.","Affedersiniz, kutsal baba...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "Rahip, Marisa Caldera’yı arıyorum. Onun çok dindar olduğunu ve düzenli olarak kiliseye geldiğini duydum. Onu bulmam için bana yardımcı olabilir misiniz?";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "Marisa, cemaatimizin en sadık üyelerinden biriydi, gerçekten de kilisemizin ruhuydu. Onun yokluğu cemaat için büyük bir kayıp. Neden ortadan kaybolduğunu bilmiyorum ama eminim ki: haksız yere sınandı, şeytanın ve onun uşaklarının parmağı olmadan değil.\nZaman zaman kasabada görüldüğüne dair söylentiler duyuyorum, ama hepsi bu kadar. Yapabileceğimiz tek şey, Rabbin iradesine güvenmek ve bir gün geri dönüp yeniden kilisenin çatısı altında huzur bulmasını ummak.";
			link.l1 = "Belki bana onun hakkında daha fazla bilgi verebilecek birini tanıyorsunuzdur?";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("Oğlum","Kızım")+", söyle bakalım, Marisa'yı neden arıyorsun? Biliyorum, zaman zaman insanlar onu bulmak ister, ve hepsi de dürüst insanlar gibi görünmez. Dünya baştan çıkarıcılarla dolu, ve onu arayanların niyeti her zaman iyi olmuyor. Bir kelime etmeden önce, ona ya da onunla bağlantılı kimseye zarar vermeyeceğinden emin olmalıyım.";
			link.l1 = "Endişenizi anlıyorum, Peder, ama sizi temin ederim: Kötü bir niyetim yok. Sadece ona çok geç ulaşmış bir mektubu teslim etmek istiyorum. Kim bilir—belki içinde onun için önemli bir şey vardır. Buyurun, bir bakın.";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Given: Letter for Marisa Caldera", "None");
		break;

		case "LFD_Church_1_3":
			dialog.text = "Evet, bu mektup sana ulaşmadan önce birçok fırtına atlatmış gibi görünüyor. Kim bilir içinde ne var, okunduktan sonra ne gibi sonuçlar doğuracak... Ama sen onurlu bir insansın, Kaptan, onu gerçek sahibine geri vererek doğru olanı yapıyorsun. Marisa'nın şu anda nerede olduğunu bilen biri varsa, o da tek güvendiği dostu Dolores Monjo'dur\nOnun evi liman idaresinin solunda. Umarım bu mektup Marisa'ya daha fazla acı getirmez, çünkü o zaten fazlasıyla acı çekti.";
			link.l1 = "Teşekkür ederim, Peder. Tanrı sizi korusun.";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;

		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
