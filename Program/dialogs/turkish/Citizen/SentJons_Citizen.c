// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsun?");
			link.l1 = RandPhraseSimple("Fikrimi değiştirdim.'","Şu anda söyleyecek bir şeyim yok.");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "Bay Jones'u arıyorum. Onu tanıyor musunuz?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "Burada çok sayıda Jones var. Bildiğim en ünlüsü, Albay Fox'un yaveri Benjamin Jones. Genellikle alayın karargâhında ziyaretçileri karşılar.";
				link.l1 = "Onun Molly adında bir kız kardeşi var mı?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("Hangi Jones'u arıyorsun? En az iki düzine Jones tanıyorum...","Burada çok fazla Jones var. Daha açık olmanız gerek.","Burada çok fazla Jones, ayrıca Johnson ve Jackson da var. Biraz daha açık olmalısın, tamam mı?");
				link.l1 = "Yetişkin bir kız kardeşi var, adı Molly. Onun nadir bulunan bir güzelliğe sahip olduğu söyleniyor.";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Hm, korkarım bu konuda sana yardımcı olamam.","Hayır, onu tanımıyorum.","Peh! Benim tanıdığım Molly Jones ender bir güzellikse, Albay Fox da mahalle papazıdır."),LinkRandPhrase("Ben birkaç Molly Jones tanıyorum. Onlardan birinin erkek kardeşi var ama... aradığın kişi o değil. Onu 'eşsiz bir güzellik' olarak ancak maymunlarla yaşamış biri tanımlar.","Üzgünüm, ama tanıdığım tüm Jones'ların kız kardeşi yok.","Üzgünüm, sana yardımcı olamam. Başkasına sor."));
			link.l1 = "Anladım. Rahatsızlık verdiysem kusura bakmayın.";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "Evet, ama onun erkek kardeşi olsa daha iyi olurdu. Bu güçlü kızcağız, şu suratı yüzünden kendine bir koca bulamayacak gibi.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Sence gizli serviste mi çalışıyorum "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Pekala... hayır. O halde hoşça kal.";
			link.l1.go = "exit";
			link.l2 = "Başka bir sorunuz var mı, peki?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Ben soruşturma bürosu muyum? Bilmiyorum, hiçbir şeyden haberim yok.";

            link.l1 = "Sen tam bir şaşkınsın! Defol.";
			link.l1.go = "exit";
			link.l2 = "Başka bir sorunuz var mı, peki?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
