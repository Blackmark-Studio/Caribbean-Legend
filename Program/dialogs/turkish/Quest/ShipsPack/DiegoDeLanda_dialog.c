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

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Hüzünlü bir hikaye, değil mi?";
				link.l1 = "Sen kimsin?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Selamlar, kaptan.";
				link.l1 = "Bekle! Daha önce tanışmıştık!";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "Bir. İki. Üç.";
				link.l1 = "Bu gösteriyi bitirelim. Sen kimsin?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				dialog.text = "Dört.";
				link.l1 = "İkisi kaldı mı?";
				link.l1.go = "DiegoDeLanda_Meeting_Fourth_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "Bu mezarın özelliğini biliyor musun? Burada kan bağıyla bağlı iki ruh yatıyor. Baba ve oğul de Alameda. Biri günahkârların eline düştü, diğeri ise... hmm, yolunu Tanrı'ya buldu.";
				link.l1 = "Don Fernando’nun günlüğü beni buraya getirdi.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "Lady Bishop’u gördün mü? Ne yazık, değil mi? Ama korkarım ki bunu hak etti.";
				link.l1 = "Elizabeth'i tanıyor musun?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "Mortimer Grim.";
				link.l1 = "Onu tanıyordun, değil mi?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_ClockTower"))
			{
				dialog.text = ""+GetCharacterName("Hendrik")+" "+GetCharacterName("van Doorn")+".";
				link.l1 = "Müşterin mi?";
				link.l1.go = "DiegoDeLanda_ClockTower_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nÜç tane daha. Altıya geldiğinde her şeyi öğreneceksin.";
			link.l1 = " Eğer şu anda senden net cevaplar alamazsam, o zaman...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nİyi gidiyorsun, kaptan. Adımı bilmeye hakkın var. Ben Diego de Landa.";
			link.l1 = " Gerçekten bir rahip misin? ";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "Her şeyden önce, ben bir sanatçıyım. Ama acele etmeyelim...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		
		case "DiegoDeLanda_Meeting_Fourth_2":
			dialog.text = "\nÇok doğru, Kaptan. Üçüncü perde başlıyor.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "Ah... Günlük. Yazılı kelime ne kadar da olağanüstü bir şey. Sanki... karanlıkta bir yol gibi. Seni vahyin beklediği yere götürüyor. Don Fernando sık sık bizim kiliseye gelirdi. Özellikle de geçen yıl.";
			link.l1 = "Yerel kilisede mi hizmet ediyorsun? Don Fernando'yu tanıyor muydun?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "Onun yolunu... gözlemledim. Ve aldığın o kitabı da. Onun neden özel olduğunu biliyor musun?";
			link.l1 = "Eski görünüyor.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "Eski mi? Hayır. Bu... aydınlanmış. Don de Alameda Sr.'ın İncili. İçindeki her kelime karanlıkta bir işaret gibi. Al bunu. Mesih'teki kardeşlerine yardım et ve belki de... bu seni... daha büyük bir şeye götürür.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие
		
		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "Ah, evet. Zavallı kadın. Kocası... pek nazik biri değil. Söylentilere göre, Barbados’taki en verimli plantasyonlar ona aitmiş. Ve en zalimleri de. Orada her ay kaç kölenin öldüğünü biliyor musun? Geçenlerde, İngiltere’den gelen gerçek bir doktoru — büyük akıllı ve yetenekli bir adamı — döve döve öldürdü. Ama inan bana, onun karısının kaderi de ondan pek farklı değil.";
			link.l1 = "Oldukça iyi bilgilendirilmiş görünüyorsun.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "İtiraf için bana gelirler, Kaptan. Sevdiklerine bile söylemeye korktukları şeyleri duyarım. Korkuları, günahları... acıları.";
			link.l1 = "Zulme uğramaktan korkmuyor musun? İngiliz topraklarında Katolik bir rahip olmak kolay değil.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "Korkularım, o kapının ardında bıraktıklarınla kıyaslanamaz bile. Ve o talihsiz kadından aldığın küçük kitap... Eğer korkunun bir şekli olsaydı, tam olarak böyle olurdu.\n"+"Günaydın, Kaptan.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "Kaplan, kaplan, parlak parlayan\n"+"Gecenin ormanlarında,\n"+"Hangi ölümsüz el ya da göz\n"+"Korkunç simetrini kim şekillendirebilir?\n"+"Elbette tanıyordum onu, Kaptan. Ama ya siz?";
			link.l1 = "Bu kadar trajik bir kaderi olan bir adamla hiç karşılaşmadım.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "Yaptın, ama henüz farkında değilsin.\n"+"O zaman Grim'i tanımıyordun. Kafatası elindeyken bile.";
			link.l1 = "Ne?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "Ölülerle böyle ilgilenmek Hristiyanlığa yakışmaz. Al, sana küçük bir ölüm sonrası talimatı. Benden sana bir hediye.\n"+"Günaydın, Kaptan.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;
		
		//<-- Мементо
		
		//--> Башня с часами
		case "DiegoDeLanda_ClockTower_2":
			dialog.text = "Zekice, Kaptan. Sen onun müşterisiydin, o da benim."+"Ne kadar da benzersiniz.\n"+"Kayıtlara nasıl girdiğini unutmadın, değil mi? Önce görkemli Willemstad şehrine yardım ettin. Sonra da onun nice evladını kana buladın.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_3";
		break;
		
		case "DiegoDeLanda_ClockTower_3":
			dialog.text = "Gerçi Hendrick bunu başaramadı. Zor bir müşteri, hem de çok zor. Mesela burada. Boş vaktinde oku — tam bir muamma.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_4";
			// получаем документы Маартена
			ClockTower_AddVisserKey();
			
		break;
		
		case "DiegoDeLanda_ClockTower_4":
			dialog.text = "Her insan bir binadır. Onları gerçekten neyin yönlendirdiğini mi öğrenmek istiyorsun? Mahzenlerine bak.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_5";
		break;
		
		case "DiegoDeLanda_ClockTower_5":
			dialog.text = "Al bakalım.";
			if (CheckAttribute(pchar, "questTemp.ClockTower_GotHint"))
			{
				link.l1 = "Kilerin anahtarı mı? Oraya zaten gittim.";
				link.l1.go = "DiegoDeLanda_ClockTower_6";
			}
			else
			{
				link.l2 = "Kilerinde ne var?";
				link.l2.go = "DiegoDeLanda_ClockTower_7";
			}
		break;
		
		case "DiegoDeLanda_ClockTower_6":
			dialog.text = "\nO halde konuşacak başka bir şeyimiz kalmadı, Kaptan.";
			link.l1 = "Alındın mı? Merak ediyorum, mahzeninde ne var?";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		case "DiegoDeLanda_ClockTower_7":
			dialog.text = "\nHer konuşmamız, oraya bir adım daha yaklaşmak demek, Kaptan.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			ClockTower_AddBook_FromDiegoDeLanda(); // получаем ключ от подвала
		break;
		
		//<-- Башня с часами
		
		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;
		
		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Bana söyle... Neden? Bu tehlikeli ve aptalcaydı. Seni ne yönlendiriyor, Kaptan? İçindeki ateş nedir?";
				link.l1 = "Bu seni ilgilendirmez.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "İkinci.";
				link.l1 = "Geçen sefer bilmecelerle konuştun. Yine öyle mi yapacaksın?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "Bekle, de Landa. Seni öylece alıp gitmene izin veremem.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				dialog.text = "İpuçları, gösterişler ve hiçbir hareket yok\n"+"Benim açımdan en azından. Senin başından ise epey macera geçti.";
				link.l1 = "Bunu nasıl düzelteceğimle ilgili bir fikrim var.";
				link.l1.go = "DiegoDeLanda_Leaving_Fourth_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "Anlamıyorum. Diğerleri — evet. Ama sen değil. Henüz değil.";
			link.l1 = "Diğerleri?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "Mesela biri adalet arıyor. Bir diğeri... ölümün karanlık sularına saplantılı. İnsanlar arzularında ne kadar kolay kayboluyor, sence de öyle değil mi?";
			link.l1 = "Garip bir rahipsiniz, Peder.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "Gitmeliyim.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "Elbette. İşiniz daha yeni başlıyor, Kaptan.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\nGerçek bilmece şimdi karşımda duruyor. Zaten iki... kutsal emanet topladın. Böyle şeyleri toplamayı mı seviyorsun? Koleksiyoncu musun?";
			link.l1 = " Bunu nereden biliyorsun? ";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "Bir ganimet avcısı mı?";
			link.l1 = "Sorumu tekrarlıyorum: bunu nereden biliyorsun?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;
		
		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "Macera mı arıyorsun?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nAh. Tabii ki. Elbette. O halde, Kaptan, sizi daha fazla tutmayacağım.";
			link.l1 = "Dur bir dakika, Peder. Hâlâ soruma cevap vermedin.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "Oh, Kaptan. Yapamam. Bazen cevaplar, cehaletten daha çok acıtır. Huzurla git. Ve koleksiyonuna... o ganimetlerine iyi bak. Önündeki yolculukta işe yarayabilirler.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "Haydi ama, Kaptan. Hiç mi ilginç gelmiyor sana? Eğlenmiyor musun? Kupaların yeterince oldu mu?\n"+"İşte senin ateşin bu, Kaptan. Sonrasını merak ediyorsun. Güzel gemilere ve ilginç eşyalara hayransın.\n"+"Hepsini toplamak zorunda kalıyorsun, elinde değil.\n"+"\n"+"Beni hemen şimdi vurabilirsin.";
			link.l1 = "Ne?!";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "Devam et. Ama o zaman her şeyi öğrenemeyeceksin ve tüm ödülleri tamamlayamayacaksın. Yine de bütün gemileri alacaksın...\n"+"Günaydın, Kaptan.";
			link.l1 = "Bırak gitsin";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(Vur onu)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_Fourth_2": // Четвёртое прощание
			dialog.text = "\nÇok geç, Kaptan. Beni vurmak için fırsatın vardı. Hem de ne fırsat! Üçe kadar saydım: bir, iki, üç... ve hiçbir şey olmadı. Ama merak etme. Altıda sana hareket göstereceğim. Artık çok az kaldı.\n"+"Günaydın, Kaptan.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 