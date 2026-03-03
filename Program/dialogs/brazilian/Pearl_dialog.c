void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Não temos nada para conversar!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("Olá! Meu nome é  "+GetFullName(npchar)+". O que posso fazer por você?","Olá mais uma vez!","Visitantes são muito raros neste fim de mundo...","É tão bom conversar com alguém novo! Já estou de saco cheio dessas caras velhas...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ah, nada...","Eu também...","Entendi...","Heh...",npchar,Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "Estamos coletando pérolas aqui, servindo  "+NationNameGenitive(sti(npchar.nation))+", sabe...";
			link.l1 = "É, eu sei...";
			link.l1.go = "exit";
			link.l2 = "Ei, me diz, tem como comprar vários desses pequenos enfeites direto do 'produtor'? O que você acha?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "Ah não, claro que não! O roubo de até mesmo uma pequena pérola é punido com a morte!";
				link.l1 = "Ordens cruéis você tem aqui, isso é certo...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "É, aqui as ordens são duras, e qualquer deslize pode custar a cabeça de alguém. Eu não estou envolvido nisso, mas posso te aconselhar a conversar com os índios locais sobre isso. Eles têm para onde fugir se algo der errado, então devem ser mais ousados do que a gente...";
				link.l1 = "Entendi... Tudo bem, obrigado.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("Você está completamente  "+GetSexPhrase("Tá maluco? Cai fora, seu idiota","Tá maluco? Cai fora, seu idiota")+"!",""+GetSexPhrase("O quê?! Você ficou maluco, seu idiota","O quê?! Você ficou maluca, sua garota idiota")+"?! Cai fora com esse monte de perguntas...",""+GetSexPhrase("Você ficou maluco, querido? Que piratas? Aqui?! Cai fora, seu idiota","Você ficou maluca, querida? Que piratas? Aqui?! Vai embora, sua tola")+"...");
			link.l1 = RandPhraseSimple("Não precisa ser grosseiro...","Cuide da sua língua!");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","Índia branca")+" quer conversar?","Você de novo, "+GetSexPhrase("paleface","índia branca")+".",""+GetSexPhrase("O Paleface gosta de falar. Ele parece uma índia.","Índia branca gosta de conversar.")+"","Os espíritos trouxeram meu rosto pálido "+GetSexPhrase("irmão","irmã")+" para mim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sim.","Sim, sou eu de novo.","Muito poético.","Também estou feliz em te ver",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Me diga, por que você veio?";
			link.l1 = "Ah, nada em especial, só queria ouvir o que você tem a dizer.";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "Capitão, o que está fazendo? Guarde sua arma antes que cause uma grande confusão!";
			link.l1 = LinkRandPhrase("Certo.","Certo.","Não se preocupe, já estou guardando isso...");
			link.l1.go = "exit";
		break;  

	}
}
