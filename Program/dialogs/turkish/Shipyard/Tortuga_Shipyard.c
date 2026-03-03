// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Bana az önce bir soru sormaya çalıştınız...","Benim tersanemde ya da bu kasabada böylesine meraklı insanlara hiç rastlamadım.","Bu kadar çok soru neden? Benim işim gemi yapmak. Hadi onunla ilgilenelim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Hm, peki...","Devam et...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga1")
			{
				link.l1 = "Gaius Marchais'i arıyorum. Onunla ilgili son duyduğum şey, 'Santa Margarita' adlı kalyonunu tamir etmeniz için buraya yanaştırdığıydı...";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Kendi kalyonu mu? Ho-ho, bu iyi bir şaka kaptan. Gaius Marchais’in elinde yarı ölü bir şalopiden başka bir şey yoktu... korsan olmaya karar verdikten sonra bir kalyon ele geçirdi, ödül olarak. Şanslı herif, ilk baskınında böyle bir ganimet\nİyi para teklif ettim, ama kabul etmedi, düşünebiliyor musun! Onun yerine, zavallı şalopesini ucuza sattı ve parayla kalyonu tamir etti! Yeni yelkenler, yeni renkler ve yeni bir isim – ki bu genelde iyiye işaret değildir\nTabii, ismi fazlasıyla papaz işi gibiydi, ama kızımın adı da Margarita, o yüzden sanırım sorun yoktu... Şiddetten bıktığını, artık tüccar olacağını söyledi. Ve şansı da yaver gitti...";
			link.l1 = "Ticaret, sanırım, dinlendirici olurdu ama papazların kalyonları genellikle şalopalar tarafından ele geçirilmez. Peki, şimdi gemisinin yeni adı ne olmuş?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "'Muhteşem'... Şaşmamalı! Yeni kalyonunun etrafında bir gelini kovalıyormuş gibi dört dönüyordu, gözünü alamıyordu ondan.";
			link.l1 = "Anladım. Gaius şu anda Tortuga'da mı?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Hayır. Yeni gemisiyle denize açıldı ve hâlâ Tortuga'ya dönmedi. Nereye gittiğini bilmiyorum, bu yüzden bu konuda sana yardımcı olamam.";
			link.l1 = "Ne büyük aksilik... Ona gerçekten ihtiyacım vardı. Hatta onun 'takdire şayan' gemisi için bir kadeh kaldırmalıydık. Neyse, bilgi için teşekkürler.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Hiç sorun değil. Yine uğrayın, kaptan. Unutmayın, geminizin onarıma ihtiyacı olursa burada her zaman bir yeriniz var!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "9");
			pchar.questTemp.Guardoftruth = "tortuga2";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
