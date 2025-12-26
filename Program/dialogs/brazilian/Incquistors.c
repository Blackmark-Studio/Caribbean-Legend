void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("Irmãos, há um inimigo infiltrado nas fileiras da Inquisição!","Toquem o alarme, irmãos!");
					link.l1 = "De fato, os inimigos da Inquisição estão em alerta...";
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Olá, "+GetSexPhrase("meu filho","minha filha")+". O que te traz aqui?.. ","Fico feliz em ver você em nossa morada, "+GetSexPhrase("meu filho","minha filha")+". . O que te traz aqui?"),""+GetSexPhrase("Meu filho","Minha filha")+", já conversamos hoje. Precisa de mais alguma coisa?",""+GetSexPhrase("Meu filho","Minha filha")+", os acólitos da nossa ordem não são conhecidos por sua paciência infinita. Então, vou perguntar mais uma vez: precisa de alguma coisa?",RandPhraseSimple("Você está distraindo os outros de suas tarefas. Não vou mais falar com você.",""+GetSexPhrase("Meu filho","Minha filha")+", não gosto de conversa fiada e sem sentido. Não vou mais falar com você."),"block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Só dei uma passada...","Totalmente cheio de negócios..."),"Ah, não, Padre......","Não, padre, só queria conversar...",RandPhraseSimple("Hmm...","Bem, como quiser, pai..."),npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "Às armas! É um espião! Peguem ele!";
					link.l1 = "Caramba!";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("Esta é uma cela vigiada, e a entrada aqui é estritamente proibida.","Nem pense em entrar, isso é punido com a morte.","Basta um passo dentro desta cela e você está acabado.");
					link.l1 = RandPhraseSimple("Entendi, soldado.","Entendi...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("Ho-ho, não é engraçado ver esses 'santos' indo direto pro inferno?!","Meu Deus, alguém realmente teve coragem de desafiá-los?!","Eles me torturaram quase até a morte, e logo vou morrer, mas você me fez feliz pela última vez na minha vida...");
					link.l1 = RandPhraseSimple("Heh!","De nada...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Aqueles hipócritas são completamente desumanos. Vão queimar no inferno por tudo o que fizeram conosco...","Eles me torturaram e atormentaram todos os dias! Mas não sou culpado aos olhos do nosso Senhor!","Meu companheiro de cela morreu ontem... Eles o torturaram no cavalete por dois dias... E quem sabe quanto tempo ainda vou aguentar ...");
					link.l1 = RandPhraseSimple("Hum... Bem, eu não sei...","Ah, entendi...");
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
	}
}
