void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "Kaptan, gün bizim. Öncü birlik alt güvertenin temizliğini bitiriyor. Hiç esir yok... Ha! Sen de kendini tutmamışsın bakıyorum.";
			link.l1 = "Her nedense, büyük bir konuşma yapacak sandım. Ama o sadece içeri daldı.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
			if (sti(pchar.rank) <= 11) Achievment_Set("ach_CL_156");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "Serbestçe konuşmama izin var mı?";
			link.l1 = "Kabul edildi.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "Hayır, burada işimiz bitti.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "Neden onlara saldırdık? O brig bir tehdit değildi, yük de taşımıyordu. Elbette Grim hakkında her türlü söylenti vardı, ama ondan sadece köle tacirleri korkardı. Bugün birçok insan öldü — peki, ne uğruna?";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "Şimdi mürettebat adına mı konuşuyorsun?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;

		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "Ve bu ilk defa olmuyor...";
			link.l1 = "Şimdi mürettebat adına mı konuşuyorsun?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "Hayır. Bana inan, eğer tayfanın böyle soruları olsaydı, bu benim işimi kötü yaptığım anlamına gelirdi ve sen de çoktan ölü bir adama dönüşmüş olurdun\n"+"Senin şansına, tayfa bu lanetli seferden güzel bir kazanç sağladı. Bu gemideki her denizcinin cebi doubloonlarla doluydu!\n"+"Değerli bir yük yoktu gerçi — sadece yerlilere ait takılar ve tuhaf tılsımlar. Yine de tayfa köşeyi döndü. Görünüşe göre Grim onlara iyi para vermiş\n"+"Umarım o altından pay istemeyi düşünmüyorsun, kaptan?";
			link.l1 = "Değilim, Alonso. Beni haberdar ettiğin için teşekkürler.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "Benim. Payımın kamarama ulaştırıldığından emin ol.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;

		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "Her zaman yanındayım, kaptan. Bu arada, Hatıra'yla ne yapmayı düşünüyorsun?";
			link.l1 = "Bunu bir ödül olarak al — başka ne yapacaksın?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Karar vermedim"+GetSexPhrase(""," henüz")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "Her zaman yanındayım, kaptan. Bu arada, Hatıra'yla ne yapmayı düşünüyorsun?";
			link.l1 = "Bunu bir ödül olarak al — başka ne olabilir ki?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Henüz karar vermedim"+GetSexPhrase(""," henüz")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "En iyisi dokunma. Üzerinde bir tür yerli semboller var. Hakkında kötü söylentiler dolaşıyor — bir zamanlar korkunç bir salgından sağ çıktığı, güvertelerinde cesetlerin neredeyse dans ettiği söyleniyor\n"+"Kıçtaki iskelete gelince, oraya hiç girmem bile: bir enayi kafatasını eğlencesine kapmaya kalkışmadıkça, benden başka kimse orada nöbet tutmaya cesaret edemez.";
			link.l1 = "Anlaşıldı, Alonso. İşine geri dön.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "Tamam, kaptan.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "Kaptan, bu saatte sizi rahatsız ettiğim için üzgünüm.";
			link.l1 = "Rapor ver, Alonso.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "Kaptan? Burada ne yapıyorsun? Burada mı uyuyordun?";
				link.l1 = "Fark etmez.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "Kamaram... huzursuz hissettiriyor.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "Durum kötü. Mürettebatın morali yerlerde sürünüyor! Herkes açıkça geminin lanetli olduğunu söylüyor. Geceleri bir şeyler gördüklerinden şikayet ediyorlar.";
			link.l1 = "Tam olarak neyi görüyorsun?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "Çoğunlukla kâbuslar. Ama en kötüsü, adamlarımızdan birinin ateşli hastalıktan ölmesiydi. Genç bir delikanlıydı, öküz gibi güçlüydü, ama birkaç saat içinde yanıp kül oldu.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "Buna doktor karar verir. "+sld.name+" işini biliyor.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "Bu normal değil. Mürettebatı kontrol altında tut, Alonso. Bu senin işin.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;
		
		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "Aye aye!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "Anlıyorum. Mürettebatın çoğu artık gruplar halinde uyuyor — yalnız kalmaktan korkuyorlar. Sanki bu gemide yalnız kalmak mümkünmüş gibi...";
			link.l1 = "Başarmış gibi görünmüyorum. Ne oldu?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "Bir kavga çıktı — José, Marcel'i bıçakladı. Bağırıyordu, 'veba taşıyor' diye.";
			link.l1 = "Durum daha mı kötüye gidiyor?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = sld.name+" Bu sabah zaten rapor edildi. On bir can kaybettik. Ne yapacağız?";
			}
			else
			{
				dialog.text = "Bir on bir can daha kaybettik. Şimdi ne yapacağız?";
			}
			link.l1 = "Ben çağrıyı yapacağım.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "Umarım öyledir, Kaptan. Peki ya José? Öldürmek şaka değil.";
			link.l1 = "Çanı çaldıktan sonra asın onu. Kontrolün bizde olduğunu gösterin.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "Otuz kırbaç. Sağ kalırsa — bu Tanrı'nın takdiri.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "Aye aye!";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "Emredersiniz!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "Kaptan! Alarm!! Hemen topların olduğu güverteye gitmelisiniz!";
			link.l1 = "Ne oluyor?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;

		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "Kendin görsen iyi olur. Hadi, çabuk!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;
		
		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "Günaydın, kaptan!";
			link.l1 = "Ha?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;

		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "Uh, berbat görünüyorsun. Zor bir gece miydi? Neyse, iyi bir haberim var. Salgın bitti. Meğerse hiç salgın yokmuş.";
			link.l1 = "Ne demek istiyorsun?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;

		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "Mürettebat korktu, o saçma hayalet gemi hikayelerine inanmaya başladı. Telkinin gücü — inan bana, çok tehlikelidir. Birden fazla gemiyi batırmıştır.";
			link.l1 = "Ama insanlar öldü!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;

		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "Dövüş, pis yaralar, bozulmuş tuzlu et — denizcinin günlük hesabı işte. Eğer hepimiz lanetli gemilerle ilgili hikayelerle kendimizi bu kadar doldurmasaydık, belki birkaç kişi daha az kaybederdik\n"+"Kıçtaki o iskelet hiç yardımcı olmadı. Neyse ki bir... şakacı geceleyin şapkasını çalmış\n"+"Bu kadar küfürbazlığa rağmen yıldırım bizi çarpmadı ya, tayfa birden canlandı ve denizci kurnazlıklarıyla yeni yaramazlıklar planlamaya başladı. Mesela, diyelim ki...";
			link.l1 = "İskelete dokunmak yok!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;

		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "Şey... eğer ona alıştıysanız, elbette bırakmayız. İyi günler, kaptan\n"+"Bu arada, güzel şapka! Sana çok yakışmış. Önceki sahibine pek uymamış belli ki.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Selam, Kaptan. Kaptan Grim ile konuşmalısınız.";
				link.l1 = "Üzgünüm denizci, ama burada göze çarpıyorsun.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Başka bir şey var mı, Kaptan?";
				link.l1 = "Hiçbir şey.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_1_1":
			dialog.text = "Ne demek istediğini anlıyorum, Kaptan. Ben de senin gibi özgür bir kaptanın emrinde çalıştım. Hazine avladı, ticaret yaptı, yük taşıdı. Sonra tüccarları soymaya karar verdi — işler yolunda gitmedi. Sağ kalanlar korsanlıktan asılmaya mahkûm edildi.";
			link.l1 = "Ve Kaptan Grim seni mi satın aldı?";
			link.l1.go = "Memento_Sailor_1_2";
		break;

		case "Memento_Sailor_1_2":
			dialog.text = "Hepimizi tek seferde, yük gibi satın aldı. Her geminin tecrübeli tayfaya ihtiyacı vardır, Grim ise meyhaneden adam toplamaz... Ama karnımızı doyurur, iyi de öder. Biz de hizmet ederiz — ve kura çekeriz.";
			link.l1 = "Kuralar mı?";
			link.l1.go = "Memento_Sailor_1_3";
		break;

		case "Memento_Sailor_1_3":
			dialog.text = "Üzgünüm, bundan bahsetmemeliyiz.";
			link.l1 = "Neden   gitmiyorsun   o   zaman?";
			link.l1.go = "Memento_Sailor_1_4";
		break;

		case "Memento_Sailor_1_4":
			dialog.text = "Nereye? En azından burada bir şans var. Belki şans yüzümüze güler. Her geminin kendi kaderi vardır. Grim’in kaderi ayrı, seninki ayrı. Biz insan değiliz, sadece gemi defterindeki numaralardan ibaretiz.";
			link.l1 = "Benim gemimde işler farklıdır.";
			link.l1.go = "Memento_Sailor_1_5";
		break;
		
		case "Memento_Sailor_1_5":
			dialog.text = "Dediğiniz gibi, Kaptan. Size iyi günler.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Uzun zamandır bu güzel gemide misafirimiz olmamıştı!";
				link.l1 = "Denizci misin? Pek öyle görünmüyorsun.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Başka bir şey var mı, Kaptan?";
				link.l1 = "Hiçbir şey.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_2_1":
			dialog.text = "Ha! Kaptan beni doğrudan hücreden satın aldı. Port Royal'de asılmam gerekiyordu — sürekli şiir okuyan bir züppeyi bıçakladım. Hak etti, o alçak.";
			link.l1 = "Yani şansın yaver gitti, öyle mi?";
			link.l1.go = "Memento_Sailor_2_2";
		break;

		case "Memento_Sailor_2_2":
			dialog.text = "Tabii ki! Kaptan cimri değildir, ama bazen onun... oyunlarına katlanmak gerekir.";
			link.l1 = "Ne tür oyunlar?";
			link.l1.go = "Memento_Sailor_2_3";
		break;
		
		case "Memento_Sailor_2_3":
			dialog.text = "Her hafta çubuk çekeriz: kısa olan tehlikeli bir iş demek, bazen de denize atlamak. Aslında komik, gerçekten. Herkesin harcı değil, ama kaptan bunun değersizleri ayıklamanın yolu olduğunu söylüyor.";
			link.l1 = "Neye layık değilim?";
			link.l1.go = "Memento_Sailor_2_4";
		break;

		case "Memento_Sailor_2_4":
			dialog.text = "Ben nereden bileyim? Kaptan konuşmayı sever, bir rahip gibi vaaz verir: «Ancak ölümle yüzleşerek gerçekten yaşayabilirsin!»\n"+"(Tükürür.)";
			link.l1 = "Güverteye tükürmek kırbaç cezası demektir. Bir denizci gibi değil, bir haydut gibi davranıyorsun. Hoşça kal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Selamlar, Kaptan.";
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Başka bir şey var mı, Kaptan?";
				link.l1 = "Hiçbir şey.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_3_1":
			dialog.text = "Kaptan Grim, içinde bulunduğum köle gemisini ele geçirdi. Hasta ve ölüm döşeğindeydim ambarın içinde ... Fazla bir şey hatırlamıyorum. Gözümü açtığımda burada, Memento'daydım.";
			link.l1 = " Peki ya diğer kölelere ne oldu? ";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = " Bilmiyorum. Kaptan herkesi serbest bıraktığını söyledi, ama gemiye alınan tek kişi bendim. Diğerleri adalara dağılmış olmalı ya da yaralarından ölmüştür. O gün benim için bir sis perdesi gibi.";
			link.l1 = "En azından artık özgürsün.";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "Özgür mü? Burada kimse özgür değil. Kaptan altın, yiyecek, giysi verir ama karşılığında tam sadakat ister — ve bizi o lanetli kura çekmeye zorlar.";
			link.l1 = "Kuralar mı?";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "Her hafta, birisi kısa çöpü çeker ve tehlikeli bir işe gönderilir — hepsi geri dönmez. Kaptan, bunun yaşayanlarla ölüleri ayırmanın yolu olduğunu söyler.";
			link.l1 = "Ve sen buna katlandın mı?";
			link.l1.go = "Memento_Sailor_3_5";
		break;

		case "Memento_Sailor_3_5":
			dialog.text = "Herkes şansın kendisinden yana olmasını ister. Kaptan, her adamı neyin harekete geçirdiğini bilir: idam korkusu, altın hırsı, kurtarılan bir hayatın borcunu ödeme isteği. Bunların hiçbiri benim için önemli değil. Paraya ihtiyacım yok, hem hatırlamadığın bir şey için nasıl borcun olabilir ki?";
			link.l1 = "Bu kadar açık konuşmaktan korkmuyor musun?";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "Bana ne yapabilirler ki? Burası ölülerin gemisi, Kaptan, ve ben buraya aitim. Ama sen — sen ait değilsin.";
			link.l1 = "Eğer öyle diyorsan. Hoşça kal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Memento'ya hoş geldiniz, Kaptan.";
				link.l1 = "Bir korsan gemisinde İspanyol bir asker mi? Her gün rastlanacak bir şey değil bu.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Başka bir şey var mı, Kaptan?";
				link.l1 = "Hiçbir şey.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		case "Memento_Sailor_4_1":
			dialog.text = "Ben bir firariğim. Kaptan Grim beni San Jose meydanındaki darağacından satın aldı. Ağır bir bedel ödedi — benim zavallı canım için bir çuval altın verdi.";
			link.l1 = "Seni neden astılar?";
			link.l1.go = "Memento_Sailor_4_2";
		break;

		case "Memento_Sailor_4_2":
			dialog.text = "Subay Saldo bizi ormanda işçileri korumaya gönderdi, orada bir haftada yarısı sıtmadan ölüyor. Ben de hayatımın daha değerli olduğuna karar verdim. Şimdi ise ona ödül koyan adama hizmet ediyorum.";
			link.l1 = "Hiç pişmanlığın yok mu?";
			link.l1.go = "Memento_Sailor_4_3";
		break;

		case "Memento_Sailor_4_3":
			dialog.text = "Bir ip uzun süre bükülebilir... Kaptan, kendisine sadık olanlara cömert davranır. Ama bazen bizi tuhaf sınavlara sokar — kura çektirir. Herkesin şansı yaver gitmez.";
			link.l1 = "Kura mı çekiyoruz?";
			link.l1.go = "Memento_Sailor_4_4";
		break;
		
		case "Memento_Sailor_4_4":
			dialog.text = "Biliyorsun. Kimini fırtınada direğe yollarlar, kimini en öne. Kaptan bunun hazır olup olmadığını anlamak için yaptığını söyler. Neyin hazır olup olmadığını bilmiyorum ama umarım şans benden yana olur.";
			link.l1 = "İyi şanslar... Sanırım.";
			link.l1.go = "Memento_Sailor_4_5";
		break;

		case "Memento_Sailor_4_5":
			dialog.text = "Teşekkür ederim, Kaptan. Ölüm er ya da geç hepimizi bulur.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Диалог 5";
				link.l1 = "Диалог 5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Başka bir şey var mı, kaptan?";
				link.l1 = "Hiçbir şey.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Memento'ya hoş geldin, meslektaşım. Benim adım Mortimer Grim.";
				link.l1 = "Kaptan "+GetFullName(pchar)+".   Beni kabul ettiğiniz için teşekkür ederim...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Başka ne hakkında konuşalım?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "Elinizdeki kılıç gerçekten etkileyici, Kaptan.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "Dürbünün iskeletin yanında harika görünüyor.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "Şunu söylemeliyim ki, tayfanız gerçekten de oldukça karışık bir topluluk.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "Hiçbir şey... meslektaşım. Sana iyi rüzgarlar.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;

		case "Memento_MortimerGrim_2":
			dialog.text = "Karayipler darağacına koşanlara cömert davranır, bunu iyi bilirim.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;
		
		case "Memento_MortimerGrim_3":
			dialog.text = "Evet? Sormak istediğiniz bir şey mi vardı?";
			link.l1 = "Arkanda bir iskelet asılı duruyor.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "Bugün rüzgar güzel, değil mi? Hava da harika.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;

		case "Memento_MortimerGrim_4":
			dialog.text = "Hangi iskelet? Arkamda sadece masmavi Karayip Denizi var.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_5":
			dialog.text = "Katılıyorum, dostum. Her gün böyle olsa hiç fena olmazdı!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_6":
			dialog.text = "Ha-ha-ha! Bu şaka asla eskimiyor! Korkma: yaşlı Yorick de, bu gemi gibi, eski hayatımdan kalan bir hatıra. Hem de tam anlamıyla, emin olabilirsin.";
			link.l1 = "‘Gerçekten mi?’";
			link.l1.go = "Memento_MortimerGrim_7";
		break;

		case "Memento_MortimerGrim_7":
			dialog.text = "Meslektaşım, ölümden korkar mısın? Tehdit değil, gerçekten merak ediyorum.";
			link.l1 = "Elbette. Aksini söyleyen herkes yalancıdır.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "Hayır. Hepimiz eninde sonunda orada olacağız.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "Ya sen?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;
		
		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "Ah! Ölüm, tüm korkuların anasıdır. Yalnızlık, karanlık, ceza — hepsi onun maskelerinden ibaret.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "Ah! Ölüm, tüm korkuların anasıdır. Yalnızlık, karanlık, ceza — hepsi onun maskelerinden ibaret.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "Ah! Ölüm, bütün korkuların anasıdır. Yalnızlık, karanlık, ceza — hepsi onun maskelerinden ibaret.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Memento_MortimerGrim_9":
			dialog.text = "Uzağa bakmana gerek yok. Al mesela yaşlı Yorick’i: kaburgalarının arasında bir fenerle kemik yığınına dönmüş — ama senin gibi korkutucu bir kaptan bile tir tir titredi!";
			if (startHeroType == 4)
			{
				dialog.text = "Uzağa bakmana gerek yok. Şu yaşlı Yorick’i düşün: kaburgalarının arasında bir fenerle kemik yığını — büyük Sean MacArthur’un kızı, korkusuz Ellen bile ödü patladı!";
			}
			link.l1 = "Güzel konuşuyorsun, ama bütün bunlarla ne yapmamız gerektiğini söylemedin.";
			link.l1.go = "Memento_MortimerGrim_10";
		break;

		case "Memento_MortimerGrim_10":
			dialog.text = "Ne yapmam gerektiğini biliyorum, ama benim çarem herkese uygun değil. Yine de denemek istersen, önce bana ne düşündüğünü söyle.";
			link.l1 = "İncil, ölümün olmadığını söyler.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "Eğer korkmaya başlarsam, gemi mahvolur.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "Cevap, bir şişe romun dibinde boğuldu.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;
		
		case "Memento_MortimerGrim_11_1":
			dialog.text = "Doğru. O kitaptaki tek katıldığım şey bu.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_2":
			dialog.text = "Takdire şayan. Ama boşuna endişeleniyorsun: ölüm diye bir şey yok.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_3":
			dialog.text = "Yo-ho-ho! Bir alaycı. Ama rom olmasa da şunu söyleyeyim: ölüm diye bir şey yok.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "Basit: gerçek hayat ancak ölümü yendiğinde başlar. Orada bulundum, perdenin ötesinde, ve inan bana, asıl yaşamım o andan sonra başladı.";
			link.l1 = "Tekrar eder misin?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "Boşver, meslektaş.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "Fark ettiğine sevindim, dostum! Gösteriş meraklısı değilim ama korkutucu bir pala olmadan ne biçim korsan olurdum ki?";
			link.l1 = "Gerçekten önemli mi bu?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;
		
		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "Kesinlikle! Geminin hazinesinden kişisel sebeplerle kayda değer miktarda para aldığım tek zaman, işte tam da bu kılıç içindi. İki bin altın doblon, dostum! Cehenneme kadar yolu var, eğer mezarımdan bir kez daha kalkabilseydim, sadece bu kılıcın değeri için geri dönerdim!\n"+"Silahın kendisi mükemmel. Ama nedense... bir şeyler eksik gibi geliyor.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "Birinden gelen bir hediye. Ölümü herkesten farklı anlayan, parlak bir sohbet ustası — ve gördüğün gibi, hayal gücü de oldukça geniş.";
			link.l1 = "Kötü görünüyor.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "Memento mori, meslektaşım.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "Mürettebatımın birbirleriyle ortak noktası seninkilerden fazla, mesela... Hepsini ipten ve zincirden ben kurtardım. Her biri ölümün nefesini hissetti. Bu, insanları kandan ya da bayraktan daha sıkı bağlar.";
			link.l1 = "Yani, hanlarda adam tutmuyorsun sanırım?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;

		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "Eski köleler ve idama mahkûm adamlar ne kadar istekli katılıyor, şaşarsın: bir köle gemisinin ambarını ya da darağacını Memento’nun güvertesine değişmek ister misin? Şimdi 178 tayfam var — ve hepsi bana borçlu.";
			link.l1 = "Ama yine de onlara ödeme yapmalı ve gemiyi idame ettirmelisin. Sadece minnettarlık yetmez.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "Ben başarılı bir korsanım, dostum. Gerçek bir hostis humanitatis’im. İnsanlığın gerçek düşmanları — köle tüccarları ve taçlı başlar — bana böyle derdi. Aralarındaki tek fark ise unvanlarıdır.\n"+"Neyse ki, bolca altınları var. Köle tüccarlarının sandıklarındaki paraları, taç tarafından ölüme mahkûm edilenleri kurtarmak için kullanıyorum. Geri kalan her şey mürettebatıma gidiyor — benim hiçbir şeye ihtiyacım yok. Bir ölünün altınla ne işi olur ki? Yakında onlar da bunu anlayacaklar...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "İşte içinde bulunduğumuz berbat durum bu, Kaptan.";
			link.l1 = "Bu da ne?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "Bir tek sen kaldın. Hastalık hepimizi aldı. Bizi yüzüstü bıraktın.";
			link.l1 = "Bu olamaz!";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "Bizi lanetli bir gemiye getirdin.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "Hepimizi mahvettin!";
			link.l1 = "Alonso, sana ne oldu?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;

		case "Memento_Alonso_phantom_15":
			dialog.text = "Mortui vivos docent.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "Neden durdun, dostum? Fikrini mi değiştirdin? O zaman neden başta saldırdın?";
			link.l1 = "Grim mi? Ama sen ölmüşsün!";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "Ha! Ölü olan asla gerçekten ölmez. Ayrıca, acele etme: belki güverte savaşını kazandın, ama hayatta kalacak mısın... bakalım, göreceğiz!";
			link.l1 = "O kavga haftalar önce bitti! Sen öldün!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "Artık bitti. Zaferin için tebrikler.";
			link.l1 = "Grim?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "Biliyor musun, mutluyum. Gerçekten, beni öldürdüğün için mutluyum. Gerçekten.";
			link.l1 = "Ne diyorsun?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "Korkağım ben, dostum. Sadece ölümden korkan zavallı bir korkak — tıpkı benden önceki binlercesi gibi. Mürettebat vebadan öldüğünde... ve bu benim suçumken, korkudan deliye döndüm. Bir ay boyunca ölüler gemisinde tek başıma sürüklendim.";
			link.l1 = "Gerçekte ne oldu?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "Ölüm sınavında başarısız oldum. Onu kabul edip, hayatta kalıp, bir şeyler öğrenmek yerine, daha da çok korktum. Ve o korkuyu bastırmak için... Başkalarını da benim yaşadıklarımı yaşamaya zorlamaya başladım.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;
		
		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "Teşekkür ederim, meslektaşım. Beni bu... varoluştan kurtardığın için. Artık gerçekten biliyorum ki ölüm yok. Ve artık korkmuyorum. Suçlayacak ya da köleleştirecek kimse kalmadı.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "Memento'yu kaptanından ayırma. Mortimer... Kaptan Mortimer iyi bir adamdı. Onu Dominika'da bul. Ve gemi... gemi seni kabul edecek.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, meslektaşım. Ölüler yaşayanlara ders verir. Elveda.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 